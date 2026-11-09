# 从 BST 到 AVL 再到红黑树 · 完整教程

> 写给已经会写 C、能看懂指针和递归，但还没系统学过自平衡树的人。
>
> 本文所有 C 代码都在 GCC 16.2.0 (MinGW-w64) 上编译通过，开启 `-Wall -Wextra` 零警告，
> 并通过了随机测试。你可以放心复制、编译、运行。

## 目录

- **第 0 章** 为什么要学"平衡树"？
- **第 1 章** 复习：二叉搜索树（BST）
- **第 2 章** 高度、平衡因子：AVL 的判据
- **第 3 章** 旋转：实现细节（本文重点）
- **第 4 章** AVL 树的插入
- **第 5 章** AVL 树的删除
- **第 6 章** 为什么还要红黑树？—— 设计取舍
- **第 7 章** 红黑树的性质
- **第 8 章** 红黑树的插入与修复
- **第 9 章** 红黑树的删除（完整实现）
- **第 10 章** 完整实现代码
- **第 11 章** 学习路线与练习答案

---

## 第 0 章 为什么要学"平衡树"？

### 0.1 数组 vs 链表：各自的问题

假设你要存一堆数字，支持"插入/删除/查找"三种操作。

| 结构 | 查找 | 插入 | 删除 | 问题 |
|---|---|---|---|---|
| 有序数组 | O(log n) 二分 | O(n) 挪位置 | O(n) | 插入删除太慢 |
| 链表 | O(n) | O(1)（已知位置） | O(1) | 查找太慢 |

**我们希望三件事都快，都接近 O(log n)。** 这就是树存在的理由：
在树里往下走一层，就排除一大半数据，走 `log n` 层就到叶子。

### 0.2 二叉搜索树能做到，但有前提

二叉搜索树（BST）的查找复杂度 **取决于树的高度 h**。

- 树长得像"人"（左右差不多高）：`h ≈ log₂n`，查找很快
- 树长得像"棍子"（一条斜线）：`h ≈ n`，退化成链表

**问题：** 用有序数据 `1, 2, 3, 4, 5 ...` 依次插入一棵 BST，树会变成一条右斜的棍子。
此时查找 `n` 需要 `n` 次比较——**BST 退化了**。

```
依次插入 1,2,3,4,5 得到：
1
 \
  2
   \
    3
     \
      4
       \
        5        ← 这就是一条链表
```

### 0.3 平衡树要解决的问题

> **让树"自己保持矮胖"，无论你按什么顺序插入。**

即：任何时候，树的高度都保持在 `O(log n)` 量级。

本文要学的两棵树都解决这个问题：

| | AVL 树 | 红黑树 |
|---|---|---|
| 平衡严格程度 | **严格**：任意节点左右子树高度差 ≤ 1 | **近似**：最长路径 ≤ 最短路径的 2 倍 |
| 查找速度 | 最快（树更矮） | 稍慢 |
| 插入/删除代价 | 较高（可能旋转多次） | 较低（最多 3 次旋转） |
| 典型用途 | 查找远多于修改的场景 | 通用；STL `map/set`、Linux 内核、Java TreeMap |

**一句话：AVL 偏"查"，红黑树偏"改"。** 理解了 AVL，红黑树就好理解了——它们用的是同一套旋转工具。

### 0.4 本文的记号约定（非常重要）

不同教材的约定不同，看的时候一定要先确认对方用的是哪种。**本文统一如下：**

| 概念 | 约定 |
|---|---|
| 空树 `NULL` 的高度 | **−1** |
| 叶节点（没有孩子）的高度 | **0** |
| 节点高度 | `max(左高, 右高) + 1` |
| 平衡因子 BF | `左子树高度 − 右子树高度` |

好处：叶节点的 BF = `(-1) − (-1) = 0`，天然平衡；判空逻辑统一为一句
`n == NULL ? -1 : n->height;`，不用到处补 `+1/-1`。

---

## 第 1 章 复习：二叉搜索树（BST）

### 1.1 节点的结构

```c
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
```

一个节点装两个指针，指向左右孩子。叶子节点的 `left` 和 `right` 都是 `NULL`。

> **注意：** 这里的节点没有 `parent` 指针。
> - **AVL 插入**不需要它（递归返回时天然知道谁是父节点）
> - **AVL 删除**和**红黑树**的修复需要"往上走"，所以后面要给节点加 `parent` 字段

### 1.2 BST 的核心性质

**对树中每个节点 X：**

- 左子树里所有值 **<** X 的值
- 右子树里所有值 **>** X 的值

这一个性质决定了：**中序遍历（左→根→右）的输出一定是升序的。**

> 反过来，这也是一个免费的自检工具：
> 每次插入或删除后，跑一遍中序，看是不是升序，就能立刻发现"树被转坏了"。
> 本书后续所有测试代码都靠它自检。

### 1.3 插入：递归 + 返回值接线

```c
TreeNode *insert(TreeNode *root, int val)
{
    if (root == NULL) {
        TreeNode *p = malloc(sizeof(TreeNode));
        if (p == NULL) { perror("malloc"); return NULL; }
        p->data = val;
        p->left = p->right = NULL;
        return p;
    }

    if (val < root->data)
        root->left = insert(root->left, val);    /* ← 关键行 */
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}
```

**契约：** `insert` 接收一棵子树的根，插好后返回**新的子树根**。

**为什么要"接收返回值"？** 因为空位处会长出新节点，子树的根会变。
父节点必须写 `root->left = insert(...)` 把新根接回去。

递归展开看看（往 `50` 里插 `20`）：

```
insert(50, 20)
  20 < 50 → 50->left = insert(50.left, 20)     ← 先不赋值，等下层结果
      insert(NULL, 20)
        创建节点，return 新节点 ────────────┐
  50->left = 新节点  ←─────────────────────┘  接回来了
```

**记住这个模式：** 递归写树，永远靠"接收返回值"来连回父子关系。
AVL 的 `insert` 会在这个基础上多两步，但骨架完全相同。

### 1.4 查找

```c
TreeNode *search(TreeNode *root, int target)
{
    while (root != NULL) {
        if (target == root->data) return root;
        root = (target < root->data) ? root->left : root->right;
    }
    return NULL;
}
```

复杂度 = 树高 = `O(h)`。完美平衡时 `h ≈ log₂n`；退化成棍子时 `h = n`。

### 1.5 删除：三个分支

删除比插入复杂，分三种情况（设要删的节点是 `n`）：

| 情况 | 处理 |
|---|---|
| `n` 没有左孩子 | 用 `n` 的右孩子顶替 `n` 的位置，`free(n)` |
| `n` 没有右孩子 | 用 `n` 的左孩子顶替，`free(n)` |
| `n` 有两个孩子 | 找 **后继**（右子树里最小的节点），把它的值抄到 `n`，再去右子树删掉后继 |

```c
TreeNode *delete_node(TreeNode *root, int key)
{
    if (root == NULL) return NULL;

    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL) {                 /* 情况 1 */
            TreeNode *t = root->right;
            free(root);
            return t;
        }
        if (root->right == NULL) {                /* 情况 2 */
            TreeNode *t = root->left;
            free(root);
            return t;
        }
        /* 情况 3：找后继 */
        TreeNode *succ = root->right;
        while (succ->left != NULL) succ = succ->left;
        root->data = succ->data;
        root->right = delete_node(root->right, succ->data);
    }
    return root;
}
```

**情况 3 为什么可以"抄值"？** 因为 BST 里每个节点只靠 `data` 存在，
身份（节点地址）没有额外意义，只要整棵树仍满足 BST 性质就行。

> ⚠️ **AVL/红黑树里，这条要小心。**
> 因为节点还带有**高度/颜色**这些"节点自己的状态"。
> 抄值不会破坏树，但**必须保证从被删位置往上的一整条路径都重新更新高度和颜色**。
> 本文第 5 章的 AVL 删除用的就是"抄值"，并依赖 `rebalance()` 沿路径修复，这是正确且简单的写法。

### 1.6 一个真实的 bug：`free_tree` 少了递归

```c
/* ❌ 错误 */
void free_tree(TreeNode *root)
{
    if (root == NULL) return;
    free(root->left);      /* 只释放了"左孩子这一块" */
    free(root->right);     /* 只释放了"右孩子这一块" */
    free(root);
}
```

问题：`free` 只释放传进去的**那一个节点**，**不会**连带释放它的子孙。

```
       50
       /
      30
      /
     20

free_tree(50):
  free(50->left)   → free(30)    只释放了 30，20 的地址从此没人知道 → 泄漏
  free(50->right)  → free(NULL)
  free(50)
```

**正确写法：后序遍历，先处理完左右子树，再释放自己。**

```c
/* ✅ 正确 */
void free_tree(TreeNode *root)
{
    if (root == NULL) return;
    free_tree(root->left);     /* 递归！ */
    free_tree(root->right);    /* 递归！ */
    free(root);
}
```

> **原则：整棵树是递归结构，处理整棵树就必须用递归。**

### 1.7 本章练习

1. 对下面这棵树写出**中序**遍历结果：
   ```
           50
          /  \
         30   70
        / \   / \
       20 40 60 80
   ```
2. 下面这段创建节点的代码少做了什么？
   ```c
   TreeNode *create(int v) {
       TreeNode *p = malloc(sizeof(TreeNode));
       p->data = v;
       p->left = p->right = NULL;
       return p;
   }
   ```
3. 依次插入 `10, 20, 30, 40`，画出最终树形，并说明查找 `40` 需要比较几次。

答案在第 11 章。

---

## 第 2 章 高度、平衡因子：AVL 的判据

### 2.1 给节点加一个 `height` 字段

AVL 每次插入后都要检查"有没有歪"。如果每次都现场递归去算子树高度，
那么一次插入会变成 O(n)。**所以每个节点自己存一个 `height`，随用随取。**

```c
typedef struct AVLNode {
    int data;
    int height;              /* 这个节点的高度：叶子=0，空=NULL 视为 -1 */
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;
```

### 2.2 三个基础函数

```c
/* 取一个节点的高度，NULL 返回 -1 */
int avl_height(AVLNode *n)
{
    return n == NULL ? -1 : n->height;
}

/* 重算节点高度 = max(左高, 右高) + 1 */
static void update_height(AVLNode *n)
{
    if (n == NULL) return;
    int lh = avl_height(n->left);
    int rh = avl_height(n->right);
    n->height = (lh > rh ? lh : rh) + 1;
}

/* 平衡因子 = 左高 − 右高 */
int avl_balance(AVLNode *n)
{
    if (n == NULL) return 0;
    return avl_height(n->left) - avl_height(n->right);
}
```

要点：

- **所有"取高度"都走 `avl_height()`**，空指针判断只写一次，避免到处漏判空。
- `update_height()` 必须在**左右孩子都处理完之后**调用（后序位置）。
- `avl_balance()` 对空节点返回 0（空树当然平衡），这样调用处不用特判。

### 2.3 手算练习

```
        A
       / \
      B   C
     / \
    D   E
       /
      F
```

按本文约定（NULL = −1）逐个算：

| 节点 | 左高 | 右高 | height | BF |
|---|---|---|---|---|
| F | −1 | −1 | 0 | 0 |
| E | 0 | −1 | 1 | 1 |
| D | −1 | −1 | 0 | 0 |
| B | 0 | 1 | 2 | −1 |
| C | −1 | −1 | 0 | 0 |
| **A** | 2 | 0 | 3 | **2** ← 失衡！ |

**结论：A 失衡，且是"左边高 2"，即 L 型。** 这就是 AVL 插入修复要干的事。

### 2.4 关键认知：要检查"每一个节点"

> **不是只看根！AVL 要求树中每一个节点的 BF 都在 [−1, +1] 之间。**

只看根是新手最常见的错误。一棵树根平衡、但某个深处节点失衡，同样不是 AVL。

> 有一个重要性质：**插入一个节点时，只有根到新叶子这条路径上的节点的 BF 会变化。**
> 所以修复只需沿这条路径从下往上走；而递归的"回溯"天然就是自下而上，正好对应。

### 2.5 本章练习

1. 在上一节那棵树里，插入 `G` 作为 `D` 的左孩子。现在哪些节点失衡了？（要逐个检查）
2. 如果只用 `height` 而不用 BF，怎么判断一个节点是否平衡？两种写法有什么性能差异？

---

## 第 3 章 旋转：实现细节

> **这是全文最重要的一章。** 很多人会说"失衡了就旋转"，但写不出三行指针。
> 本章从"换爹"的直觉推到代码，一步步来。

### 3.1 旋转到底是什么

旋转是**一次局部改写**：几个指针重新指向，**不改变**谁是谁的子孙（只改"谁是谁的孩子"），
所以**中序顺序不变**（BST 性质只靠中序判断）。

右旋的图（记住这个图，后面反复用）：

```
        y                 x
       / \               / \
      x   C             A   y
     / \       ==>         / \
    A   B                 B   C
```

**用一句话说清楚：**

> **`x` 升上来当新的根，`y` 降下去当 `x` 的右孩子，`B` 改挂到 `y` 的左边。**

- `x` = `y` 的**左孩子**（要升上来的那个）
- `B` = `x` 的右孩子：原来夹在 `x`、`y` 中间的那个"内孙"
- `A`、`C` 不动

### 3.2 先想清楚"谁负责接回父节点"

假设 `y` 上面有个父节点 `P`。`P` 原来指向 `y`。

**关键：旋转函数不处理 `P`。**

为什么？因为**旋转函数会返回新根 `x`**，由调用方写
`P->left = rotate_right(P->left)`（或用递归返回值接上）。
**旋转只负责"x 和 y 之间"的接线。**

> 这样设计的好处：旋转函数里没有"往上找父节点"的逻辑，代码只有 9 行，而且能同时用于 AVL（无 parent）和红黑树（有 parent，见第 8 章）。

### 3.3 一行一行推右旋

#### 第 0 步：先把要挪的东西存进局部变量

```c
AVLNode *x = y->left;      /* 升上来的那个 */
AVLNode *B = x->right;     /* 内孙，必须先存！ */
```

**为什么必须存 `B`？** 因为下一步要写 `x->right = y`，
这一句会**覆盖掉 `x->right`，原来的 `B` 指针就丢了**，
而 `B` 连着的整棵子树还在——丢了它，那棵子树就再也找不到了（泄漏 + 树形错乱）。

#### 第 1 行：让 `x` 当爹

```c
x->right = y;
```

```
      x            ← x 现在指向 y 当右孩子
     / \
    A   y
       / \
      B   C
```

此时 `y` 还挂在 `x->right`，但 `x->right` 原来存 `B` 的信息已经没了（我们存进变量了）。

#### 第 2 行：`B` 改挂到 `y` 左边

```c
y->left = B;
```

```
      x
     / \
    A   y
       / \
      B   C
```

**为什么是 `y->left`，不是 `y->right`？**
因为 `B` 在原树里位于 `x` 的右边、`y` 的左边，即 `x < B < y`。
挂到 `y` 的左边才满足 BST。**挂错边，整个 BST 就坏了。**

#### 第 3、4 行：更新高度

```c
update_height(y);    /* 先更新被降下去的 y */
update_height(x);    /* 再更新升上来的 x */
```

**顺序绝对不能反。** `x` 的新高度依赖 `y` 的新高度算出来
（`x` 现在有个孩子是 `y`）。先算 `x` 会用到 `y` 的旧高度，结果就错了。

#### 最后：返回新根

```c
return x;
```

### 3.4 完整的 `rotate_right`

```c
static AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left;      /* 升上来的那个 */
    AVLNode *B = x->right;     /* 内孙，先存 */

    x->right = y;              /* x 当爹，y 挂右边 */
    y->left  = B;              /* B 改挂到 y 左边 */

    update_height(y);          /* 先更新降下去的 */
    update_height(x);          /* 再更新升上来的 */

    return x;                  /* 新根交回 */
}
```

九行。你现在可以对照"三句话"再读一遍。

### 3.5 左旋：镜像

```
        x                 y
       / \               / \
      A   y      ==>    x   C
         / \           / \
        B   C         A   B
```

**三句话：** `y` 升上来当根，`x` 降下去当 `y` 的左孩子，`B` 改挂到 `x` 的右边。

```c
static AVLNode *rotate_left(AVLNode *x)
{
    AVLNode *y = x->right;     /* 升上来的那个 */
    AVLNode *B = y->left;      /* 内孙，先存 */

    y->left  = x;              /* y 当爹，x 挂左边 */
    x->right = B;              /* B 改挂到 x 右边 */

    update_height(x);          /* 先更新降下去的 */
    update_height(y);          /* 再更新升上来的 */

    return y;
}
```

**对照右旋看：左边高 → 右旋；右边高 → 左旋。** 名字听起来别扭（"左边高怎么是右旋？"），
因为"右旋"说的是**旋转方向**：整个结构顺时针转，右边的东西转到上面去。
记不住就记图，别记名字。

### 3.6 旋转的验收标准

写完旋转后，**不要只看代码，要跑出来验证**。两条标准：

1. **中序仍是升序** → 指针连对了，BST 没坏
2. **每个节点的 height、BF 打印正确** → 高度更新顺序对了

测试代码：

```c
/*
 * 搭一棵小树：
 *        30 (y)
 *       /  \
 *      20  40
 *     /  \
 *    10  25      ← 25 就是"内孙" B
 */
void demo_rotate(void)
{
    AVLNode *y = avl_new(30);
    y->left  = avl_new(20);
    y->right = avl_new(40);
    y->left->left  = avl_new(10);
    y->left->right = avl_new(25);

    /* 手搭的树必须手动更新高度，且要从下往上 */
    update_height(y->left->left);     /* 10: 0 */
    update_height(y->left->right);    /* 25: 0 */
    update_height(y->left);           /* 20: 1 */
    update_height(y->right);          /* 40: 0 */
    update_height(y);                 /* 30: 2 */

    AVLNode *newroot = rotate_right(y);
    avl_dump_inorder(newroot);
    /* 实际输出（已在本机 gcc 验证）：
       10(h0,bf+0) 20(h2,bf-1) 25(h0,bf+0) 30(h1,bf+0) 40(h0,bf+0)
       新根是 20
    */
}
```

**看懂这个输出：**

```
        20          ← 新根，左 10(h0)，右 30(h1) → height=2, BF=-1
       /  \
     10    30       ← 30 左挂 25，右挂 40
            / \
          25   40
```

- 中序仍是 `10 20 25 30 40`，**升序 ✅**（BST 没坏）
- `20` 的 height 是 **2** 不是 1（因为它有两个孩子），BF 是 **−1**（左 0 − 右 1）
  → 这个节点本身是平衡的，旋转后整棵树重新变成了一个合法 AVL 形状

> `update_height` 是 `static` 的，在 `avl.c` 内部可用。
> 手搭树时**漏了更新高度**是极常见的错误，会直接导致旋转后 BF 全错。
> **更省心的做法**：用 `avl_insert` 一个个插进去，让它自己维护高度。

### 3.7 本章练习

1. 不看上面代码，写出 `rotate_left`（照右旋的四个步骤）。
2. 画图并逐个写出：对下面这棵树做 `rotate_left(30)` 后，每个节点的 `left/right` 指向谁？
   ```
       30
         \
          50
         /  \
       40    60
   ```
3. 如果旋转后**忘记** `update_height`，会在什么时候暴露出错误？（提示：想想下一次插入时 `balance` 拿到的数据）

---

## 第 4 章 AVL 树的插入

### 4.1 一句话概括

> **AVL 插入 = BST 插入 + 回来时更新高度 + 发现自己歪了就转。**

就这三件事。核心仍然是"**靠返回值接回父子关系**"。

### 4.2 代码骨架

```c
AVLNode *avl_insert(AVLNode *root, int val)
{
    /* ① 照搬 BST：插进去 */
    if (root == NULL)
        return avl_new(val);

    if (val < root->data)
        root->left = avl_insert(root->left, val);
    else if (val > root->data)
        root->right = avl_insert(root->right, val);
    else
        return root;                    /* 重复值不插 */

    /* ② 回来时修复：两步 */
    return rebalance(root);
}
```

`rebalance()` 内部做两件事：更新高度、判失衡、必要时旋转。

### 4.3 `rebalance()`：四种失衡

```c
static AVLNode *rebalance(AVLNode *root)
{
    if (root == NULL) return NULL;
    update_height(root);                    /* 必须先更新高度！ */

    int bf = avl_balance(root);

    if (bf > 1)                                     /* 左边高 */
    {
        if (avl_balance(root->left) >= 0)           /* LL：一字型 */
            return rotate_right(root);

        root->left = rotate_left(root->left);       /* LR：先拉直 */
        return rotate_right(root);                  /*     再平衡 */
    }
    if (bf < -1)                                    /* 右边高 */
    {
        if (avl_balance(root->right) <= 0)          /* RR：一字型 */
            return rotate_left(root);

        root->right = rotate_right(root->right);    /* RL：先拉直 */
        return rotate_left(root);                   /*     再平衡 */
    }
    return root;                                    /* 没歪，原样返回 */
}
```

### 4.4 判断口诀：按顺序问两个问题

拿到一个失衡节点 `root`，依次回答：

**第 1 问：`root` 哪边高？**

| `BF` | 含义 | 代号 |
|---|---|---|
| `> 1`（≥ 2） | 左高 | **L** 开头 |
| `< -1`（≤ −2） | 右高 | **R** 开头 |

**第 2 问：那个"高的孩子"哪边高？**

| 情况 | 高孩子的 BF | 名字 | 处理 |
|---|---|---|---|
| 左高、左孩子也左高 | `leftBF >= 0` | **LL** | 对 root **右旋** 一次 |
| 左高、左孩子右高 | `leftBF < 0` | **LR** | 先对 **root->left 左旋**，再对 root **右旋** |
| 右高、右孩子也右高 | `rightBF <= 0` | **RR** | 对 root **左旋** 一次 |
| 右高、右孩子左高 | `rightBF > 0` | **RL** | 先对 **root->right 右旋**，再对 root **左旋** |

**记忆：** 第一个字母 = `root` 哪边高，第二个字母 = 那个高孩子哪边高。
**直线型（LL/RR）转一次；拐弯型（LR/RL）转两次，第一次把拐弯拉直。**

### 4.5 四种情况画图

**LL（左-左，一字型）**

```
       z                    y
      /                    / \
     y       右旋z         x   z
    /        ====>
   x
```

**LR（左-右，拐弯型）**

```
       z             z                y
      /             /                / \
     y    先左旋y   x     再右旋z    x   z
    /     =====>     \    =====>
   x                  y
```

**RR（右-右，一字型）**

```
   z                          y
    \                        / \
     y       左旋z          z   x
      \      ====>
       x
```

**RL（右-左，拐弯型）**

```
   z              z                  y
    \              \                / \
     y   先右旋y    x    再左旋z    z   x
      \  =====>   /     =====>
       x         y
```

### 4.6 为什么"只修第一个失衡节点"就够了

**插入**一个节点，只会让**根到新叶子这条路径**上的节点高度最多各增加 1。
所以第一个（从下往上）失衡的节点，BF 只可能是 ±2，不会是 ±3。

而**一次旋转会把那棵子树的高度恢复到插入之前的值**。
子树高度没变 → 上面所有节点的 BF 都不受影响 → 上面全都不会失衡。

> **AVL 插入修复：自下而上，通常只修一次。** 这与删除不同（第 5 章会讲）。

### 4.7 `rebalance` 里那个"必须先更新高度"的坑

```c
update_height(root);       /* ① */
int bf = avl_balance(root); /* ② */
```

如果顺序反了，`avl_balance` 拿到的还是**旧高度**，会误判"没歪"，
于是该转的没转，AVL 性质被破坏。

### 4.8 完整可运行示例

```c
#include <stdio.h>
#include "avl.h"

int main(void)
{
    AVLNode *root = NULL;
    int vals[] = {30, 20, 10, 40, 50, 25, 5, 35, 45, 1};
    for (int i = 0; i < 10; i++)
        root = avl_insert(root, vals[i]);

    avl_dump_inorder(root);      /* 中序，格式 值(h高,bf平衡因子) */
    avl_destroy(root);
    return 0;
}
```

**实测输出（已验证）：**

```
1(h0,bf+0) 5(h1,bf+0) 10(h0,bf+0) 20(h2,bf+1) 25(h0,bf+0) 30(h3,bf+0) 35(h0,bf+0) 40(h2,bf-1) 45(h0,bf+0) 50(h1,bf+1)
```

**判据：** 中序升序 ✅；所有节点 `|BF| ≤ 1` ✅；每行 `height` 与 `max(子高)+1` 相符 ✅。

### 4.9 本章练习

1. 依次插入 `1, 2, 3, 4, 5, 6, 7`，画出**每一步**插入后的树形（重点看什么时候触发旋转、触发的是哪种类型）。
2. 依次插入 `50, 30, 70, 20, 40, 60, 80, 25`，插完 `25` 后哪个节点失衡？是哪种类型？旋转一次后树形如何？
3. `LR` 情况为什么不能直接对 root 右旋？（画图看结果满足 AVL 吗）

---

## 第 5 章 AVL 树的删除

### 5.1 和插入的最大区别

> **插入：修一个就够。**
> **删除：可能一路上每个节点都要修。**

原因：插入让子树长高时，旋转会把高度"还原"，上面的节点不受影响。
但删除让子树变矮时，旋转**不一定**能把高度补回来——补不回来，上面就可能接着失衡。

**所以 `avl_delete` 的每个递归层返回前，都必须调用 `rebalance`。**

### 5.2 删除的三个分支

和 BST 一样：

```c
AVLNode *avl_delete(AVLNode *root, int val)
{
    if (root == NULL) return NULL;

    if (val < root->data)
        root->left = avl_delete(root->left, val);
    else if (val > root->data)
        root->right = avl_delete(root->right, val);
    else
    {
        /* ── 找到了 ── */
        if (root->left == NULL)                 /* 情况 1：只有右孩子/没有孩子 */
        {
            AVLNode *r = root->right;
            free(root);
            return r;
        }
        if (root->right == NULL)                /* 情况 2：只有左孩子 */
        {
            AVLNode *l = root->left;
            free(root);
            return l;
        }
        /* 情况 3：两个孩子 → 找后继，抄值，再去右子树删掉它 */
        AVLNode *succ = min_node(root->right);
        root->data = succ->data;
        root->right = avl_delete(root->right, succ->data);
    }

    /* 回来时都要重新平衡 */
    return rebalance(root);
}
```

`min_node` 就是一路往左走到底：

```c
static AVLNode *min_node(AVLNode *n)
{
    while (n->left != NULL) n = n->left;
    return n;
}
```

### 5.3 情况 1、2 为什么直接 `return` 就结束

删掉一个只有一个孩子的节点时，孩子顶上来，**不需要在这里 `rebalance`**。
但这棵"变矮了的子树"的返回值交给了**父节点**，父节点那层会接着 `rebalance`。
所以修复是从下往上逐层进行的。

### 5.4 情况 3 "抄值"的细节

- 抄的是**后继的值**，不是节点本身；后继节点随后从右子树被真正删除
- **为什么这不会破坏 AVL 的性质？**
  因为 `root` 的值变了，但它的**子树结构没变**；高度由 `rebalance` 里的
  `update_height` 重新算，`BF` 也重新算。整条路径都会走一遍 `rebalance`。
- **真正的坑**：如果你的树里存的是**指向对象的指针/大结构体**，而
  "节点身份"有意义（比如你以后要用它做迭代器），抄值就会有麻烦。
  那时应该改成**物理搬移节点**（把后继节点摘下来、替换到被删位置），
  代价是代码更啰嗦。

### 5.5 删除时可能触发"链式修复"

画个小例子（删除后连续失衡）：

```
        50
       /  \
     30    70
    /  \     \
  20   40    80
```

删除 `20` 之后，`30` 的左子树从高 1 变成高 0：

```
        50
       /  \
     30    70
       \     \
       40    80
```

`50`：左高 1、右高 2 → BF = **−1**，还算平衡。但再删几个：

```
        50
       /  \
     30    80
       \
       40
```

`50`：左高 1、右高 1，平衡。**如果删得更多**，就会一路往上失衡。
这正是"删除需要在每个返回层都 `rebalance`"的原因。

### 5.6 实测：删除包含双孩子的情况

**输入：** 插入 `30 20 10 40 50 25 5 35 45 1`，然后依次删除 `20`、`30`（`30` 是双孩子）。

**实测输出：**

```
删除 20 之后: 1 5 10 25 30 35 40 45 50 （全部 BST=1 AVL=1）
删除 30 之后: 1 5 10 25 35 40 45 50  （全部 BST=1 AVL=1，树高=4）
```

并且在随机测试中通过了 **200 轮 × 400 次混合插入与删除**，每步都检查：
BST 性质、所有节点的 `|BF| ≤ 1`、`height` 字段正确、节点总数正确。

### 5.7 本章练习

1. 对下面的树删除 `5`，画出结果，说明哪些节点失衡、用哪种旋转修：
   ```
          10
         /  \
        5    15
       / \     \
      3   7     20
     /     \
    1       8
   ```
2. 删除一个有**两个孩子**的节点，`rebalance` 会在这条路径上调用几次？
3. 为什么删除时"后继的最小值节点"被选来抄值，而不是"前驱"？两种都能工作，说说各自会让树更倾向哪一侧。

---

## 第 6 章 为什么还要红黑树？—— 设计取舍

### 6.1 AVL 的"过度"在哪里

AVL 要求**每个节点**左右子树高度差 ≤ 1。这带来：

- ✅ **查找非常快**（树尽可能矮）
- ❌ **插入/删除代价偏高**：为了维持这么严格的条件，一次删除可能要在路径上做出多次旋转

如果你的场景是**"读多写少"**（比如只建一次、然后反复查询），AVL 极好。
但如果是**"写也很频繁"**（比如内存里的索引、每次操作都要增删），AVL 的旋转成本就值得商量。

### 6.2 红黑树的思路：放宽一点，换来写入便宜

> **红黑树不要求高度差 ≤ 1，只要求："最长路径不超过最短路径的 2 倍"。**

具体通过**节点颜色**来实现。它保证：

- 树高始终是 `O(log n)`
- **插入最多 2 次旋转**，**删除最多 3 次旋转**

用**稍长一点的树**换**更少的旋转**。这就是工程上的取舍：
STL 的 `std::map` / `std::set`、Linux 内核调度器、Java 的 `TreeMap`，用的都是红黑树。

### 6.3 两者对比

| | AVL | 红黑树 |
|---|---|---|
| 平衡条件 | 每个节点 \|BF\| ≤ 1 | 最长 ≤ 2 × 最短 |
| 树高上界 | 约 1.44 log₂n | 2 log₂n |
| 查找 | **更快** | 稍慢 |
| 插入旋转 | 最多 1~2 次 | 最多 2 次 |
| 删除旋转 | O(log n) 次 | 最多 3 次 |
| 实现难度 | 中等 | 较难（插入）/ 很难（删除） |
| 需要 parent 指针 | 不需要（递归可解决） | **需要**（修复要往上走） |

> **结论：两者都是"好树"，选谁看场景。** 面试常问"区别"，答"平衡条件不同、
> 红黑树旋转少、适合写多的场景"就够了。

---

## 第 7 章 红黑树的性质

### 7.1 五条性质（背下来）

1. 每个节点是 **红色** 或 **黑色**
2. **根节点是黑色**
3. 所有叶子（NIL/空指针）都是**黑色**
4. **红色节点的两个孩子都必须是黑色**（即不允许"红红相邻"）
5. 从任一节点出发到其所有叶子的路径上，**黑色节点数量相同**（黑高相等）

> 第 3 条里的"叶子"指**空指针 NULL**，不是数据叶子。很多教程会把 NULL 换成
> 一个专门的黑色哨兵节点 `TNULL`，只是为了少写判空，本质完全一样。
> **本文代码直接用 `NULL`，并把 `NULL` 当黑色处理。**

### 7.2 节点结构：多了 `color` 和 `parent`

```c
typedef enum { RED, BLACK } RBColor;

typedef struct RBNode
{
    int data;
    RBColor color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;   /* ← 修复要往上走，所以要存父亲 */
} RBNode;
```

**为什么必须有 `parent`？** 红黑树的修复是**迭代**的（`while` 循环往上爬），
不像 AVL 可以用递归回溯。没有 `parent` 就得用显式栈，代码更啰嗦。

### 7.3 为什么这些性质能保证"最长 ≤ 2×最短"

推理链（很重要，理解一次就忘不掉）：

1. 由性质 5，任何路径的**黑高**相同。设这条共同黑高为 `bh`。
2. 由性质 4，红节点不能相邻。所以任何路径上**红色最多和黑色一样多**。
3. 于是任何路径长度 ≤ `2bh`，又 ≥ `bh`。
4. **最长路径 ≤ 2 × 最短路径。** ✅

因为黑高 `bh ≥ log₂(n+1)`，所以树高 `≤ 2 log₂(n+1) = O(log n)`。

### 7.4 新插入的节点为什么是红色？

**如果插黑色**：会立刻破坏性质 5（黑高不等），几乎每次都要大修。
**如果插红色**：只会可能破坏性质 4（红红相邻），修正简单得多。

所以：**新节点永远染红**，修复的目标是**消除"红红相邻"**。

### 7.5 旋转换上了 `parent`，怎么写

AVL 的旋转函数靠"返回新根"，因为没有 `parent`。红黑树有 `parent`，旋转直接**原地改指针**，
不需要返回值，但要把 **4 条边**都接好：

| 边 | 说明 |
|---|---|
| `x->parent` | 被降下去的节点，其父亲变成升上来的 |
| `grandparent->left/right` | 父亲的孩子指针也要改 |
| `y->left`（新子的左孩子） | 内孙 `B` 要改挂 |
| `B->parent` | 内孙的父亲也变了 |

```c
/* 左旋：y = x->right 升上来 */
static void rotate_left(RBNode **root, RBNode *x)
{
    RBNode *y = x->right;
    RBNode *B = y->left;                 /* 内孙，先存 */

    x->right = B;                        /* ① B 改挂到 x 右边 */
    if (B != NULL) B->parent = x;

    y->parent = x->parent;               /* ② y 接到 x 原来的父亲下 */
    if (x->parent == NULL)
        *root = y;                       /* x 是根，根变了 */
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;                         /* ③ y 降下去当 x 的爹 */
    x->parent = y;
}
```

`rotate_right` 完全镜像：

```c
static void rotate_right(RBNode **root, RBNode *y)
{
    RBNode *x = y->left;
    RBNode *B = x->right;

    y->left = B;
    if (B != NULL) B->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}
```

> **对比 AVL 的旋转**：核心那两行连接一模一样（`x->right = y; y->left = B;`），
> 区别只是多了 `parent` 的维护，以及"谁是根"的分支判断。

---

## 第 8 章 红黑树的插入与修复

### 8.1 插入流程

1. 按 BST 规则插入，新节点染 **红色**
2. 如果父节点是黑色 → **什么都没破坏，结束**
3. 如果父节点是红色 → **红红相邻**，进入修复

### 8.2 修复的核心：看"叔叔"的脸色

设当前红红相邻的节点是 `z`（红），父亲 `p`（红），爷爷 `g`（一定是黑，因为红不能相邻），
叔叔 `u` 是 `g` 的另一个孩子。

**只有两种情况：叔叔红 / 叔叔黑。**

#### 情况 1：叔叔是红色

```
        g(黑)                  g(红)         ← 继续往上修
       /      \               /      \
     p(红)    u(红)   ==>    p(黑)    u(黑)
     /                       /
   z(红)                   z(红)
```

**动作：** `p` 和 `u` 变黑，`g` 变红，`z` 上移到 `g`，**继续循环**。

**为什么这样做？** 红红矛盾被"推"到了爷爷身上（爷爷变红了，它和它的父亲可能又冲突）。
这一步**不旋转**，只改颜色。

如果 `g` 是根，循环结束后会把根染黑（性质 2）。

#### 情况 2：叔叔是黑色

分两个子情况，取决于 `z` 相对 `p` 是左孩子还是右孩子：

**情况 2a：z 与 p 同侧（一字型，即 LL 或 RR）**

```
      g(黑)                p(黑)         ← 修复完成
     /                    /    \
   p(红)         ==>    z(红)  g(红)
   /
 z(红)
```

**动作：** `p` 变黑，`g` 变红，**对 `g` 做一次旋转**，结束。

**情况 2b：z 与 p 异侧（拐弯，即 LR 或 RL）**

```
      g(黑)                g(黑)               p(黑)? 
     /                    /                   ...
   p(红)        ==>     z(红)      再转一次
      \                /
      z(红)          p(红)
```

**动作：** 先**对 `p` 旋转一次**，把拐弯拉直，变成 2a 的形状，再按 2a 处理。

> **看这里是不是很眼熟？** 这和 AVL 的 LL/LR/RR/RL **一模一样的套路**：
> 一字型转一次，拐弯型先拉直再转。**你学过 AVL，这章不会难。**

### 8.3 修复代码

```c
static void insert_fixup(RBNode **root, RBNode *z)
{
    /* 只要 z 有父亲、且父亲是红的，就还有红红矛盾 */
    while (z->parent != NULL && is_red(z->parent))
    {
        RBNode *p = z->parent;
        RBNode *g = p->parent;

        if (p == g->left)                        /* 父亲是爷爷的左孩子 */
        {
            RBNode *u = g->right;                /* 叔叔 */

            if (is_red(u))                       /* 情况 1：叔叔红 */
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;                           /* 上移，继续修 */
            }
            else
            {
                if (z == p->right)               /* 情况 2b：拐弯 */
                {
                    rotate_left(root, p);        /* 先拉直 */
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;                /* 情况 2a：一字型 */
                g->color = RED;
                rotate_right(root, g);           /* 转一次，完成 */
            }
        }
        else                                      /* 镜像：父亲是右孩子 */
        {
            RBNode *u = g->left;

            if (is_red(u))
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else
            {
                if (z == p->left)
                {
                    rotate_right(root, p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotate_left(root, g);
            }
        }
    }
    (*root)->color = BLACK;                      /* 性质 2：根必须黑 */
}
```

### 8.4 插入代码

```c
RBNode *rb_insert(RBNode *root, int val)
{
    RBNode *z = rb_new(val, RED);    /* 新节点永远是红的 */

    if (root == NULL) { z->color = BLACK; return z; }

    /* ① 标准 BST 插入（迭代） */
    RBNode *cur = root, *parent = NULL;
    while (cur != NULL)
    {
        parent = cur;
        if (val < cur->data)      cur = cur->left;
        else if (val > cur->data) cur = cur->right;
        else { free(z); return root; }   /* 重复值 */
    }
    z->parent = parent;
    if (val < parent->data) parent->left  = z;
    else                    parent->right = z;

    /* ② 修复 */
    insert_fixup(&root, z);
    return root;
}
```

### 8.5 跟着修复走一遍

依次插入 `10, 20, 30`：

```
插入 10：树空 → 10 当根，染黑
    10(B)

插入 20：20 > 10，挂 10 右边，染红
    10(B)       父是黑 → 不修 ✅
      \
      20(R)

插入 30：30 > 20，挂 20 右边，染红
    10(B)
      \
      20(R)     ← 红红相邻！z=30, p=20, g=10, 叔叔 u=NULL(黑)
        \
        30(R)   情况 2：叔叔黑，且 z 是 p 的右孩子 → 一字型 RR

动作：p(20) 变黑，g(10) 变红，对 g(10) 左旋
    20(B)
   /    \
 10(R)  30(R)
```

**结果：** 根是黑，无红红相邻，黑高一致 ✅。

### 8.6 本章练习

1. 依次插入 `1, 2, 3, 4, 5`，画出每次插入后的红黑树，标出每一步触发了哪种修复情况。
2. 情况 1（叔叔红）为什么可以在不旋转的情况下把问题"推上去"？如果 `g` 是根，会发生什么？
3. 情况 2 里为什么父节点最终一定被染黑？（想想黑高守恒）

---

## 第 9 章 红黑树的删除（完整实现）

> **这一章是全文最难的。** 但别怕：它的骨架和插入是同一套——**先删除，再修复；修复时看"兄弟"的脸色**。
> 读完你会拿到一份经过 300 轮 × 500 次随机测试的完整实现。

### 9.1 删除比插入难在哪里

插入时，**新节点是红色的**，最多破坏"红红相邻"这一条性质，修起来简单。
删除时，**可能删掉一个黑节点**，那就会破坏性质 5（黑高不等）。

而且删除还有一个额外麻烦：**被删的节点可能有两个孩子**，
你要先把"别人的节点"搬到它的位置上——这就牵扯到搬迁节点的颜色、父子指针。

**所以要分两阶段看：**

```
阶段一：物理删除（BST 的删除逻辑 + parent 维护）
阶段二：颜色修复（如果移走的是黑节点）
```

### 9.2 阶段一：物理删除

BST 删除的三种情况（第 1.5 节讲过），在红黑树里要加上 `parent` 的维护：

| 情况 | 动作 |
|---|---|
| `z` 没有左孩子 | 用 `z->right` 顶替 `z` 的位置 |
| `z` 没有右孩子 | 用 `z->left` 顶替 `z` 的位置 |
| `z` 有两个孩子 | 用右子树最小值 `y` **物理搬**到 `z` 的位置 |

> **注意：红黑树这里不用"抄值"，而是真的把 `y` 这个节点搬过去。**
> 为什么？因为节点有颜色——如果只抄值，被删掉的其实是 `y` 那个节点，
> 它的颜色也得跟着消失；而搬动整个节点，逻辑最清楚，代码也最不容易错。

**"搬"是怎么搬的：** 用 `transplant` 函数，把子树 `v` 接到 `u` 原来的位置。

```c
/* 用子树 v 顶替子树 u 的位置（v 可以是 NULL） */
static void transplant(RBNode **root, RBNode *u, RBNode *v)
{
    if (u->parent == NULL)
        *root = v;                 /* u 是根 */
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}
```

**双孩子的情况**（`y` 是 `z` 右子树的最小节点）：

```
        z                     y
       / \                   / \
      L   R        ==>      L   R'
         /                     /
        y                     x
         \
          x
```

步骤：

1. `y = min(z->right)`，记下 `y_orig = y->color`（这个颜色决定要不要修）
2. `x = y->right`（`y` 最多只有右孩子，因为它是最小值）
3. **如果 `y->parent == z`**（`y` 就是 `z` 的右孩子）：`x` 直接挂在 `y` 下面，不用搬
4. **否则**：先把 `y` 从原位置摘掉（`transplant(y, y->right)`），再把 `y` 搬到 `z` 的位置
5. 让 `y` 接管 `z` 的左右孩子，**并继承 `z` 的颜色**（这一步关键：颜色不变，黑高就不变）
6. 最后 `free(z)`

### 9.3 阶段二：什么时候需要修

**只有当"移走的颜色"是黑色时才需要修。**

```c
y_orig = (被移走的那个节点的颜色);
...
if (y_orig == BLACK)
    delete_fixup(&root, x, x_parent);
```

- 移走红色 → 黑高不变 → **不用修**
- 移走黑色 → 有一条路径少了一层黑 → **要修**

### 9.4 修复的核心：把"少的这层黑"还上

把缺口记在顶替上来的节点 `x` 上（`x` 可能是 `NULL`！），
说成"**`x` 这一支欠一层黑**"（一些资料叫 double black）。

修复的循环条件是：

```c
while (x != root && x 是黑色)    /* 黑的才欠债；红的直接染黑就还清 */
{
    ... 看兄弟 ...
}
x->color = BLACK;                /* 收尾 */
```

> **为什么红的直接染黑就行？** 因为把红染黑，等于给这条路径**加**了一层黑——债就还清了。
> 而如果 `x` 已经是黑，就还不动，只能找兄弟帮忙。

### 9.5 四种情况（`x` 是父 `p` 的左孩子，兄弟 `s = p->right`）

> 记住：**只处理"`x` 欠一层黑"这一种矛盾**。四种情况是"怎么还债"的四种办法。

#### 情况 1：兄弟 `s` 是红的

```
        p(黑)                      s(黑)
       /     \                    /     \
    x(黑)    s(红)     ==>      p(红)   SR(黑)
    欠黑    /    \              /    \
          SL    SR          x(黑)   SL
          欠黑
```

**动作：** `s` 变黑，`p` 变红，**对 `p` 左旋**，然后重新取兄弟 `s = p->right`。

**作用：** 把"红兄弟"变成"黑兄弟"，转成情况 2/3/4。**这是转换器，不解决问题。**

> 为什么兄弟一定是红的可以直接转？因为红兄弟的两个孩子都是黑的（性质 4），
> 转完之后 `x` 的新兄弟（原来的 SL）是黑的，符合后面情况的前提。

#### 情况 2：兄弟 `s` 是黑的，且**两个孩子都是黑的**

```
        p(?)                       p(?)  ← 债上移给 p
       /    \                     /    \
    x(黑)   s(黑)     ==>      x(黑)   s(红)
    欠黑   /    \               欠黑   /    \
        黑     黑                   黑     黑
```

**动作：** `s` 变红，`x = p`，`x_parent = p->parent`，**继续循环**。

**作用下：** 兄弟变红 → 兄弟那支少了一层黑 → 现在 `p` 的左右两支都少一层 →
债整体上移到 `p`。**这就是"往上推"，和插入的情况 1 完全对应。**

#### 情况 3：兄弟 `s` 是黑的，`s` 左孩子红、右孩子黑

```
        p(?)                     p(?)
       /    \                   /    \
    x(黑)   s(黑)    ==>     x(黑)   SL(黑)
    欠黑   /    \            欠黑   /    \
        SL(红) 黑                红     s(红)
                                       /   \
                                      黑    黑
```

**动作：** `s->left` 变黑，`s` 变红，**对 `s` 右旋**，然后 `s = p->right`（新兄弟）。

**作用：** 转成情况 4（新兄弟的右孩子是红的）。**也是转换器。**

#### 情况 4：兄弟 `s` 是黑的，`s` 右孩子是红的

```
        p(颜色c)                  s(颜色c)
       /    \                    /      \
    x(黑)   s(黑)     ==>      p(黑)    SR(黑)
    欠黑   /    \              /    \
         ?    SR(红)       x(黑)    ?
                           欠黑(被消掉)
```

**动作：**
1. `s->color = p->color`
2. `p->color = BLACK`
3. `s->right->color = BLACK`
4. **对 `p` 左旋**
5. `x = root`，**结束循环**

**作用：** 这是唯一**真正解决**问题的情况。旋转 + 变色之后，`x` 那支多了一层黑（债还清），
其他路径黑高不变。

### 9.6 对称情况怎么办

上面四种都是"`x` 是左孩子"。当 `x` 是右孩子时，**把 left/right 全部互换**：

| 左孩子版 | 右孩子版 |
|---|---|
| `s = p->right` | `s = p->left` |
| 对 `p` 左旋 | 对 `p` 右旋 |
| 情况 3 看 `s->left` 红 | 情况 3 看 `s->right` 红 |
| 情况 3 对 `s` 右旋 | 情况 3 对 `s` 左旋 |
| 情况 4 看 `s->right` 红 | 情况 4 看 `s->left` 红 |

代码里就是两个大 `if/else` 分支，逻辑完全镜像。

### 9.7 一个致命的坑：`x` 可能是 `NULL`

这是红黑树删除**最容易写错**的地方。

想象：删掉一个黑叶子节点，`x` 就是 `NULL`。
修复循环需要读 `x->parent` 来判断"我是左孩子还是右孩子"——但 `NULL->parent` 会**直接崩溃**。

**解决方案：额外传一个 `x_parent` 参数。**

```c
static void delete_fixup(RBNode **root, RBNode *x, RBNode *x_parent);
```

每次 `x` 往上移的时候，`x_parent` 也要跟着更新：

```c
x = x_parent;              /* 债上移 */
x_parent = x->parent;      /* 父也跟着上移 */
```

> 教材里用黑色 `TNULL` 哨兵，就是为了避免这个问题（哨兵有真实的 `parent` 指针）。
> 我们用 `NULL` 当叶子，就必须自己记住父节点。**两种做法本质一样，但后者更容易看清逻辑。**

### 9.8 完整修复代码

```c
static void delete_fixup(RBNode **root, RBNode *x, RBNode *x_parent)
{
    while (x != *root && is_black(x))
    {
        if (x_parent == NULL) break;

        if (x == x_parent->left)
        {
            RBNode *s = x_parent->right;          /* 兄弟 */

            if (s == NULL) {                      /* 防御性判断 */
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))                        /* 情况 1 */
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_left(root, x_parent);
                s = x_parent->right;
            }

            if (is_black(s->left) && is_black(s->right))   /* 情况 2 */
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->right))                    /* 情况 3 */
                {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotate_right(root, s);
                    s = x_parent->right;
                }
                /* 情况 4 */
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->right->color = BLACK;
                rotate_left(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
        else
        {
            /* 镜像 */
            RBNode *s = x_parent->left;

            if (s == NULL) {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_right(root, x_parent);
                s = x_parent->left;
            }

            if (is_black(s->left) && is_black(s->right))
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->left))
                {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotate_left(root, s);
                    s = x_parent->left;
                }
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->left->color = BLACK;
                rotate_right(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}
```

### 9.9 完整删除函数

```c
RBNode *rb_delete(RBNode *root, int val)
{
    /* ① 先找 */
    RBNode *z = root;
    while (z != NULL && z->data != val)
        z = (val < z->data) ? z->left : z->right;
    if (z == NULL) return root;              /* 没找到 */

    RBNode *x;            /* 顶替上来的节点（可能为 NULL） */
    RBNode *x_parent;     /* 它的父亲 */
    RBColor y_orig;       /* 被移走的节点的原色 */

    if (z->left == NULL)
    {
        x = z->right;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->left);
    }
    else
    {
        /* 两个孩子：用右子树最小值 y 物理顶替 z */
        RBNode *y = min_node(z->right);
        y_orig = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x_parent = y;
        }
        else
        {
            x_parent = y->parent;
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;                 /* 继承 z 的颜色！ */
    }

    /* ② 移走黑色才需要修 */
    if (y_orig == BLACK)
        delete_fixup(&root, x, x_parent);

    free(z);
    return root;
}
```

### 9.10 跟着走一遍：删除黑叶子

树（节点后面的字母是颜色）：

```
        20(B)
       /     \
     10(R)   30(R)
     /  \    /   \
   5(B) 15(B) 25(B) 35(B)
```

**删除 `5`（黑叶子）：**

1. `z = 5`，没有孩子 → `x = NULL`，`x_parent = 10`，`y_orig = BLACK`
2. `transplant(5, NULL)` 后，`10->left = NULL`
3. `y_orig == BLACK` → 进入 `delete_fixup(root, NULL, 10)`
4. `x = NULL` 是黑，`x != root` → 循环
5. `x == 10->left`，兄弟 `s = 15(B)`
6. `s` 不是红；`s->left`、`s->right` 都是 NULL（黑）→ **情况 2**
7. `s` 变红，`x = 10`，`x_parent = 20`
8. 现在 `x = 10` 是**红**，循环条件 `is_black(x)` 不成立 → **退出**
9. 收尾 `x->color = BLACK` → `10` 变黑

**结果：**

```
        20(B)
       /     \
     10(B)   30(R)
       \     /   \
      15(R) 25(B) 35(B)
```

**验算黑高：** 每条路径都是 2 层黑。
- 20 → 10 → 15 → NULL：10(B)、NULL(B) = 2 ✅
- 20 → 30 → 25 → NULL：30(R) 不算、25(B)、NULL = 2 ✅

**修好了。** 注意：这次修复**没有旋转**，只改了两次颜色。

### 9.11 和插入的对照

| | 插入修复 | 删除修复 |
|---|---|---|
| 目标 | 消除"红红相邻" | 消除"少一层黑" |
| 看谁 | 叔叔的颜色 | 兄弟的颜色 + 兄弟孩子的颜色 |
| 上推 | 情况 1 推到爷爷 | 情况 2 推到父亲 |
| 真正终结的 | 情况 2/3（旋转） | 情况 4（旋转） |
| 旋转次数 | ≤ 2 | ≤ 3 |
| 循环变量 | `z` | `x`（可能是 NULL！） |

### 9.12 本章练习

1. 在上面的树里继续删除 `15`（红叶子），会发生什么？需要修复吗？
2. 删除 `10`（红，有一个右孩子 `15`）会发生什么？
3. 什么情况下删除后需要连续上推多次（情况 2 循环）？
4. 为什么 `y->color = z->color`（双孩子时继承颜色）是必须的？


---

## 第 10 章 完整实现代码

> 以下代码全部在本机 gcc 16.2.0 编译通过（`-Wall -Wextra` 零警告），
> 并通过了随机测试。建议按顺序保存到各自的目录里编译。

### 10.1 AVL 树

**`avl.h`**

```c
#ifndef AVL_H
#define AVL_H

typedef struct AVLNode
{
    int data;
    int height;          /* 叶子为 0，NULL 视为 -1 */
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *avl_new(int val);
AVLNode *avl_insert(AVLNode *root, int val);
AVLNode *avl_delete(AVLNode *root, int val);
AVLNode *avl_find(AVLNode *root, int val);
int  avl_height(AVLNode *n);
int  avl_balance(AVLNode *n);
void avl_dump_inorder(AVLNode *n);
void avl_destroy(AVLNode *n);

#endif
```

**`avl.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int avl_height(AVLNode *n)
{
    return n == NULL ? -1 : n->height;
}

static void update_height(AVLNode *n)
{
    if (n == NULL) return;
    int lh = avl_height(n->left);
    int rh = avl_height(n->right);
    n->height = (lh > rh ? lh : rh) + 1;
}

int avl_balance(AVLNode *n)
{
    if (n == NULL) return 0;
    return avl_height(n->left) - avl_height(n->right);
}

AVLNode *avl_new(int val)
{
    AVLNode *p = (AVLNode *)malloc(sizeof(AVLNode));
    if (p == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
    p->data = val;
    p->height = 0;
    p->left = p->right = NULL;
    return p;
}

static AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *B = x->right;

    x->right = y;
    y->left  = B;

    update_height(y);
    update_height(x);
    return x;
}

static AVLNode *rotate_left(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *B = y->left;

    y->left  = x;
    x->right = B;

    update_height(x);
    update_height(y);
    return y;
}

static AVLNode *rebalance(AVLNode *root)
{
    if (root == NULL) return NULL;
    update_height(root);

    int bf = avl_balance(root);

    if (bf > 1)
    {
        if (avl_balance(root->left) >= 0)
            return rotate_right(root);
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (bf < -1)
    {
        if (avl_balance(root->right) <= 0)
            return rotate_left(root);
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

AVLNode *avl_insert(AVLNode *root, int val)
{
    if (root == NULL)
        return avl_new(val);

    if (val < root->data)
        root->left = avl_insert(root->left, val);
    else if (val > root->data)
        root->right = avl_insert(root->right, val);
    else
        return root;

    return rebalance(root);
}

static AVLNode *min_node(AVLNode *n)
{
    while (n->left != NULL) n = n->left;
    return n;
}

AVLNode *avl_delete(AVLNode *root, int val)
{
    if (root == NULL)
        return NULL;

    if (val < root->data)
        root->left = avl_delete(root->left, val);
    else if (val > root->data)
        root->right = avl_delete(root->right, val);
    else
    {
        if (root->left == NULL)
        {
            AVLNode *r = root->right;
            free(root);
            return r;
        }
        if (root->right == NULL)
        {
            AVLNode *l = root->left;
            free(root);
            return l;
        }
        AVLNode *succ = min_node(root->right);
        root->data = succ->data;
        root->right = avl_delete(root->right, succ->data);
    }
    return rebalance(root);
}

AVLNode *avl_find(AVLNode *root, int val)
{
    while (root != NULL && root->data != val)
        root = (val < root->data) ? root->left : root->right;
    return root;
}

void avl_dump_inorder(AVLNode *n)
{
    if (n == NULL) return;
    avl_dump_inorder(n->left);
    printf("%d(h%d,bf%+d) ", n->data, n->height, avl_balance(n));
    avl_dump_inorder(n->right);
}

void avl_destroy(AVLNode *n)
{
    if (n == NULL) return;
    avl_destroy(n->left);
    avl_destroy(n->right);
    free(n);
}
```

**编译：** `gcc avl.c main.c -Wall -Wextra -o avl_test`

### 10.2 红黑树

> 完整实现，包含**插入、删除、四类校验函数**。
> 已通过 300 轮 × 500 次随机插入/删除测试，`-Wall -Wextra` 零警告。

**`rbtree.h`**

```c
#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } RBColor;

typedef struct RBNode
{
    int data;
    RBColor color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;   /* 红黑树修复需要往上走，所以必须存父亲 */
} RBNode;

/* ---------- 基本操作 ---------- */
RBNode *rb_new(int val, int color);
RBNode *rb_insert(RBNode *root, int val);
RBNode *rb_delete(RBNode *root, int val);
RBNode *rb_find(RBNode *root, int val);

/* ---------- 遍历与释放 ---------- */
void rb_dump_inorder(RBNode *n);
void rb_destroy(RBNode *n);

/* ---------- 校验（学习/测试用） ---------- */
int rb_is_bst(RBNode *root);        /* 中序是否严格升序 */
int rb_black_height(RBNode *root);  /* 黑高；-1 表示不等 */
int rb_check(RBNode *root);         /* 五条性质全查，返回 1 通过 */

#endif
```

**`rbtree.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

/* ============================================================
 * 约定：用 NULL 表示空叶子，且把 NULL 视为黑色。
 * （教材里的黑色 TNULL 哨兵只是为了少判空，本质相同。）
 * ============================================================ */

static int is_red(RBNode *n)
{
    return n != NULL && n->color == RED;
}

static int is_black(RBNode *n)
{
    return n == NULL || n->color == BLACK;
}

RBNode *rb_new(int val, int color)
{
    RBNode *p = (RBNode *)malloc(sizeof(RBNode));
    if (p == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
    p->data   = val;
    p->color  = color;
    p->left   = NULL;
    p->right  = NULL;
    p->parent = NULL;
    return p;
}

/* ============================================================
 * 旋转（带 parent 的版本）
 * 核心两行和 AVL 完全一样：x->right = y; y->left = B;
 * 多出来的是：B->parent、y->parent、爷爷的孩子指针、根的更新。
 * ============================================================ */

static void rotate_left(RBNode **root, RBNode *x)
{
    RBNode *y = x->right;
    RBNode *B = y->left;

    x->right = B;
    if (B != NULL) B->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

static void rotate_right(RBNode **root, RBNode *y)
{
    RBNode *x = y->left;
    RBNode *B = x->right;

    y->left = B;
    if (B != NULL) B->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* ============================================================
 * 插入修复
 * 矛盾：z 和 z->parent 都是红色。看叔叔：
 *   叔叔红 → 父叔变黑，爷爷变红，z 上移到爷爷继续
 *   叔叔黑 → 一字型：父变黑、爷爷变红、对爷爷旋转，结束
 *            拐弯型：先对父旋转成一字型，再按上面处理
 * ============================================================ */

static void insert_fixup(RBNode **root, RBNode *z)
{
    while (z->parent != NULL && is_red(z->parent))
    {
        RBNode *p = z->parent;
        RBNode *g = p->parent;

        if (p == g->left)
        {
            RBNode *u = g->right;                 /* 叔叔 */

            if (is_red(u))
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else
            {
                if (z == p->right)                /* 拐弯：先拉直 */
                {
                    rotate_left(root, p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;                 /* 一字型 */
                g->color = RED;
                rotate_right(root, g);
            }
        }
        else
        {
            RBNode *u = g->left;

            if (is_red(u))
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else
            {
                if (z == p->left)
                {
                    rotate_right(root, p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotate_left(root, g);
            }
        }
    }
    (*root)->color = BLACK;
}

RBNode *rb_insert(RBNode *root, int val)
{
    RBNode *z = rb_new(val, RED);          /* 新节点永远红色 */

    if (root == NULL)
    {
        z->color = BLACK;
        return z;
    }

    /* ① 标准 BST 插入 */
    RBNode *cur = root, *parent = NULL;
    while (cur != NULL)
    {
        parent = cur;
        if (val < cur->data)      cur = cur->left;
        else if (val > cur->data) cur = cur->right;
        else { free(z); return root; }     /* 重复值 */
    }
    z->parent = parent;
    if (val < parent->data) parent->left  = z;
    else                    parent->right = z;

    /* ② 修复 */
    insert_fixup(&root, z);
    return root;
}

/* ============================================================
 * 删除
 * ============================================================ */

/* 用子树 v 顶替子树 u 的位置（v 可以是 NULL） */
static void transplant(RBNode **root, RBNode *u, RBNode *v)
{
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

static RBNode *min_node(RBNode *n)
{
    while (n->left != NULL) n = n->left;
    return n;
}

/* ------------------------------------------------------------
 * 删除修复
 *
 * x 是"顶替上来的节点"，可能为 NULL。
 * 因为 x 可能是 NULL（读不到 x->parent），所以额外传一个 x_parent。
 *
 * 记账方式：x 这一支比别的路径少了一层黑，需要把这个缺口补掉。
 * 设 s 是兄弟（x 在左边时 s = parent->right）：
 *
 *   情况 1：s 红
 *        s 变黑、parent 变红、对 parent 左旋 → 转成 2/3/4
 *   情况 2：s 黑，s 两个孩子都黑
 *        s 变红，缺口上推给 parent，x 上移
 *   情况 3：s 黑，s 左孩子红、右孩子黑
 *        s 左孩子变黑、s 变红、对 s 右旋 → 转成情况 4
 *   情况 4：s 黑，s 右孩子红
 *        s 继承 parent 的颜色，parent 变黑，s 右孩子变黑，
 *        对 parent 左旋，结束
 *
 * 对称情况把 left/right 互换即可。
 * ------------------------------------------------------------ */
static void delete_fixup(RBNode **root, RBNode *x, RBNode *x_parent)
{
    /* 只有"x 是黑的"才需要补黑 */
    while (x != *root && is_black(x))
    {
        if (x_parent == NULL) break;      /* 理论上不会发生 */

        if (x == x_parent->left)
        {
            RBNode *s = x_parent->right;  /* 兄弟 */

            if (s == NULL)                /* 防御：兄弟不可能为空，但保险 */
            {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))                       /* 情况 1 */
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_left(root, x_parent);
                s = x_parent->right;
            }

            if (is_black(s->left) && is_black(s->right))   /* 情况 2 */
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->right))                    /* 情况 3 */
                {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotate_right(root, s);
                    s = x_parent->right;
                }
                /* 情况 4 */
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->right->color = BLACK;
                rotate_left(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
        else
        {
            /* 镜像：x 是右孩子 */
            RBNode *s = x_parent->left;

            if (s == NULL)
            {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_right(root, x_parent);
                s = x_parent->left;
            }

            if (is_black(s->left) && is_black(s->right))
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->left))
                {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotate_left(root, s);
                    s = x_parent->left;
                }
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->left->color = BLACK;
                rotate_right(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;   /* 根、或补完黑的节点，染黑收尾 */
}

RBNode *rb_delete(RBNode *root, int val)
{
    /* ① 先找 */
    RBNode *z = root;
    while (z != NULL && z->data != val)
        z = (val < z->data) ? z->left : z->right;
    if (z == NULL) return root;            /* 没找到 */

    RBNode *x;            /* 顶替上来的节点 */
    RBNode *x_parent;     /* x 的父亲（x 为 NULL 时也要知道） */
    RBColor y_orig;       /* 真正"移走"的那个节点的原色 */

    if (z->left == NULL)
    {
        x = z->right;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->left);
    }
    else
    {
        /* 两个孩子：用右子树最小值 y 顶替 z */
        RBNode *y = min_node(z->right);
        y_orig = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x_parent = y;                  /* x 直接挂在 y 下面 */
            if (x != NULL) x->parent = y;  /* 已有，保险起见 */
        }
        else
        {
            x_parent = y->parent;          /* 记下 y 原来的父亲 */
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;               /* 继承 z 的颜色 */
    }

    /* ② 如果移走的是黑节点，缺口需要补 */
    if (y_orig == BLACK)
        delete_fixup(&root, x, x_parent);

    free(z);
    return root;
}

/* ============================================================
 * 查找 / 遍历 / 释放
 * ============================================================ */

RBNode *rb_find(RBNode *root, int val)
{
    while (root != NULL && root->data != val)
        root = (val < root->data) ? root->left : root->right;
    return root;
}

void rb_dump_inorder(RBNode *n)
{
    if (n == NULL) return;
    rb_dump_inorder(n->left);
    printf("%d(%s) ", n->data, n->color == RED ? "R" : "B");
    rb_dump_inorder(n->right);
}

void rb_destroy(RBNode *n)
{
    if (n == NULL) return;
    rb_destroy(n->left);
    rb_destroy(n->right);
    free(n);
}

/* ============================================================
 * 校验
 * ============================================================ */

static int check_inorder(RBNode *n, int *prev, int *first)
{
    if (n == NULL) return 1;
    if (!check_inorder(n->left, prev, first)) return 0;
    if (!*first && n->data <= *prev) return 0;
    *first = 0;
    *prev = n->data;
    if (!check_inorder(n->right, prev, first)) return 0;
    return 1;
}

int rb_is_bst(RBNode *root)
{
    int prev = 0, first = 1;
    return check_inorder(root, &prev, &first);
}

static int count_black(RBNode *n)
{
    if (n == NULL) return 1;               /* NULL 算一层黑 */
    int l = count_black(n->left);
    int r = count_black(n->right);
    if (l != r || l < 0 || r < 0) return -1;
    return l + (n->color == BLACK ? 1 : 0);
}

int rb_black_height(RBNode *root)
{
    return count_black(root);
}

/* 递归检查：红红相邻、父子指针一致，返回 1 通过 */
static int check_tree(RBNode *n, RBNode *parent)
{
    if (n == NULL) return 1;
    if (n->parent != parent) return 0;
    if (is_red(n) && (is_red(n->left) || is_red(n->right))) return 0;
    return check_tree(n->left, n) && check_tree(n->right, n);
}

int rb_check(RBNode *root)
{
    if (!rb_is_bst(root))            return 0;   /* 性质：BST */
    if (root != NULL && is_red(root)) return 0; /* 性质 2：根黑 */
    if (!check_tree(root, NULL))      return 0; /* 性质 4 + parent */
    if (rb_black_height(root) < 0)    return 0; /* 性质 5 */
    return 1;
}
```

**`main.c`（测试）**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"

static int count_nodes(RBNode *n)
{
    if (n == NULL) return 0;
    return 1 + count_nodes(n->left) + count_nodes(n->right);
}

static int tree_height(RBNode *n)
{
    if (n == NULL) return 0;
    int l = tree_height(n->left), r = tree_height(n->right);
    return (l > r ? l : r) + 1;
}

/* ---------------- 演示 ---------------- */

static void demo(void)
{
    RBNode *root = NULL;
    int vals[] = {10, 20, 30, 15, 25, 5, 1, 40, 50, 35, 45};

    printf("=== 演示：插入 ===\n");
    for (int i = 0; i < (int)(sizeof(vals) / sizeof(vals[0])); i++)
        root = rb_insert(root, vals[i]);

    printf("中序: ");
    rb_dump_inorder(root);
    printf("\n校验: %s  黑高=%d  节点=%d  树高=%d\n\n",
           rb_check(root) ? "OK" : "FAIL",
           rb_black_height(root), count_nodes(root), tree_height(root));

    printf("=== 演示：删除 ===\n");
    int dels[] = {20, 30, 1, 50, 10};
    for (int i = 0; i < (int)(sizeof(dels) / sizeof(dels[0])); i++)
    {
        root = rb_delete(root, dels[i]);
        printf("删 %2d → 中序: ", dels[i]);
        rb_dump_inorder(root);
        printf("\n      校验: %s 黑高=%d 节点=%d\n",
               rb_check(root) ? "OK" : "FAIL",
               rb_black_height(root), count_nodes(root));
    }

    printf("\n删不存在的 999: %s\n",
           rb_delete(root, 999) == root ? "根不变 OK" : "FAIL");

    rb_destroy(root);
}

/* ---------------- 随机测试：插入 + 删除 ---------------- */

static int random_test(void)
{
    srand(20261109);

    for (int round = 0; round < 300; round++)
    {
        RBNode *root = NULL;
        int live[400];
        int nlive = 0;

        for (int step = 0; step < 500; step++)
        {
            if (rand() % 3 != 0)                 /* 2/3 插入 */
            {
                int v = rand() % 300;
                int existed = 0;
                for (int k = 0; k < nlive; k++)
                    if (live[k] == v) { existed = 1; break; }

                int before = count_nodes(root);
                root = rb_insert(root, v);
                if (!existed) live[nlive++] = v;

                int expect = before + (existed ? 0 : 1);
                if (!rb_check(root) || count_nodes(root) != expect)
                {
                    printf("FAIL insert round=%d step=%d v=%d\n", round, step, v);
                    return 0;
                }
            }
            else if (nlive > 0)                  /* 1/3 删除 */
            {
                int idx = rand() % nlive;
                int v = live[idx];
                int before = count_nodes(root);

                root = rb_delete(root, v);
                live[idx] = live[--nlive];

                if (!rb_check(root) || count_nodes(root) != before - 1)
                {
                    printf("FAIL delete round=%d step=%d v=%d\n", round, step, v);
                    return 0;
                }
            }
        }

        /* 一轮结束：把剩下的全部删空，检查能删干净 */
        while (nlive > 0)
        {
            int idx = rand() % nlive;
            int v = live[idx];
            root = rb_delete(root, v);
            live[idx] = live[--nlive];
            if (!rb_check(root)) { printf("FAIL drain\n"); return 0; }
        }
        if (root != NULL) { printf("FAIL not empty\n"); return 0; }

        rb_destroy(root);
    }
    return 1;
}

/* ---------------- 顺序插入 / 顺序删除 ---------------- */

static int sequential_test(void)
{
    RBNode *root = NULL;
    int n = 2000;

    for (int i = 1; i <= n; i++)
        root = rb_insert(root, i);
    if (!rb_check(root)) { printf("FAIL 顺序插入\n"); return 0; }
    printf("顺序插入 1..%d: 树高=%d\n", n, tree_height(root));

    for (int i = 1; i <= n; i++)
    {
        root = rb_delete(root, i);
        if (!rb_check(root)) { printf("FAIL 顺序删除 i=%d\n", i); return 0; }
    }
    if (root != NULL) { printf("FAIL 未删空\n"); return 0; }
    printf("顺序删除 1..%d: 全部通过，树已空\n", n);
    return 1;
}

int main(void)
{
    demo();

    printf("\n=== 随机测试 ===\n");
    if (random_test())
        printf("300 轮 x 500 次混合插入/删除，每步校验五性质 + 节点数：全部通过\n");
    else
        return 1;

    printf("\n=== 顺序测试 ===\n");
    if (!sequential_test()) return 1;

    printf("\n全部测试通过\n");
    return 0;
}
```

**编译运行：**

```
gcc rbtree.c main.c -Wall -Wextra -o rbtree_test
./rbtree_test
```

**实测输出（本机验证）：**

```
=== 演示：插入 ===
中序: 1(R) 5(B) 10(B) 15(B) 20(B) 25(B) 30(B) 35(B) 40(R) 45(R) 50(B) 
校验: OK  黑高=4  节点=11  树高=5

=== 演示：删除 ===
删 20 → 中序: 1(R) 5(B) 10(B) 15(B) 25(B) 30(B) 35(R) 40(B) 45(R) 50(B) 
      校验: OK 黑高=4 节点=10
删 30 → 中序: 1(R) 5(B) 10(B) 15(B) 25(B) 35(B) 40(B) 45(R) 50(B) 
      校验: OK 黑高=4 节点=9
删  1 → 中序: 5(B) 10(B) 15(B) 25(B) 35(B) 40(B) 45(R) 50(B) 
      校验: OK 黑高=4 节点=8
删 50 → 中序: 5(B) 10(B) 15(B) 25(B) 35(B) 40(B) 45(B) 
      校验: OK 黑高=4 节点=7
删 10 → 中序: 5(R) 15(B) 25(B) 35(B) 40(R) 45(B) 
      校验: OK 黑高=3 节点=6

删不存在的 999: 根不变 OK

=== 随机测试 ===
300 轮 x 500 次混合插入/删除，每步校验五性质 + 节点数：全部通过

=== 顺序测试 ===
顺序插入 1..2000: 树高=19
顺序删除 1..2000: 全部通过，树已空

全部测试通过
```

### 10.3 红黑树校验函数说明

`rb_check()` 一次检查四件事，随机测试里每一步都调用：

| 检查 | 对应性质 |
|---|---|
| 中序严格升序 | BST 性质 |
| 根是黑色 | 性质 2 |
| 红色节点的孩子都是黑色 | 性质 4 |
| 每个节点 `parent` 指针正确 | 实现正确性（防旋转写错） |
| 所有路径黑高相等 | 性质 5 |

**建议：** 你自己修改代码后，**先跑 `rb_check()`**，再跑随机测试。
这两层能抓住 99% 的实现错误。

### 10.4 关于你的 `AVLtree` 项目结构的一点建议

你现在用**函数指针 vtable**（每个节点存 5 个函数指针）：
`get_height` / `update_height` / `get_balance` / `dump` / `destroy`。

- ✅ **风格一致性好**，和你 `heap.h`、`cqueue.h` 一致
- ⚠️ 但**每个节点会多出 5 个指针（约 40 字节）**，节点数多时内存翻倍

**建议：** 学习阶段保持现状没坏处。等你想优化时，把这几个函数移到一个"树对象"里
（`AVLTree { AVLNode *root; ...methods... }`），**节点只存数据**，
既保留 OOP 风格，又不浪费内存。这是你以后可以自己尝试的重构。

---

## 第 11 章 学习路线与练习答案

### 11.1 推荐学习顺序

```
第 1 章  BST 复习（你已基本掌握，只做 1.7 的题）
   ↓  确认 BUG：free_tree 必须递归
第 2 章  高度 / 平衡因子（会手算每一种节点的 BF）
   ↓
第 3 章  旋转 ⭐ 本文重点，务必手写一遍 rotate_right / rotate_left
   ↓  用 3.6 的方式验证（中序升序 + 高度正确）
第 4 章  AVL 插入（自己把 rebalance 拼出来）
   ↓
第 5 章  AVL 删除（先能读懂 rebalance 为什么在每个 return 前调用）
   ↓
第 6~8 章  红黑树性质 + 插入（和 AVL 的旋转套路对照着看）
   ↓
第 9 章  红黑树删除（先懂 4 种情况，再抄一遍完整实现，最后用随机测试验证）
```

### 11.2 面试常问的 10 个问题

1. 为什么 BST 会退化？AVL 怎么解决？
2. 什么是平衡因子？AVL 的平衡条件是什么？
3. 四种失衡 LL/LR/RR/RL 分别怎么转？
4. 为什么 LR 要先对左孩子左旋再对根右旋？
5. AVL 插入最多旋转几次？删除呢？为什么不同？
6. 红黑树的五条性质？
7. 为什么新插入节点是红色？
8. 红黑树插入修复分几种情况？叔叔红和叔叔黑分别怎么做？
9. 红黑树为什么最长路径 ≤ 2 倍最短路径？
10. 红黑树删除后什么情况需要修复？四种情况分别怎么做？
11. 红黑树删除时 `x` 为什么可能是 `NULL`？怎么处理？
12. AVL 和红黑树怎么选？

### 11.3 第 1 章答案

1. 中序：`20 30 40 50 60 70 80`
2. 少了 **`malloc` 返回值检查**。`malloc` 失败返回 `NULL`，
   直接 `p->data = v` 就是空指针解引用，程序崩溃。
   正确写法：
   ```c
   if (p == NULL) { perror("malloc"); return NULL; }
   ```
3. 依次插 `10,20,30,40` 会变成一条右斜线（每个都往右挂）：
   ```
   10
     \
      20
       \
        30
         \
          40
   ```
   查找 `40` 要比较 4 次。**这就是退化，需要 AVL 来纠正。**

### 11.4 第 2 章答案

1. 插入 G 作为 D 的左孩子后：
   - **D**：左高 0、右高 −1 → BF = 1，仍平衡
   - **B**：左高 1、右高 1 → BF = 0，平衡
   - **A**：左高 3、右高 0 → BF = 3，**失衡**
   - 实际上 D、B、A 各自都还平衡，**失衡的是 A**（差 3）。
     这说明"某条路径变长了"最终会累积到某个祖先。
2. 用 height 判断：`abs(height(left) - height(right)) <= 1`。
   和 BF 本质等价（BF 就是一个减法）。直接用 `height` 算需要多一步，
   但性能一样，因为都是 `O(1)`。

### 11.5 第 3 章答案

1. `rotate_left`（见第 3.5 节）。
2. 对 `30` 左旋后：
   ```
        50
       /  \
     30    60
       \
       40
   ```
   中序 `30 40 50 60` 升序，BST 没坏。
3. 忘记 `update_height` 时，旋转后节点 height 是**旧的**。
   下一次插入时 `avl_balance` 读到旧高度 → **误判为不平衡或误判为平衡**，
   于是**多转或少转**，树形出错。这种 bug 隐蔽性极强，
   所以要用 3.6 的"每次打印 BF 和 height"去验证。

### 11.6 第 4 章答案

1. 插入 `1..7` 的关键节点（简述）：
   - 插 3 后：`2` 失衡（RR），左旋 → 平衡
   - 插 5、6、7 后，`4` 附近会反复触发 RR 与 RL
   - 最终树高 3，中序 1..7 升序
2. 插 `50,30,70,20,40,60,80,25` 后：
   - `20` 的左孩子 `25` 使 `20` 左高 1 → 仍平衡
   - `30`：左高 2（20→25）、右高 1（40）→ BF = 1
   - `50`：左高 3、右高 2 → BF = 1
   - **整体仍平衡**，没有触发旋转
   （如果想触发，插到 `10` 或 `5` 就失衡了）
3. LR 情况**不能**直接对 root 右旋：右旋后根还是 `z`，
   只是把 `y`、`x` 换了个位置，并没有解决"左边过深"的问题，
   依然满足不了 AVL。**必须先把 `y` 左旋成 LL 形状**，再对 `z` 右旋。

### 11.7 第 5 章答案

1. 删除 `5` 之后 `3` 和 `7` 上提，`1` 和 `8` 仍在。
   子树高度下降后，`10` 可能失衡，按具体 BF 值选择 LL/RR/LR/RL。
2. 删除双孩子节点：`rebalance` 会在**被删节点的每一层递归返回时**都被调用
   （从叶子到根），再加上"去右子树删后继"那一路上经过的节点，
   所以是 **`O(log n)` 次调用**，每次内部可能 O(1) 旋转。
3. 选后继（右子树最小值）：倾向于让**左子树变重**；选前驱则倾向于右子树变重。
   两种都能保持 BST 与平衡性，选哪个取决于实现习惯。
   **AVL 常见做法是用后继。**

### 11.8 第 8 章答案

1. 依次插入 `1,2,3,4,5`：
   - 插 1：根 1(B)
   - 插 2：1(B) → 右 2(R)，父黑，不修
   - 插 3：红红（2R），叔叔黑且一字 RR → 左旋 1，2 变黑，1 变红 → `2(B) 1(R) 3(R)`
   - 插 4：`3(R)` 下挂 `4(R)`，红红，叔叔（1R）是红 → 情况 1：1、3 变黑，2 变红，根 2 染黑
   - 插 5：触发旋转与变色，最终 `2(B) 4(R) 1(B) 3(B) 5(B)`
2. 因为叔叔红时，把父亲和叔叔变黑、爷爷变红，**黑高保持不变**，
   所以不需要旋转就能把"红红"推给爷爷。
   若 `g` 是根，循环结束时 `g` 会被染黑（函数末尾那句）。
3. 黑高守恒——父变黑是 `g` 变红、整条分支重新平衡后的必然结果。

---


### 11.9 第 9 章答案

1. **删除 `15`（红叶子）：** 不需要修复。
   红色节点不贡献黑高，删掉它不影响任何路径的黑高，也不会造成红红相邻（它没有孩子）。
   代码上 `y_orig == RED`，直接跳过 `delete_fixup`。

2. **删除 `10`（黑，只有一个右孩子 `15`）：**
   `x = 15(R)`，`y_orig = BLACK` → **需要进入修复**。
   但循环条件是 `x != root && is_black(x)`，而 `15` 是**红色**，
   所以循环一次都不进，直接执行收尾 `x->color = BLACK`：
   `15` 变黑，补回了被删掉的那层黑。**零旋转、零循环，一步还清。**
   这就是"红色直接染黑"的典型场景。

3. **需要连续上推（情况 2 循环）的例子：**
   当"兄弟是黑、且兄弟两个孩子都是黑"时，`s` 变红、债上移到父亲。
   如果父亲也是黑的，循环继续，可能一路推到根。
   典型场景：删掉一个黑叶子，它的兄弟是黑且没有红孩子。
   **最坏情况下上推 O(log n) 层**（这就是为什么删除比插入麻烦）。

4. **`y->color = z->color` 是必须的：**
   `y` 搬到 `z` 的位置后，它占据了 `z` 原来的"位置"。
   黑高是按**路径上的黑节点数**算的，而 `y` 现在所在的这条路径
   原本经过的是 `z`。只有让 `y` 继承 `z` 的颜色，
   这条路径的黑节点数才和原来一致；否则所有黑高都会错。


## 附录：速查卡

**旋转（AVL，返回新根）**

```c
rotate_right(y):  x=y->left; B=x->right; x->right=y; y->left=B; upd(y); upd(x); return x;
rotate_left(x):   y=x->right; B=y->left; y->left=x; x->right=B; upd(x); upd(y); return y;
```

**四种失衡（AVL）**

```
BF > 1  → 左高：
     leftBF >= 0  → LL → rotate_right(root)
     leftBF <  0  → LR → root->left = rotate_left(root->left); rotate_right(root)
BF < -1 → 右高：
     rightBF <= 0 → RR → rotate_left(root)
     rightBF >  0 → RL → root->right = rotate_right(root->right); rotate_left(root)
```

**红黑树插入修复**

```
叔叔红 → 父、叔变黑，爷爷变红，上移继续
叔叔黑：
   一字型 → 父变黑，爷爷变红，对爷爷旋转 → 结束
   拐弯   → 先对父旋转变成一字型，再按上面处理
```

**红黑树删除修复**（`x` 是顶替节点，`s` 是兄弟；`x` 在左边时）

```
x 是红        → 直接染黑，结束
s 红          → s 黑、父红、对父左旋 → 重取 s
s 黑，两子黑   → s 染红，缺口上推给父，x = 父，继续
s 黑，左红右黑 → s 左子黑、s 红、对 s 右旋 → 重取 s
s 黑，右子红   → s 继承父色、父黑、s 右子黑、对父左旋 → 结束
```

**红黑树五条性质**

```
1. 每个节点非红即黑
2. 根是黑
3. 叶子（NULL）是黑
4. 红节点孩子都黑（无红红相邻）
5. 任一节点到叶子的每条路径黑高相同
```

---

*文档结束。所有代码均已在本机 GCC 16.2.0 实测通过。*





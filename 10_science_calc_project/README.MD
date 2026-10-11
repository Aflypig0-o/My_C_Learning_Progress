# 科学计算器

一个用 C 语言实现的命令行科学计算器，支持中缀表达式求值。

## 项目状态

当前版本：v0.0.2（开发中）

## 功能

### 已实现
- [x] 加减乘除
- [x] 括号优先级
- [x] 一元负号（-3）
- [x] 整数运算
- [x] 浮点数（3.14）
- [x] 多位数（123）

### 计划中
- [ ] 乘方（^）
- [ ] 三角函数（sin/cos/tan）
- [ ] 对数（log/ln）
- [ ] 常量（pi/e）
- [ ] 矩阵运算
- [ ] 复数

## 文件结构

    science_calc/
    ├── main.c           主程序，菜单和交互
    ├── infix.c/h        中缀转后缀
    ├── postfix.c/h      后缀求值
    ├── stack.c/h        整数栈
    ├── charstack.c/h    字符栈
    ├── doublestack.c/h 浮点栈
    ├── tokenizer.c/h    词法分析
    ├── README.md        本文件
    ├── setting.c/h      设置
    ├── file.io c/h      历史计算记录
    |── TODO.md          待办事项
    

## 模块依赖图

    main.c
      ├── infix.c      （中缀转后缀）
      │     └── charstack.c
      └── postfix.c    （后缀求值）
            └── doublestack.c

## 数据流

    用户输入 "3 + 4 * 2"
        │
        ▼
    infix_to_postfix()  →  "3 4 2 * +"
        │
        ▼
    eval_postfix()      →  11.0
        │
        ▼
    输出结果

## 编译

    gcc main.c infix.c postfix.c stack.c charstack.c double_stack.c tokenizer.c -o calc

或用 Makefile：

    mingw32-make
    mingw32-make run

## 使用示例

    $ ./calc
    请输入表达式：3 + 4 * 2
    后缀表达式：3 4 2 * +
    结果：11

    $ ./calc
    请输入表达式：( 1 + 2 ) * 4
    后缀表达式：1 2 + 4 *
    结果：12

## 设计说明

### 为什么用两个栈？
- `charstack` 存运算符（中缀转后缀用）
- `double_stack` 存操作数（后缀求值用）

### 一元负号怎么处理？
- 在 tokenizer 里识别，用一个特殊标记 `~` 表示
- 优先级最高，单目运算

## 已知问题

- 不支持函数（sin/cos 开发中）

## 参考资料

- 中缀转后缀：Dijkstra 的 Shunting-yard 算法
- 后缀求值：逆波兰表达式求值

## 更新日志

### 2026-10-11
- 实现设置界面
- 加入历史记录功能

### 2026-10-10
- 完成基础加减乘除
- 加入一元负号支持
- 开始重构 tokenizer

### 2026-10-08
- 完成整数栈
- 完成字符栈
- 完成基础后缀求值
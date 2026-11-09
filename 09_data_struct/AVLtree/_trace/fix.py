# -*- coding: utf-8 -*-
import io

src = "D:/C/09_data_struct/AVLtree/AVLtree.c"
t = io.open(src, encoding="utf-8", newline="").read().replace("\r\n", "\n")

# 定位 bf < -1 分支里的两处错误调用
i = t.index("if(bf < -1)")
seg = t[i:i + 400]
print("--- 原始片段 ---")
print(seg[:400])

# 修 1: RR 分支应调用 rotate_left
a = "return rotate_right(root);//RR"
assert a in t, "找不到 RR 处"
t = t.replace(a, "return rotate_left(root);//RR")

# 修 2: RL 分支第一步应对右子左旋
b = "root->right = rotate_right(root->right);//RL"
assert b in t, "找不到 RL 处"
t = t.replace(b, "root->right = rotate_left(root->right);//RL")

io.open("D:/C/09_data_struct/AVLtree/_trace/try.c", "w",
        encoding="utf-8", newline="\n").write(t)
print("\n已写 try.c")

# -*- coding: utf-8 -*-
"""基于用户当前源文件，只改 RR 分支一处，然后完整测试。"""
import io

src = "D:/C/09_data_struct/AVLtree/AVLtree.c"
t = io.open(src, encoding="utf-8", newline="").read().replace("\r\n", "\n")

# 只改 RR 分支：return rotate_right(root) -> return rotate_left(root)
old = "return rotate_right(root);//RR"
assert old in t, "找不到 RR 分支"
t = t.replace(old, "return rotate_left(root);//RR")

io.open("D:/C/09_data_struct/AVLtree/_trace/final.c", "w",
        encoding="utf-8", newline="\n").write(t)

# 打印 RL/RR 两个分支
i = t.index("if(bf < -1)")
print(t[i:i + 300])

# -*- coding: utf-8 -*-
import io

src = "D:/C/09_data_struct/AVLtree/_trace/try.c"
t = io.open(src, encoding="utf-8", newline="").read().replace("\r\n", "\n")

old = "root->right = rotate_left(root->right);//RL，左旋，右旋"
new = "root->right = rotate_right(root->right);//RL，先对右子右旋"
assert old in t, "找不到 RL 行"
t = t.replace(old, new)

io.open("D:/C/09_data_struct/AVLtree/_trace/try2.c", "w",
        encoding="utf-8", newline="\n").write(t)
print("已生成 try2.c")
i = t.index("if(bf < -1)")
print(t[i:i+330])

# -*- coding: utf-8 -*-
"""修正文档中两处可以更精确的表述"""
import os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# 直接编辑生成脚本，重新构建
HERE = os.path.dirname(os.path.abspath(__file__))
P1 = os.path.join(HERE, "gen_part1.py")
P2 = os.path.join(HERE, "gen_part2.py")

import io

# 1) 第 6 章对比表：明确"单次删除操作"
t = io.open(P2, encoding="utf-8").read()
old = '''        ["插入代价", "可能旋转多次", "最多 2 次旋转"],
        ["删除代价", "可能旋转 O(log n) 次", "最多 3 次旋转"],'''
new = '''        ["插入代价（单次操作）", "最多 1~2 次旋转", "最多 2 次旋转"],
        ["删除代价（单次操作）", "最坏 O(log n) 次旋转", "最多 3 次旋转"],'''
assert old in t, "第6章对比表未找到"
t = t.replace(old, new)
io.open(P2, "w", encoding="utf-8", newline="\n").write(t)
print("已修正第 6 章对比表")

# 2) 第 0 章对比表同样处理
t1 = io.open(P1, encoding="utf-8").read()
old1 = '''        ["插入代价", "可能旋转多次", "最多 2 次旋转"],
        ["删除代价", "可能旋转 O(log n) 次", "最多 3 次旋转"],'''
if old1 in t1:
    t1 = t1.replace(old1, new)
    io.open(P1, "w", encoding="utf-8", newline="\n").write(t1)
    print("已修正第 0 章对比表")
else:
    print("第 0 章对比表格式不同，检查中")

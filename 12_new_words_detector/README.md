# 新词检测器（New Words Detector）

## 简介

一个用 C 语言编写的命令行工具，用于从英文试卷中自动找出**超出当前词汇水平**的生词。

典型场景：
- 你已经有高考 3500 词的词汇量
- 正在准备四级考试
- 做卷子时想快速知道哪些词是"四级独有的生词"

输入试卷文本，输出一份标注了释义和出现位置的生词表。

## 功能

- 从"大词表"（如四级词汇）中剔除"小词表"（如高考 3500 词）
- 自动切分试卷文本，提取所有英文单词
- 匹配生词，输出单词、释义、所在行号
- 结果保存到文件，方便打印或复习

## 项目结构

    new_words_detector/
    ├── data/                     输入数据
    │   ├── cet4.txt              大词表（四级）
    │   ├── gaokao3500.txt        小词表（高考）
    │   └── exam.txt              试卷文本
    ├── src/                      源代码
    │   ├── main.c                主流程
    │   ├── wordlist.c/h          词表管理
    │   ├── tokenizer.c/h         文本切分
    │   ├── detector.c/h          生词匹配
    │   └── io_utils.c/h          文件与字符串工具
    ├── output/                   输出结果
    │   ├── cet4_only.txt         剔除后的目标词表
    │   └── result.txt            最终生词表
    ├── Makefile                  编译脚本(此由AI完成)
    ├── README.md                 本文件
    └── TODO.md                   待办事项(目前被删掉了)

## 数据文件格式

### 词表文件（cet4.txt / gaokao3500.txt）

每行一个词条，格式为：

    单词  词性. 释义

示例：

    access  v. 获取  n. 接近，入口
    project  n. 工程；课题、作业
    intention  n. 打算，意图

单词和释义之间用空格或制表符分隔。只有"第一段"会被当作单词，后面全部是释义。

### 试卷文本（exam.txt）

普通英文文本，可以包含标点、数字、换行。程序会自动切分出所有连续字母序列作为单词。

示例：

    I have a project to finish.
    My intention is to access the database.
    The apple is red.

## 编译

### 方式 1：Makefile（推荐）

    mingw32-make

生成的 `detector.exe` 位于项目根目录。

### 方式 2：手动编译

    gcc src/main.c src/wordlist.c src/tokenizer.c src/detector.c src/io_utils.c -o detector.exe

## 使用

### 步骤 1：准备数据

把三个文件放到 `data/` 目录：

- `data/cet4.txt`：大词表
- `data/gaokao3500.txt`：小词表
- `data/exam.txt`：试卷文本

### 步骤 2：运行

    cd 12_new_words_detector
    ./detector.exe

**注意**：必须在项目根目录下运行，否则找不到 `data/` 里的文件。

### 步骤 3：查看结果

- `output/cet4_only.txt`：剔除后的目标词表
- `output/result.txt`：最终生词表

`result.txt` 示例：

    共 3 个生词：

    第 1 行  project          n. 工程；课题、作业
    第 2 行  intention        n. 打算，意图
    第 2 行  access           v. 获取  n. 接近，入口

## 设计说明

### 数据流

    data/cet4.txt ─┐
                   ├─→ [剔除] ─→ output/cet4_only.txt ─┐
    data/gaokao.txt┘                                   │
                                                       ├─→ [匹配] ─→ output/result.txt
    data/exam.txt ──→ [切分] ──→ 单词数组 ─────────────┘

### 模块职责

| 模块 | 职责 |
| :--- | :--- |
| `io_utils` | 文件读写、字符串工具（转小写、去空白） |
| `wordlist` | 词表结构、加载、查找、剔除、保存 |
| `tokenizer` | 文本切分，提取所有英文单词并记录行号 |
| `detector` | 匹配生词，记录位置和释义，输出结果 |

### 为什么用线性查找？

词表规模最多几千个词，线性查找（O(n)）足够快。
整个流程约 2000 万次字符串比较，现代 CPU 1 秒内跑完。
不需要哈希表或二分查找。

## 性能

以真实数据测试：

| 项目 | 数量 |
| :--- | :--- |
| 四级词表 | ~4500 |
| 高考词表 | ~3500 |
| 目标词表 | ~1500 |
| 试卷单词 | ~2000 |
| **运行时间** | **< 1 秒** |

## 已知限制

- **不支持词形变化**：试卷里的 `apples` 不会匹配词表里的 `apple`
- **不做去重**：同一个生词出现多次会重复输出
- **只记录行号**：不记录列号（受 UTF-8 中文影响）
- **词表格式固定**：一行一个词条，第一段是单词，其余是释义
- **大小写不敏感**：匹配时全部转小写，但输出的是词表里的原始形式


## 作者

Aflypig0_o

## 日期

2026-10-14
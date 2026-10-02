# ===== 编译器配置 =====
CC = gcc
CFLAGS = -g -Wall -Wextra
TARGET = sq110.exe
SRCS = sq110.c sq110_calc.c
OBJS = $(SRCS:.c=.o)

# ===== 主目标：链接所有 .o =====
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# ===== 模式规则：.c → .o =====
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===== 清理 =====
.PHONY: clean
clean:
	cmd /c "del /Q $(TARGET) $(OBJS) 2>nul"

# ===== 运行 =====
.PHONY: run
run: $(TARGET)
	./$(TARGET)
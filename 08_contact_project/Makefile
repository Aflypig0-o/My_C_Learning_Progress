CC = gcc
CFLAGS = -g -Wall -Wextra -fexec-charset=GBK
TARGET = contact.exe
SRCS = main.c list.c file_io.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)
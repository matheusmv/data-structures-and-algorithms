CC := gcc

CFLAGS := -pedantic-errors -Wall -Werror

SRCS := double_linked_list.c example.c

BIN := example

all: CFLAGS+= -O2
all: relase

debug: CFLAGS+= -O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

clean:
	$(RM) $(BIN)

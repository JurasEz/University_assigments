CC = gcc
CFLAGS = -std=c99
SRCS = test.c main.c
OBJS = $(SRCS:.c=.o)

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o test $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

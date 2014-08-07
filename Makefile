
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CORO = coro.c
CFLAGS += -std=c99 -DCORO_PTHREAD

.PHONY: $(OBJS) $(SRC) $(SRC:.c=)

loop: loop.o loop.c
generator: generator.o generator.c
queue: queue.o queue.c

$(SRC):
	$(CC) $(CFLAGS) $(CORO) $(@:.c=.o) -o $(@:.c=)

$(OBJS):
	$(CC) $(CFLAGS) -c $(@:.o=.c) -o $(@:.c=)

clean:
	rm -f $(OBJS)
	rm -f $(SRC:.c=)

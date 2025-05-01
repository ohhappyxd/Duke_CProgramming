CC = gcc
CFLAGS = -Wall -Werror -std=gnu99

OBJS = deck.o future.o cards.o input.o

test-future: $(OBJS) test-future.o
	$(CC) $(CFLAGS) -o $@ $^

test-future.o: test-future.c deck.h future.h cards.h

test-input: $(OBJS) test-input.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o test-future test-input

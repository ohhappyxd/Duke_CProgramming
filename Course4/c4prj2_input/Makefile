CC = gcc
CFLAGS = -Wall -Werror -std=gnu99

OBJS = test-future.o deck.o future.o cards.o

test-future: $(OBJS)
	$(CC) $(CFLAGS) -o test-future $(OBJS)

test-future.o: test-future.c deck.h future.h cards.h

clean:
	rm -f *.o test-future

.PHONY: clean

rotate.o: rotate.c
	gcc -Wall -Werror -pedantic -std=gnu99 -c -o rotate.o rotate.c

rotate-matrix: rotate.o read-matrix.o
	gcc -o rotate-matrix rotate.o read-matrix.o

clean:
	rm *~ rotate-matrix

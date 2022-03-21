CFLAGS = -ggdb -pedantic -Wextra -Wall -std=c99

store.o: store.c
	cc $(CFLAGS) -c $^ -o $@ 

test: store.o store_test.c
	cc $(CFLAGS) $^ -o $@ 

.PHONY: clean

clean:
	rm *.o test

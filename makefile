CFLAGS = -ggdb -pedantic -Wextra -Wall -std=c99

store.o: store.c
	cc $(CFLAGS) -c $^ -o $@ 

.PHONY: clean

clean:
	rm *.o


CFLAGS =-ggdb -pedantic -Wextra -Wall -std=c99

graph: store.o file.o algorithm.o main.c
	$(CC) $(CFLAGS) $^ -o $@

store.o: store.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

file.o: file.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

algorithm.o: algorithm.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm *.o graph


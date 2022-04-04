CFLAGS =-ggdb -pedantic -Wextra -Wall -std=c99

graph: store.o file.o algorithm.o generator.o main.c
	$(CC) $(CFLAGS) $^ -o $@

test_generator: store.o generator.o testy/test_generator.c
	$(CC) $(CFLAGS) $^ -o $@
	./test_generator 1 3 5 12

test_algorithm: store.o file.o algorithm.o testy/test_algorithm.c
	$(CC) $(CFLAGS) $^ -o $@
	./test_algorithm dane/mygraph 1 3

store.o: store.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

file.o: file.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

algorithm.o: algorithm.c
	$(CC) $(CFLAGS) -c $^ -o $@

generator.o: generator.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm *.o graph test_generator test_algorithm

CFLAGS =-ggdb -pedantic -Wextra -Wall -std=c99 

all: graph 

test_algorithm: store.o file.o algorithm.o testy/test_algorithm.c
	$(CC) $(CFLAGS) $^ -o $@
	./test_algorithm dane/mygraph 1 3

test_generator: store.o generator.o testy/test_generator.c
	$(CC) $(CFLAGS) $^ -o $@
	./test_generator 1 3 5 12 
	 
graph: store.o file.o algorithm.o generator.o main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@


.PHONY: clean

clean:
	rm *.o graph testy/*.o testy/test_generator testy/test_algorithm


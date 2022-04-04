CFLAGS =-ggdb -pedantic -Wextra -Wall -std=c99 

all: graph 
	 
graph: store.o file.o algorithm.o generator.o main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@


.PHONY: clean

clean:
	rm *.o graph testy/*.o


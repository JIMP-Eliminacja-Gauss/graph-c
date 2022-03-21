CFLAGS = -ggdb -pedantic -Wextra -Wall -std=c99

store.o: store.c
	cc $(CFLAGS) -c $^ -o $@ 

file.o: file.c
	cc $(CFLAGS) -c $^ -o $@ 

test_store: store.o test/store_test.c
	cc $(CFLAGS) $^ -o $@ 

test_file: store.o file.o test/file_test.c
	cc $(CFLAGS) $^ -o $@ 

.PHONY: clean

clean:
	rm *.o test_store test_file


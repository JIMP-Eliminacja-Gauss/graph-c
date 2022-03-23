CFLAGS =-ggdb -pedantic -Wextra -Wall -std=c99

store.o: store.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

file.o: file.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

test_store: store.o test/store_test.c
	$(CC) $(CFLAGS) $^ -o $@ 

test_file: store.o file.o test/file_test.c
	$(CC) $(CFLAGS) $^ -o $@ 

.PHONY: clean

clean:
	rm *.o test_store test_file


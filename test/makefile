CFLAGS = -ggdb -pedantic -Wextra -Wall -std=c99

test: algorithmTESTY.o
	cc $(CFLAGS) $^ -o $@

algorithmTESTY.o: algorithmTESTY.c
	cc $(CFLAGS) -c $^ -o $@ -DGRAF1=5

.PHONY: clean

clean:
	rm *.o test


#include "../file.h"
#include <stdio.h>

void print_struct(graph_t graph, int rows, int columns) {
    edge_t temp;

    for (int i = 0; i < rows * columns; i++) {
        fprintf(stdout, "%d. \n", i); 

        temp = graph[i].head;

        while (temp != NULL) {
            fprintf(stdout, "\tvertex index = %d, weight = %.16lf\n",
                    temp -> vertex_index, temp -> weight);
            temp = temp -> next;
        } 
    }

}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: Brakujaca nazwa pliku\n", argv[0]);
        return -1;
    }

    int rows, columns;
    graph_t graph = file_read(argv[1], &rows, &columns);

    print_struct(graph, rows, columns);

    store_free(graph, rows * columns);

    return 0;
}

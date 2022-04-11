#include "../file.h"
#include <stdio.h>

void print_struct(edge_t edge, int rows, int columns) {
    edge_t temp;

    for (int i = 0; i < rows * columns; i++) {
        fprintf(stdout, "Wierzcholek #%d\n", i); 

        temp = edge + i;

        while (temp != NULL) {
            fprintf(stdout, "\t Numer wierzcholka polaczonego = %d, Waga krawedzi = %.16lf\n",
                    temp -> vertex_index, temp -> weight);
            temp = temp -> next;
        } 
        fprintf(stdout, "\n\n");
    }

}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s plik_do_czytania [plik_do_pisania]\n", argv[0]);
        return -1;
    }

    int rows, columns;
    graph_t graph = file_read(argv[1], &rows, &columns);

    print_struct(graph -> edge, rows, columns);

    if (argc == 3)
        file_create (argv[2], graph);

    store_free(graph);

    return 0;
}

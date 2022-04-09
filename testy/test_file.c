#include "../file.h"
#include <stdio.h>

void print_struct(graph_t graph, int rows, int columns) {
    graph_t temp;

    for (int i = 0; i < rows * columns; i++) {
        fprintf(stdout, "Wierzcholek #%d\n", i); 

        temp = graph + i;

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
        fprintf(stderr, "%s: Brakujaca nazwa pliku\n", argv[0]);
        return -1;
    }

    int rows, columns;
    graph_desc_t graph_desc = file_read(argv[1], &rows, &columns);

    print_struct(graph_desc -> graph, rows, columns);

    file_create (argv[2], graph_desc);

    store_free(graph_desc);

    return 0;
}

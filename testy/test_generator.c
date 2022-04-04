#include "../generator.h"
#include "../store.h"
#include <stdio.h>
#include <stdlib.h>


void print_struct (graph_desc_t g) {
    int rows = g->rows;
    int columns = g->columns;
    graph_t graph = g->graph;
    graph_t tmp;

    for (int i = 0; i < rows*columns; i++) {
        fprintf (stdout, "%d. \n", i);
        tmp = &(graph[i]);
        while (tmp != NULL) {
            fprintf (stdout, "\tvertex index = %d, weight = %.16lf\n", tmp->vertex_index, tmp->weight);
            tmp = tmp->next;
        }
    }


}

int main (int argc, char **argv) {
    if (argc < 3) {
        printf ("podano za mało argumentów - liczba_wierszy liczba_kolumn [przedział wag od x [do y]]\n");
        return 1;
    }
    int rows = atoi (argv[1]);
    int columns = atoi (argv[2]);
    if (rows < 1 || columns < 1) {
        printf ("podano złą liczbę wierszy i kolumn - powinna być większa od 0\n");
        return 1;
    }
    double x = argc > 3 ? atof (argv[3]) : 1;
    double y = argc > 4 ? atof (argv[4]) : x + 10;
    double probability = argc > 5 ? atof(argv[5]) : 1;
    if (x > y) {
        printf ("podano zły przedział wag - x powinno być większe od y\n");
        return 1;
    }
    graph_desc_t g;
    g = generate_grid (rows, columns, x, y, probability);
    print_struct (g);
    return 0;
}

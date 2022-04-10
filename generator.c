#include <stdlib.h> 
#include <time.h>

#include "generator.h"

#include "store.h"

static int add_pair(edge_t edge, int vertex_index, int vertex, double weight) {
    if (store_add_edge(edge, vertex_index, weight, vertex) != 0 ||
        store_add_edge(edge, vertex, weight, vertex_index) != 0) 
        return 1; 

    return 0;
}

static int make_connection(double probability) {
    int border = probability * RAND_MAX;
    int value = rand();

    return border >= value ? 1 : 0;
}

graph_t generate_grid(int rows, int columns, double x, double y, double probability) {
    graph_t g = store_init(rows, columns);
    double weight;
    edge_t edge;

    if (g == NULL || g->edge == NULL ) {
        lastError = MEMORY_ERR;
        return NULL;
    }

    edge = g->edge;

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            if (j < columns - 1 && make_connection(probability)) {
                weight = (rand() / (double)RAND_MAX) * (y - x) + x;
                add_pair(edge, i * columns + j, i * columns + j + 1, weight); 
            }

            if (i < rows - 1 && make_connection(probability)) { 
                weight = (rand() / (double)RAND_MAX) * (y - x) + x;
                add_pair(edge, i * columns + j, (i + 1) * columns + j, weight);
            }
        }
    }

    return g;
}

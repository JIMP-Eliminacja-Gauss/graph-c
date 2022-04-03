#include <stdlib.h> 
#include <time.h>

#include "generator.h"

#include "store.h"

static int add_pair(graph_t graph, int vertex_index, int vertex, double weight) {
    if (store_add_edge(graph, vertex_index, weight, vertex) != 0 ||
        store_add_edge(graph, vertex, weight, vertex_index) != 0) 
        return 1; 

    return 0;
}

graph_desc_t generate_grid(int rows, int columns, double x, double y) {
    graph_desc_t g = store_init(rows, columns);
    double weight;
    graph_t graph;

    if (g == NULL || g->graph == NULL ) {
        lastError = MEMORY_ERR;
        return NULL;
    }

    graph = g->graph;

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                weight = (rand() / (double)RAND_MAX) * (y - x) + x;
                add_pair(graph, i * columns + j, i * columns + j + 1, weight);
                
            }

            if (i < rows - 1) { 
                weight = (rand() / (double)RAND_MAX) * (y - x) + x;
                add_pair(graph, i * columns + j, (i + 1) * columns + j, weight);
            }
        }
    }

    return g;
}

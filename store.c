#include "store.h"
int lastError = 0;

#include <stdlib.h>

#define MALLOC_FAILED(PTR, SIZE) ( ((PTR) = malloc(sizeof *(PTR) * (SIZE))) == NULL )

graph_t store_init(int rows, int columns) {
    graph_t new_graph;
    int n_vertices = rows*columns;

    if MALLOC_FAILED(new_graph, 1) {
        lastError = MEMORY_ERR;
        return NULL;
    }

    new_graph->rows = rows;
    new_graph->columns = columns;

    if MALLOC_FAILED(new_graph->edge, n_vertices) {
        lastError = MEMORY_ERR;
        free(new_graph);
        return NULL;
    }

    for (int i = 0; i < n_vertices; i++) {
        new_graph->edge[i].weight = -1;
        new_graph->edge[i].next = NULL;
    } 

    return new_graph; 
}

int store_add_edge(edge_t edge, int vertex_index, double weight, int vertex) {
    edge_t tmp;

    if (edge[vertex].weight == -1) {
        edge[vertex].weight = weight;
        edge[vertex].vertex_index = vertex_index;
        edge[vertex].next = NULL;
        return 0;
    }
    if (edge[vertex].next == NULL) {
        if (MALLOC_FAILED (edge[vertex].next, 1)) { 
            lastError = MEMORY_ERR;
            return 1;
        }

        tmp = edge[vertex].next;
    } else {
        tmp = edge[vertex].next;

        while (tmp->next != NULL)
            tmp = tmp->next;

        if (MALLOC_FAILED (tmp->next, 1)) {
            lastError = MEMORY_ERR;
            return 1; 
        }

        tmp = tmp->next;
    }
    
    tmp->vertex_index = vertex_index;
    tmp->weight = weight;
    tmp->next = NULL;
    return 0;

}

void store_free(graph_t g) {
    edge_t edge = g->edge;
    int n_vertices = g->rows * g->columns;
    edge_t temp;

    for (int i = 0; i < n_vertices; i++) { 
        while (edge[i].next != NULL) {
            temp = edge[i].next;
            edge[i].next = edge[i].next -> next;
            free(temp);
        }
    }

    free(g->edge);
    free(g);
}

void dijkstra_free (dijkstra_t d) {
    free (d);
}

dijkstra_t dijkstra_init (int n_vertices) {
    dijkstra_t d;
    if (MALLOC_FAILED (d, n_vertices)) {
        lastError = MEMORY_ERR;
        return NULL;
    }

    for (int i = 0; i < n_vertices; i++) {
        d[i].shortest_path = 0;
        d[i].last_vertex_index = 0;
    }
    return d;
}

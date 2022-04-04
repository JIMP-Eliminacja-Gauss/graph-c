#include "store.h"
int lastError = 0;

#include <stdlib.h>

#define MALLOC_FAILED(PTR, SIZE) ( ((PTR) = malloc(sizeof *(PTR) * (SIZE))) == NULL )

graph_desc_t store_init(int rows, int columns) {
    graph_desc_t new_graph;
    int n_vertices = rows*columns;

    if MALLOC_FAILED(new_graph, 1) {
        lastError = MEMORY_ERR;
        return NULL;
    }

    new_graph->rows = rows;
    new_graph->columns = columns;

    if MALLOC_FAILED(new_graph->graph, n_vertices) {
        lastError = MEMORY_ERR;
        free(new_graph);
        return NULL;
    }

    for (int i = 0; i < n_vertices; i++) {
        new_graph->graph[i].weight = -1;
        new_graph->graph[i].next = NULL;
    } 

    return new_graph; 
}

int store_add_edge(graph_t graph, int vertex_index, double weight, int vertex) {
    graph_t tmp;

    if (graph[vertex].weight == -1) {
        graph[vertex].weight = weight;
        graph[vertex].vertex_index = vertex_index;
        graph[vertex].next = NULL;
        return 0;
    }
    if (graph[vertex].next == NULL) {
        if (MALLOC_FAILED (graph[vertex].next, 1)) { 
            lastError = MEMORY_ERR;
            return 1;
        }

        tmp = graph[vertex].next;
    } else {
        tmp = graph[vertex].next;

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

void store_free(graph_desc_t g) {
    graph_t graph = g->graph;
    int n_vertices = g->rows * g->columns;
    graph_t temp;

    for (int i = 0; i < n_vertices; i++) { 
        while (graph[i].next != NULL) {
            temp = graph[i].next;
            graph[i].next = graph[i].next -> next;
            free(temp);
        }
    }

    free(g->graph);
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

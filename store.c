#include "store.h"

#include <stdlib.h>

#define MALLOC_FAILED(PTR, SIZE) ( ((PTR) = malloc(sizeof *(PTR) * (SIZE))) == NULL )

graph_t store_init(int n_vertices) {
    graph_t new_graph;

    if MALLOC_FAILED(new_graph, n_vertices) {
        return NULL;
    }

    for (int i = 0; i < n_vertices; i++) {
        new_graph[i].shortest_path = 0;
        new_graph[i].last_vertex_index = i;
        new_graph[i].head = NULL;
    } 

    return new_graph; 
}

edge_t store_init_edge(edge_t head, int vertex_index, double weight) {
    edge_t start_pos = head;

    while (start_pos != NULL) {
        start_pos = start_pos -> next;
    }

    if MALLOC_FAILED(start_pos, 1) {
        return NULL;
    }

    start_pos -> vertex_index = vertex_index;
    start_pos -> weight = weight;
    start_pos -> next = NULL;

    return head;
}

void store_free(graph_t graph, int n_vertices) {
    edge_t temp;
    for (int i = 0; i < n_vertices; i++) {
        while (graph[i].head != NULL) {
            temp = graph[i].head;
            graph[i].head = graph[i].head -> next;
            free(temp);
        }
    }
}

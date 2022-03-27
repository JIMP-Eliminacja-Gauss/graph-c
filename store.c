#include "store.h"

#include <stdlib.h>

#define MALLOC_FAILED(PTR, SIZE) ( ((PTR) = malloc(sizeof *(PTR) * (SIZE))) == NULL )

graph_t store_init(int n_vertices) {
    graph_t new_graph;

    if MALLOC_FAILED(new_graph, n_vertices) {
        return NULL;
    }

    for (int i = 0; i < n_vertices; i++) {
        new_graph[i].weight = -1;
        new_graph[i].next = NULL;
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
        if (MALLOC_FAILED (graph[vertex].next, 1))
            return MEMORY_ERR;
        tmp = graph[vertex].next;
    } else {
        tmp = graph[vertex].next;
        while (tmp->next != NULL)
            tmp = tmp->next;
        if (MALLOC_FAILED (tmp->next, 1))
            return MEMORY_ERR;
        tmp = tmp->next;
    }
    
    tmp->vertex_index = vertex_index;
    tmp->weight = weight;
    tmp->next = NULL;
    return 0;

}

void store_free(graph_t graph, int n_vertices) {
    graph_t temp;
    graph_t temp2;

    for (int i = 0; i < n_vertices; i++) { 
        if (graph[i].next == NULL)
            continue;
        temp = graph[i].next;
        temp2 = temp;
        while (temp != NULL) {
            temp = temp->next;
            free(temp2);
            temp2 = temp;
        }
    }

    free(graph);
}

void dijkstra_free (dijkstra_t d) {
    free (d);
}

dijkstra_t dijkstra_init (int n_vertices) {
    dijkstra_t d;
    if (MALLOC_FAILED (d, n_vertices))
        return NULL;
    for (int i = 0; i < n_vertices; i++) {
        d[i].shortest_path = 0;
        d[i].last_vertex_index = 0;
    }
    return d;
}

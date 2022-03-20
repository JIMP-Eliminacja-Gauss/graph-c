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

        /* alokuje miejsce na strukture przetrzymujaca
         * informacje o pierwszym polaczonym wierzcholku
         * z wierzcholkiem (i) oraz ustawiam jego domyslne 
         * parametry, zeby w funkcji store_init_edge mozna 
         * bylo latwo rozpoznac czy juz cos bylo zapisane 
         * to zmiennej new_graph[i].head
         */

    } 

    return new_graph; 
}

int store_init_edge(edge_t *head, int vertex_index, double weight) {
    if (*head == NULL) {
        if (MALLOC_FAILED(*head, 1)) {
            return MEMORY_ERR;
        }

        (*head) -> vertex_index = vertex_index;
        (*head) -> weight = weight;
        (*head) -> next = NULL;

        return 0;

    }

    edge_t start_pos = *head; 

    while (start_pos -> next != NULL) {
        start_pos = start_pos -> next;
    }

    if MALLOC_FAILED(start_pos -> next, 1) {
        return MEMORY_ERR;
    }

    start_pos = start_pos -> next;

    start_pos -> vertex_index = vertex_index;
    start_pos -> weight = weight;
    start_pos -> next = NULL;

    return 0;
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

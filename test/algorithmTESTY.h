#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

typedef struct przejscia {
    int vertex_index;
    double weight;
    struct przejscia *next;
} *przejscia_t;

typedef struct wierzcholek {
    int last_vertex_index;
    double shortest_path;
    struct przejscia *head;
} *wierzcholek_t;


int bfs (wierzcholek_t graph[], int n, int start_vertex);

void printall (wierzcholek_t graph[], int n, int start_vertex);

#endif

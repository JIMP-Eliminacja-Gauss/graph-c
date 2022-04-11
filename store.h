#ifndef _STORE_H_
#define _STORE_H_

extern int lastError; // definicja w store.c
enum { ARGS_ERR = 1, READ_ERR = 2, WRITE_ERR = 3, MEMORY_ERR = 4, FORMAT_ERR = 5 };

typedef struct edge {
    int vertex_index;
    double weight;
    struct edge *next;
} *edge_t;

typedef struct {
    double shortest_path;
    int last_vertex_index;
} *dijkstra_t;

typedef struct {
    int columns;
    int rows;
    edge_t edge;
} *graph_t;


graph_t store_init(int rows, int columns);

int store_add_edge(edge_t edge, int vertex_index, double weight, int vertex);

void store_free(graph_t g); 

dijkstra_t dijkstra_init (int n_vertices);

#endif

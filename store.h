#ifndef _STORE_H_
#define _STORE_H_

extern int lastError; // definicja w store.c
enum { ARGS_ERR = 1, READ_ERR = 2, WRITE_ERR = 3, MEMORY_ERR = 4, FORMAT_ERR = 5 };

typedef struct graph {
    int vertex_index;
    double weight;
    struct graph *next;
} *graph_t;

typedef struct {
    double shortest_path;
    int last_vertex_index;
} *dijkstra_t;

typedef struct graph_desc {
    int columns;
    int rows;
    graph_t graph;
} *graph_desc_t;


graph_desc_t store_init(int rows, int columns);

int store_add_edge(graph_t graph, int vertex_index, double weight, int vertex);

void store_free(graph_desc_t g); 

void dijkstra_free (dijkstra_t d);

dijkstra_t dijkstra_init (int n_vertices);

#endif

#ifndef _STORE_H_
#define _STORE_H_

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


graph_t store_init(int n_vertices);

int store_add_edge(graph_t graph, int vertex_index, double weight, int vertex);

void store_free(graph_t graph, int n_vertices); 

void dijkstra_free (dijkstra_t d);

dijkstra_t dijkstra_init (int n_vertices);

#endif

#ifndef _STORE_H_
#define _STORE_H_

// to sie wrzuci i tak do maina
enum { ARGS_ERR = 1, READ_ERR, WRITE_ERR, MEMORY_ERR, FORMAT_ERR }; 

typedef struct edge {
    int vertex_index;
    double weight;
    struct edge *next;
} *edge_t;

typedef struct {
    double shortest_path;
    int last_vertex_index;
    edge_t head;
} *graph_t;


graph_t store_init(int n_vertices);

int store_add_edge(edge_t *head, int vertex_index, double weight);

void store_free(graph_t graph, int n_vertices); 

#endif

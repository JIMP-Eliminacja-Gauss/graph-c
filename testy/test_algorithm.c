#include "../algorithm.h"
#include "../store.h"
#include "../file.h"

#include <stdio.h>
#include <stdlib.h>


void print_dijkstra (dijkstra_t d, int n_vertices, int start_vertex) {
    printf ("wierzchołek startowy: %d\n", start_vertex);

    for (int i = 0; i < n_vertices; i++)
        if (i != start_vertex)
            if (d[i].shortest_path != 0)
                printf ("najkrotsza droga do %d = %g\n", i, d[i].shortest_path);

    printf ("\n");
}

int main (int argc, char **argv) {
    if (argc < 4) {
        printf ("pierwszy argument - plik z którego czytamy graf\n");
        printf ("drugi argument - indeks wierzchołka od, którego zaczynamy BFS\n");
        printf ("trzeci argument - indeks wierzchołka od, którego zaczynamy Dijkstre\n");
        return 1;
    }
    
    int rows;
    int columns;
    int bfs_start = atoi (argv[2]);
    int dijkstra_start = atoi (argv[3]);
    
    if (bfs_start < 0 || dijkstra_start < 0) {
        printf ("podane wierzchołki, od których zaczynamy DIJKSTRE/BFS powinny być większe od 0\n");
        return 1;
    }

    dijkstra_t d = NULL;
    graph_t g = file_read (argv[1], &rows, &columns);

    if (g == NULL) {
        fprintf (stderr, "błąd podczas odczytu pliku\n");
        return 1;
    }
    
    if (bfs_start >= g->rows*g->columns || dijkstra_start >= g->rows*g->columns) {
        printf ("podane wierzchołki, od których zaczynamy DIJKSTRE/BFS nie powinny być większe bądź równe liczbie wierzchołków grafu\n");
        return 1;
    }

    if (bfs_start >= 0) {
        if (bfs (g, bfs_start) == 0)
            printf ("graf jest spójny\n");
        else
            printf ("graf nie jest spójny\n");
    } else {
        fprintf (stderr, "podany indeks wierzchołka do bfs powinien być >= 0\n");
    }
    
    if (dijkstra_start >= 0) {
        d = dijkstra (g, dijkstra_start);
        print_dijkstra (d, rows*columns, dijkstra_start);
    } else {
        fprintf (stderr, "podany indeks wierzchołka do dijkstry powinien być >= 0\n");
    }

    store_free (g);
    dijkstra_free (d);
}

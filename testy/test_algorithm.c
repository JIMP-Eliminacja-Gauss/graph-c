#include "../algorithm.h"
#include "../store.h"


#include <stdio.h>
#include <stdlib.h>

void bfs_test (graph_t g, int bfs_start) {
    if (bfs (g, bfs_start) == 0)
        printf ("graf jest spójny\n");
    else
        printf ("graf nie jest spójny\n");
}

int print_d (dijkstra_t d, int n_vertices, int start_vertex) {
    if (d == NULL) {
        printf (";\n");
        return 1;
    }
    printf ("wierzchołek startowy: %d\n", start_vertex);

    for (int i = 0; i < n_vertices; i++)
        if (i != start_vertex)
            if (d[i].shortest_path != 0)
                printf ("najkrotsza droga do %d = %g\n", i, d[i].shortest_path);

    printf ("\n");
    return 0;
}

int main (int argc, char **argv) {
    if (argc < 2) {
        printf ("pierwszy argument - indeks wierzchołka od, którego zaczynamy BFS\n");
        printf ("drugi argument - indeks wierzchołka od, którego zaczynamy Dijkstre\n");
        printf ("trzeci argument - jeżeli podany to wypisujemy najkrósze drogi, a jeżeli nie podany to nie wypisujemy\n");
        return 1;
    }
    /* Trzy grafy 1.Spójny 2.Niespójny 3.Posiadający ujemne wagi krawędzi */
    graph_t g1 = store_init(3,3);
    graph_t g2 = store_init(3,3);
    graph_t g3 = store_init(3,3);

    /* 1 spójny */
    store_add_edge (g1->edge, 1, 5, 0);
    store_add_edge (g1->edge, 3, 1, 0);

    store_add_edge (g1->edge, 0, 5, 1);
    store_add_edge (g1->edge, 2, 1, 1);
    store_add_edge (g1->edge, 4, 2, 1);

    store_add_edge (g1->edge, 1, 1, 2);
    store_add_edge (g1->edge, 5, 6, 2);

    store_add_edge (g1->edge, 0, 1, 3);
    store_add_edge (g1->edge, 4, 1, 3);
    store_add_edge (g1->edge, 6, 3, 3);

    store_add_edge (g1->edge, 1, 2, 4);
    store_add_edge (g1->edge, 3, 1, 4);
    store_add_edge (g1->edge, 5, 1, 4);
    store_add_edge (g1->edge, 7, 10, 4);

    store_add_edge (g1->edge, 2, 6, 5);
    store_add_edge (g1->edge, 4, 1, 5);
    store_add_edge (g1->edge, 8, 1, 5);

    store_add_edge (g1->edge, 3, 3, 6);
    store_add_edge (g1->edge, 7, 2, 6);
    
    store_add_edge (g1->edge, 4, 10, 7);
    store_add_edge (g1->edge, 8, 8, 7);
    store_add_edge (g1->edge, 6, 2, 7);

    store_add_edge (g1->edge, 5, 1, 8);
    store_add_edge (g1->edge, 7, 8, 8);

    /* 2 niespójny - wierzchołek 2 - brak krawędzi */
    store_add_edge (g2->edge, 1, 5, 0);
    store_add_edge (g2->edge, 3, 1, 0);

    store_add_edge (g2->edge, 0, 5, 1);
    store_add_edge (g2->edge, 4, 2, 1);

    store_add_edge (g2->edge, 0, 1, 3);
    store_add_edge (g2->edge, 4, 1, 3);
    store_add_edge (g2->edge, 6, 3, 3);

    store_add_edge (g2->edge, 1, 2, 4);
    store_add_edge (g2->edge, 3, 1, 4);
    store_add_edge (g2->edge, 5, 1, 4);
    store_add_edge (g2->edge, 7, 10, 4);

    store_add_edge (g2->edge, 4, 1, 5);
    store_add_edge (g2->edge, 8, 1, 5);

    store_add_edge (g2->edge, 3, 3, 6);
    store_add_edge (g2->edge, 7, 2, 6);
    
    store_add_edge (g2->edge, 4, 10, 7);
    store_add_edge (g2->edge, 8, 8, 7);
    store_add_edge (g2->edge, 6, 2, 7);

    store_add_edge (g2->edge, 5, 1, 8);
    store_add_edge (g2->edge, 7, 8, 8);

    /* 3 Posiadający ujemne wagi krawędzi */
    store_add_edge (g3->edge, 1, -5, 0);
    store_add_edge (g3->edge, 3, 1, 0);

    store_add_edge (g3->edge, 0, 5, 1);
    store_add_edge (g3->edge, 2, 1, 1);
    store_add_edge (g3->edge, 4, 2, 1);

    store_add_edge (g3->edge, 1, 1, 2);
    store_add_edge (g3->edge, 5, -6, 2);

    store_add_edge (g3->edge, 0, 1, 3);
    store_add_edge (g3->edge, 4, 1, 3);
    store_add_edge (g3->edge, 6, 3, 3);

    store_add_edge (g3->edge, 1, 2, 4);
    store_add_edge (g3->edge, 3, 1, 4);
    store_add_edge (g3->edge, 5, -1, 4);
    store_add_edge (g3->edge, 7, 10, 4);

    store_add_edge (g3->edge, 2, 6, 5);
    store_add_edge (g3->edge, 4, 1, 5);
    store_add_edge (g3->edge, 8, 1, 5);

    store_add_edge (g3->edge, 3, -3, 6);
    store_add_edge (g3->edge, 7, 2, 6);
    
    store_add_edge (g3->edge, 4, 10, 7);
    store_add_edge (g3->edge, 8, 8, 7);
    store_add_edge (g3->edge, 6, 2, 7);

    store_add_edge (g3->edge, 5, 1, 8);
    store_add_edge (g3->edge, 7, 8, 8);

     
    int rows = g1->rows;
    int columns = g1->columns;
    int bfs_start = atoi (argv[1]);
    int dijkstra_start = argc > 2 ? atoi (argv[2]) : -1;
    int dprint = argc > 3 ? 1 : 0; 
    
    if (bfs_start < 0 || dijkstra_start < 0) {
        printf ("podane wierzchołki, od których zaczynamy DIJKSTRE/BFS powinny być większe od 0\n");
        return 1;
    }

    dijkstra_t d1 = NULL;
    dijkstra_t d2 = NULL;
    dijkstra_t d3 = NULL;

    /*if (g == NULL) {
        fprintf (stderr, "błąd podczas odczytu pliku\n");
        return 1;
    }*/
    
    if (bfs_start >= g1->rows*g1->columns || dijkstra_start >= g1->rows*g1->columns) {
        printf ("podane wierzchołki, od których zaczynamy DIJKSTRE/BFS nie powinny być większe bądź równe liczbie wierzchołków grafu\n");
        return 1;
    }

    if (bfs_start >= 0) {
        printf ("GRAF 1\n");
        bfs_test (g1, bfs_start);
        printf ("GRAF 2\n");
        bfs_test (g2, bfs_start);
        printf ("GRAF 3\n");
        bfs_test (g3, bfs_start);
    } else {
        fprintf (stderr, "podany indeks wierzchołka do bfs powinien być >= 0\n");
    }
    
    if (dijkstra_start >= 0) {
        d1 = dijkstra (g1, dijkstra_start);
        if (d1 == NULL)
            printf ("kod błędu dla 1 = %d\n", lastError);
        d2 = dijkstra (g2, dijkstra_start);
        if (d2 == NULL)
            printf ("kod błedu dla 2 = %d\n", lastError);
        d3 = dijkstra (g3, dijkstra_start);
        if (d3 == NULL)
            printf ("kod błedu dla 3 = %d\n", lastError);
        if (dprint == 1) {
            printf ("\n\nGRAF 1\n");
            print_d (d1, rows*columns, dijkstra_start);
            printf ("\n\nGRAF 2\n");
            print_d (d2, rows*columns, dijkstra_start);
            printf ("\n\nGRAF 3\n");
            print_d (d3, rows*columns, dijkstra_start);
        }
    } else if (argc > 3){
        fprintf (stderr, "podany indeks wierzchołka do dijkstry powinien być >= 0\n");
    }

    store_free (g1);
    store_free (g2);
    store_free (g3);
    free (d1);
    free (d2);
    free (d3);
}

#include "file.h"
#include "algorithm.h"
#include "store.h"

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>


char *usage =
    "Aktualnie dostępne opcje:\n"
    "-o nazwa_pliku [-b indeks_wierzcholka] [-p indeks_wierzcholka]\n"
    "   -o nazwa_pliku - nazwa pliku, z którego czytamy graf\n"
    "   -b indeks_wierzchołka - indeks wierzchołka, od którego zaczynamy BFS\n"
    "   -p indeks_wierzchołka - indeks wierzchołka, od którego zaczynamy DIJKSTRE\n"
    "\n"
    "oraz -w nazwa_pliku - czyli wypisanie opisu grafu do podanego pliku\n";

void print_dijkstra (dijkstra_t d, int n_vertices, int start_vertex) {
    printf ("wierzcholek startowy: %d\n", start_vertex);

    for (int i = 0; i < n_vertices; i++)
        if (i != start_vertex)
            printf ("najkrotsza droga do %d = %g\n", i, d[i].shortest_path);

    printf ("\n");
}

void free_filenames (char *writefile, char *readfile) {
    if (writefile != NULL)
        free(writefile);
    if (readfile != NULL)
        free(readfile);
}

int main (int argc, char **argv) {
    int rows = 0;
    int columns = 0;
    double fromX = 0;
    double toY = 0;
    char *writefile = NULL;
    char *readfile = NULL;
    int bfs_start = -1;
    int dijkstra_start = -1;
    int opt;

    graph_t graph = NULL;
    dijkstra_t d = NULL;

    while ((opt = getopt(argc, argv, "r:c:x:y:w:o:b:p:")) != -1) {
        switch (opt) {
        case 'r':
            rows = atoi (optarg);
            break;
        case 'c':
            columns = atoi (optarg);
            break;
        case 'x':
            fromX = atof (optarg);
            break;
        case 'y':
            toY = atof (optarg);
            break;
        case 'w':
            writefile = malloc ((strlen(optarg)+1) * sizeof *(writefile));
            strcpy (writefile, optarg);
            break;
        case 'o':
            readfile = malloc ((strlen(optarg)+1) * sizeof *(readfile));
            strcpy (readfile, optarg);
            break;
        case 'b':
            bfs_start = atoi (optarg);
            break;
        case 'p':
            dijkstra_start = atoi (optarg);
            break;
        default:
            fprintf (stderr, usage, argv[0]);
            return 1;
        }
    }
    if (optind < argc) {
        fprintf (stderr, "\nZłe parametry!\n");
        for (; optind < argc; optind++)
            fprintf (stderr, "\t\"%s\"\n", argv[optind]);
        fprintf (stderr, "\n");
        fprintf (stderr, usage, argv[0]);

        free_filenames (writefile, readfile);
        return ARGS_ERR;
    }

    if (readfile != NULL) {
        graph = file_read (readfile, &rows, &columns);
        if (graph == NULL) {
            fprintf (stderr, "nie mogę czytać z pliku %s\n", readfile);
            free_filenames (writefile, readfile);
            return READ_ERR;
        }
    } else if (rows != 0 && columns != 0 && fromX != 0 && toY != 0) {
        /*if (fromX > toY) {
            fprintf (stderr, "złe parametry - fromX > toY\n");
            return 1;
        }
        struktura_t = generate (rows, columns, fromX, toY);
        if (struktura_t == NULL) {
            fprintf (stderr, "niewystarczająca ilość pamięci\n");
            return 4;
        if (writefile != NULL) {
            if (file_create (writefile, rows, columns, struktura_t) == 1)
                fprintf (stderr, "nie mogę pisać do pliku %s\n", writefile);
        }*/
        fprintf (stderr, "generowanie grafu aktualnie nie dostępne\n");
    } else {
        fprintf (stderr, usage, argv[0]);
        return ARGS_ERR;
    }

    if (writefile != NULL) 
        if (file_create (writefile, rows, columns, graph) == WRITE_ERR)
            fprintf (stderr, "nie mogę pisać do pliku %s\n", writefile);

    if (bfs_start >= 0) {
        if (bfs (graph, rows*columns, bfs_start) == 0)
            printf ("graf jest spójny\n");
        else
            printf ("graf nie jest spójny\n");
    } else if (bfs_start != -1) {
        fprintf (stderr, "podany indeks wierzchołka do bfs powinien być >= 0\n");
    }

    if (dijkstra_start >= 0) {
        d = dijkstra (graph, rows*columns, dijkstra_start);
        print_dijkstra (d, rows*columns, dijkstra_start);
    } else if (dijkstra_start != -1) {
        fprintf (stderr, "podany indeks wierzchołka do dijkstry powinien być >= 0\n");
    }

    store_free (graph, rows*columns);
    dijkstra_free (d);
    free (readfile);
    free (writefile);

    return 0;
}

#include "file.h"
#include "algorithm.h"
#include "store.h"
#include "generator.h"

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>


char *usage =
    "Generowanie grafu\n"
    "Uzycie: %s -r liczba_wierszy -c liczba_kolumn -x waga_od_x -y waga_do_y [-w plik] [-b indeks_wierzcholka] [-p indeks_wierzcholka] [-d prawdopodobienstwo]\n"
    "           <x,y> - przedzial wag wierzcholkow\n"
    "               jezeli plik jest dany to\n"
    "                   wypisuje opis grafu do pliku\n"
    "               jezeli -b indeks_wierzcholka jest dany\n"
    "                   uzywa algorytmu BFS do sprawdzenia czy graf jest spojny zaczynajac od danego wierzcholka\n"
    "               jezeli -p indeks_wierzcholka jest dany\n"
    "                   uzywa algorytmu Dijkstry do znalezienia najkrotszej sciezki od danego wierzcholka do innych\n"
    "               jezeli -d prawdopodobienstwo jest dany\n"
    "                   generuje krawedzie w grafie z podanym prawdopodobienstwem\n"
    
    "\nCzytanie grafu z pliku\n"
    "Uzycie: %s -o plik_czytany [-b indeks_wierzcholka] [-p indeks_wierzcholka]\n";


void print_dijkstra (dijkstra_t d, int n_vertices, int start_vertex) {
    printf ("wierzcholek startowy do dijkstry: %d\n", start_vertex);

    for (int i = 0; i < n_vertices; i++)
        if (i != start_vertex && d[i].shortest_path != 0)   /* bo jak = 0 to z danego wierzchołka źródłowego nie da sie przejsc na ten sprawdzany wierzcholek */
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
    double fromX = 1;
    double toY = 11;
    double probability = 1;
    char *writefile = NULL;
    char *readfile = NULL;
    int bfs_start = -1;
    int dijkstra_start = -1;
    int opt;
    int p_given = 0, toY_given = 0;

    graph_t g = NULL;
    dijkstra_t d = NULL;

    while ((opt = getopt(argc, argv, "r:c:x:y:w:o:b:p:d:")) != -1) {
        switch (opt) {
        case 'r':
            rows = atoi (optarg);
            if (rows < 1) {
                fprintf (stderr, "podana liczba wierszy powinna być większa od 0\n");
                free_filenames (writefile, readfile);
                return ARGS_ERR;
            }
            break;
        case 'c':
            columns = atoi (optarg);
            if (columns < 1) {
                fprintf (stderr, "podana liczba kolumn powinna być większa od 0\n");
                free_filenames (writefile, readfile);
                return ARGS_ERR;
            }
            break;
        case 'x':
            fromX = atof (optarg);
            break;
        case 'y':
            toY_given = 1;
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
            p_given = 1;
            dijkstra_start = atoi (optarg);
            break;
        case 'd':
            probability = atof (optarg);
            break;
        default:
            fprintf (stderr, usage, argv[0], argv[0]);
            free_filenames(readfile, writefile);
            return ARGS_ERR;
        }
    }
    if (optind < argc) {
        fprintf (stderr, "\nZłe parametry!\n");
        for (; optind < argc; optind++)
            fprintf (stderr, "\t\"%s\"\n", argv[optind]);
        fprintf (stderr, "\n");
        fprintf (stderr, usage, argv[0], argv[0]);

        free_filenames (writefile, readfile);
        return ARGS_ERR;
    }

    if (readfile != NULL) {
        g = file_read (readfile, &rows, &columns);
        if (g == NULL) {
            fprintf (stderr, "nie mogę czytać z pliku %s\n", readfile);
            free_filenames (writefile, readfile);
            return READ_ERR;
        }
    } else if (rows != 0 && columns != 0) {     // plik, z którego czytamy nie jest dany i została podana liczba wierszy i kolumn więc generujemy graf
        if (fromX != 1 && toY_given == 0)
            toY = fromX + 10;
        if (fromX > toY) {
            fprintf (stderr, "podano nieprawidłowy przedział wag <x,y> - podane x jest większe od y\n");
            free_filenames (writefile, readfile);
            return ARGS_ERR;
        }

        if (probability > 1 || probability < 0) {
            fprintf(stderr, "Prawdopodobienstwo powinno zostac wybrane z przedzialu <0, 1>\n");
            return ARGS_ERR;
        }

        g = generate_grid(rows, columns, fromX, toY, probability);
        if (g == NULL) 
            return lastError;


        if (writefile != NULL) 
            if (file_create (writefile, g) == WRITE_ERR)
                fprintf (stderr, "nie mogę pisać do pliku %s\n", writefile);

    } else {
        fprintf (stderr, usage, argv[0], argv[0]);
        free_filenames (writefile, readfile);
        return ARGS_ERR;
    } 


    if (bfs_start >= 0 && bfs_start < g->rows*g->columns) {
        if (bfs (g, bfs_start) == 0)
            printf ("graf jest spójny\n");
        else
            printf ("graf nie jest spójny\n");
    } else if (bfs_start != -1) {
        fprintf (stderr, "podany indeks wierzchołka do bfs powinien być większy bądź równy 0 i mniejszy od liczby wierzchołków grafu\n");
    }

    if (dijkstra_start >= 0 && dijkstra_start < g->rows*g->columns) {
        d = dijkstra (g, dijkstra_start);
        if (d != NULL) {
            print_dijkstra (d, rows*columns, dijkstra_start);
        } else if (lastError == MEMORY_ERR) {
            free_filenames (writefile, readfile);
            store_free (g);
            return MEMORY_ERR;
        } else if (lastError == FORMAT_ERR) {
            fprintf (stderr, "wagi krawędzi do Dijkstry powinny być większe od 0\n");
        }
    } else if (p_given == 1) {
        fprintf (stderr, "podany indeks wierzchołka do dijkstry powinien być większy bądź równy 0 i mniejszy od liczby wierzchołków grafu, a początek przedziału\n");
    }

    store_free (g);
    free_filenames (writefile, readfile);
    if (d != NULL)
        free (d);

    return 0;
}

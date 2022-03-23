#include <stdio.h>
#include <ctype.h>

#include "file.h"

graph_t file_read(char *file_name, int *rows, int *columns) {
    /* Format pliku
     Linijka 0: liczba_wierszy liczba_kolumn
     Linijka 1: wierzchołek1 :waga1 wierzchołek2 :waga2 ... wierzchołekn :wagan

     Linijka 1 przetrzymuje polaczenia wierzcholka 0,
     linijka 2 przetrzymuje polaczenia wierzcholka 1,
     linijka n przetrzymuje polaczenia wierzcholka n-1;
    */

    FILE *in = fopen(file_name, "r");
    graph_t graph;
    int line = 0, vertex;
    double weight;

    if (in == NULL) {
        return NULL;
    }

    if (fscanf(in, "%d %d\n", rows, columns) < 2) {
        fclose(in);
        return NULL;
    }

    graph = store_init(*rows * *columns);

    if (graph == NULL) {
        fclose(in);
        return NULL;
    }

    int newline_indicator;
    while (fscanf(in, "%d :%lf", &vertex, &weight) == 2) {
        // Szukam znaku nowej linii
        // Jezeli po wadze bedzie opis kolejnego wierzcholka przesuwam kursor
        // o 1 pozycje w pliku w lewo

        if (store_add_edge( &(graph[line].head), vertex, weight) != 0) {
            return NULL;
        }

        while ( (newline_indicator = fgetc(in)) != EOF && isspace(newline_indicator)) {
            if (newline_indicator == '\n') {
                line++;
            }
        }

        // newline_indicator jest EOF albo nie jest znakiem bialym
        fseek(in, -1, SEEK_CUR);
    }

    fclose(in);

    return graph; 
}

int file_create(char *file_name, int rows, int columns, graph_t graph) {
    FILE *out = fopen (file_name, "w");
    if (out == NULL)
        return 1;
    fprintf (out, "%d %d\n", rows, columns);
    for (int i = 0; i < rows*columns; i++) {
        edge_t tmp = graph[i].head;
        while (tmp != NULL) {
            fprintf (out, "%d :%.16lf ", tmp->vertex_index, tmp->weight);
            tmp = tmp->next;
        }
        fprintf (out, "\n");
    }
    return 0;
}

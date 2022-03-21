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
    char newline_indicator;
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

    while (fscanf(in, "%d :%lf%c", &vertex, &weight, &newline_indicator) == 3) {
        if (store_add_edge( &(graph[line].head), vertex, weight ) != 0) {
            fclose(in);
            return NULL;
        } 

        if (newline_indicator == '\n')
            line++;
        else {
            // to nie jest nowa linia ale moze byc (n) znakow bialych po czym nowa linia
            // nie uzywam newline_indicator bo nie przetrzyma EOF
            int nline;

            while ( (nline = fgetc(in)) != EOF  && isspace(nline) ) {
                if (nline == '\n') 
                    break;
            }

            if (nline == '\n') {
                line++;
            } else {
                fseek(in, -1, SEEK_CUR);
            }
        }
    }

    fclose(in);

    return graph; 
}

int file_create(char *file_name, int rows, int columns, graph_t graph) {
    return 0;
}

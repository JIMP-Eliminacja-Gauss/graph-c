#include <stdio.h>
#include <ctype.h>

#include "file.h"

#include "store.h"

graph_desc_t file_read(char *file_name, int *rows, int *columns) {
    /* Format pliku
     Linijka 0: liczba_wierszy liczba_kolumn
     Linijka 1: wierzchołek1 :waga1 wierzchołek2 :waga2 ... wierzchołekn :wagan

     Linijka 1 przetrzymuje polaczenia wierzcholka 0,
     linijka 2 przetrzymuje polaczenia wierzcholka 1,
     linijka n przetrzymuje polaczenia wierzcholka n-1;
    */

    FILE *in = fopen(file_name, "r");
    graph_desc_t g;
    graph_t graph;
    int line = 0, vertex;
    double weight;

    if (in == NULL) {
        lastError = READ_ERR;
        return NULL;
    }

    if (fscanf(in, "%d %d\n", rows, columns) < 2) {
        fclose(in);
        lastError = FORMAT_ERR;
        return NULL;
    }

    g = store_init(*rows, *columns);

    if (g == NULL) {
        fclose(in);
        lastError = MEMORY_ERR;
        return NULL;
    }
    
    graph = g->graph;

    int newline_indicator;
    while (fscanf(in, "%d :%lf", &vertex, &weight) == 2) {
        // Szukam znaku nowej linii
        // Jezeli po wadze bedzie opis kolejnego wierzcholka przesuwam kursor
        // o 1 pozycje w pliku w lewo

        if (store_add_edge (graph, vertex, weight, line) != 0) {
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

    return g; 
}

int file_create(char *file_name, graph_desc_t g) {
    FILE *out = fopen (file_name, "w");
    graph_t graph = g->graph;
    int n_vertices = g->rows * g->columns;
    if (out == NULL) {
        lastError = WRITE_ERR;
        return 1;
    }

    fprintf (out, "%d %d\n", g->rows, g->columns);
    for (int i = 0; i < n_vertices; i++) {
        if (graph[i].weight == -1) {
            fprintf (out, "\n");
            continue;
        }
        fprintf (out, "%d :%.16lf ", graph[i].vertex_index, graph[i].weight);
        graph_t tmp = graph[i].next;
        while (tmp != NULL) {
            fprintf (out, "%d :%.16lf ", tmp->vertex_index, tmp->weight);
            tmp = tmp->next;
        }
        fprintf (out, "\n");
    }

    fclose (out);

    return 0;
}

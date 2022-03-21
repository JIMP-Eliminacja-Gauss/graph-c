#include <stdio.h>
#include <stdlib.h>

/*
*  0:  1,3
*  1:  0, 2, 4
*  2:  1, 5         LUB W TYM NIESPOJNYM BRAK KRAWEDZI DLA 2 WIERZCHOLKA
*  3:  0, 4, 6
*  4:  1, 3, 5, 7
*  5:  2, 4, 8
*  6:  3, 7
*  7:  4, 6, 8
*  8:  5, 7
*/

/* kolejka od wierzcholka poczatkowego */

typedef struct przejscia {
    int vertex_index;
    double weight;
    struct przejscia *next;
} *przejscia_t;

typedef struct wierzcholek {
    int last_vertex_index;
    double shortest_path;
    struct przejscia *head;
} *wierzcholek_t;



int bfs (wierzcholek_t graph[9], int n, int start_vertex) {
    int visited[n];
    int queue[n];
    int k = 1;
    przejscia_t tmp;

    visited[start_vertex] = 1;
    queue[0] = start_vertex;
    queue[1] = -1;

    for (int i = 0; i < n; i++) {
        if (queue[i] == -1) {
            return 1;
        }
        /*if (k == n)
            return 0;*/
        tmp = graph[queue[i]]->head;
        if (tmp == NULL)
            continue;
        while (tmp != NULL) {
            if (visited[tmp->vertex_index] != 1) {
                visited[tmp->vertex_index] = 1;
                queue[k] = tmp->vertex_index;
                if (k != n-1)
                    queue[k+1] = -1;
                k++;
            }
            /* DIJKSTRA */
            if (graph[tmp->vertex_index]->shortest_path == 0 || graph[tmp->vertex_index]->shortest_path > graph[queue[i]]->shortest_path + tmp->weight) {
                graph[tmp->vertex_index]->shortest_path = graph[queue[i]]->shortest_path + tmp->weight;
                graph[tmp->vertex_index]->last_vertex_index = queue[i];
            }
            /* DIJKSTRA */

            tmp = tmp->next;
        }
    }

    if (k == n)
        return 0;
    else
        return 1;
}


void printall (wierzcholek_t graph[9], int n, int start_vertex) {
    printf ("wierzcholek startowy: %d\n", start_vertex);
    for (int i = 0; i < 9; i++)
        if (i != start_vertex)
            printf ("najkrotsza droga do %d = %g\n", i, graph[i]->shortest_path);
    printf ("\n");
}

int main (int argc, char **argv) {
    if( argc < 2 ) {
        printf ("za malo argumentow\n");
        return 1;
    }
    int start_vertex = atoi (argv[1]);
    wierzcholek_t graph[9];

    for (int i = 0; i < 9; i++) {
        graph[i] = malloc (sizeof(struct wierzcholek));
    }

    /* DLA GRAFU 1 (spojny) */
#ifdef GRAF1
    graph[0]->head = malloc (sizeof(struct przejscia));
    graph[0]->head->vertex_index = 1;
    graph[0]->head->next = malloc (sizeof(struct przejscia));
    graph[0]->head->next->vertex_index = 3;

    graph[0]->head->weight = 5;
    graph[0]->head->next->weight = 1;


    graph[1]->head = malloc (sizeof(struct przejscia));
    graph[1]->head->vertex_index = 0;
    graph[1]->head->next = malloc (sizeof(struct przejscia));
    graph[1]->head->next->vertex_index = 2;
    graph[1]->head->next->next = malloc (sizeof(struct przejscia));
    graph[1]->head->next->next->vertex_index = 4;

    graph[1]->head->weight = 5;
    graph[1]->head->next->weight = 1;
    graph[1]->head->next->next->weight = 2;


    graph[2]->head = malloc (sizeof(struct przejscia));
    graph[2]->head->vertex_index = 1;
    graph[2]->head->next = malloc (sizeof(struct przejscia));
    graph[2]->head->next->vertex_index = 5;

    graph[2]->head->weight = 1;
    graph[2]->head->next->weight = 6;


    graph[3]->head = malloc (sizeof(struct przejscia));
    graph[3]->head->vertex_index = 0;
    graph[3]->head->next = malloc (sizeof(struct przejscia));
    graph[3]->head->next->vertex_index = 4;
    graph[3]->head->next->next = malloc (sizeof(struct przejscia));
    graph[3]->head->next->next->vertex_index = 6;

    graph[3]->head->weight = 1;
    graph[3]->head->next->weight = 1;
    graph[3]->head->next->next->weight = 3;


    graph[4]->head = malloc (sizeof(struct przejscia));
    graph[4]->head->vertex_index = 1;
    graph[4]->head->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->vertex_index = 3;
    graph[4]->head->next->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->next->vertex_index = 5;
    graph[4]->head->next->next->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->next->next->vertex_index = 7;

    graph[4]->head->weight = 2;
    graph[4]->head->next->weight = 1;
    graph[4]->head->next->next->weight = 1;
    graph[4]->head->next->next->next->weight = 10;


    graph[5]->head = malloc (sizeof(struct przejscia));
    graph[5]->head->vertex_index = 2;
    graph[5]->head->next = malloc (sizeof(struct przejscia));
    graph[5]->head->next->vertex_index = 4;
    graph[5]->head->next->next = malloc (sizeof(struct przejscia));
    graph[5]->head->next->next->vertex_index = 8;

    graph[5]->head->weight = 6;
    graph[5]->head->next->weight = 1;
    graph[5]->head->next->next->weight = 1;


    graph[6]->head = malloc (sizeof(struct przejscia));
    graph[6]->head->vertex_index = 3;
    graph[6]->head->next = malloc (sizeof(struct przejscia));
    graph[6]->head->next->vertex_index = 7;

    graph[6]->head->weight = 3;
    graph[6]->head->next->weight = 2;


    graph[7]->head = malloc (sizeof(struct przejscia));
    graph[7]->head->vertex_index = 4;
    graph[7]->head->next = malloc (sizeof(struct przejscia));
    graph[7]->head->next->vertex_index = 6;
    graph[7]->head->next->next = malloc (sizeof(struct przejscia));
    graph[7]->head->next->next->vertex_index = 8;

    graph[7]->head->weight = 10;
    graph[7]->head->next->weight = 2;
    graph[7]->head->next->next->weight = 8;


    graph[8]->head = malloc (sizeof(struct przejscia));
    graph[8]->head->vertex_index = 5;
    graph[8]->head->next = malloc (sizeof(struct przejscia));
    graph[8]->head->next->vertex_index = 7;

    graph[8]->head->weight = 1;
    graph[8]->head->next->weight = 8;


#endif
#ifndef GRAF1
    graph[0]->head = malloc (sizeof(struct przejscia));
    graph[0]->head->vertex_index = 1;
    graph[0]->head->next = malloc (sizeof(struct przejscia));
    graph[0]->head->next->vertex_index = 3;

    graph[1]->head = malloc (sizeof(struct przejscia));
    graph[1]->head->vertex_index = 0;
    graph[1]->head->next = malloc (sizeof(struct przejscia));
    graph[1]->head->next->vertex_index = 4;

    graph[3]->head = malloc (sizeof(struct przejscia));
    graph[3]->head->vertex_index = 0;
    graph[3]->head->next = malloc (sizeof(struct przejscia));
    graph[3]->head->next->vertex_index = 4;
    graph[3]->head->next->next = malloc (sizeof(struct przejscia));
    graph[3]->head->next->next->vertex_index = 6;

    graph[4]->head = malloc (sizeof(struct przejscia));
    graph[4]->head->vertex_index = 1;
    graph[4]->head->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->vertex_index = 3;
    graph[4]->head->next->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->next->vertex_index = 5;
    graph[4]->head->next->next->next = malloc (sizeof(struct przejscia));
    graph[4]->head->next->next->next->vertex_index = 7;

    graph[5]->head = malloc (sizeof(struct przejscia));
    graph[5]->head->vertex_index = 4;
    graph[5]->head->next = malloc (sizeof(struct przejscia));
    graph[5]->head->next->vertex_index = 8;

    graph[6]->head = malloc (sizeof(struct przejscia));
    graph[6]->head->vertex_index = 3;
    graph[6]->head->next = malloc (sizeof(struct przejscia));
    graph[6]->head->next->vertex_index = 7;

    graph[7]->head = malloc (sizeof(struct przejscia));
    graph[7]->head->vertex_index = 4;
    graph[7]->head->next = malloc (sizeof(struct przejscia));
    graph[7]->head->next->vertex_index = 6;
    graph[7]->head->next->next = malloc (sizeof(struct przejscia));
    graph[7]->head->next->next->vertex_index = 8;

    graph[8]->head = malloc (sizeof(struct przejscia));
    graph[8]->head->vertex_index = 5;
    graph[8]->head->next = malloc (sizeof(struct przejscia));
    graph[8]->head->next->vertex_index = 7;
#endif


    if (bfs (graph, 9, start_vertex) == 0)
        printf ("graf spojny\n");
    else
        printf ("graf niespojny\n");

    printall (graph, 9, start_vertex);
    return 0;
}

























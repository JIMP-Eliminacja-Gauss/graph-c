#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"


int bfs (graph_t graph, int n, int start_vertex) {
    int *visited = calloc (n, sizeof *(visited));
    int *queue = calloc (n, sizeof *(queue));    // calloc, bo malloc nie inicjalizuje (nie wypelnia wartosciami poczatkowymi - 0)
    /*int visited[9] = {0};              
    int queue[9] = {0};*/
    int k = 0;
    graph_t tmp;

    visited[start_vertex] = 1;    /* ustawiamy wierzchołek, od którego zaczynamy jako odwiedzony
                                    
                                   *            działanie kolejki:
                                   * kolejka - tablica n elementowa, gdzie n to liczba wierzchołków w grafie
                                   * k - liczba dodanych wierzchołków do kolejki
                                   *
                                   * do kolejki dodajemy wierzchołki, na które możemy przejść 
                                   * z badanego wierzchołka (jeżeli nie zostały już wcześniej odwiedzone)
                                   *
                                   * dodając wierzchołek do kolejki ustawiamy jego indeks na k-ty element kolejki
                                   * oraz k+1 element kolejki ustawiamy jako -1 (jeżeli k+1 nie jest równe n-1)
                                   * i zwiększamy k o jeden
                                   *
                                   * jeżeli aktualnie badany wierzchołek w kolejce (queue[i]) to -1 to znaczy, że
                                   * graf jest niespójny, bo z poprzednio badanego wierzchołka z kolejki (queue[i-1])
                                   * nie było już przejść na żaden jeszcze nieodwiedzony wierzchołek
                                   *
                                   * jeżeli indeksy wszystkich wierzchołków zostały dodane do kolejki
                                   * czyli k = n, to graf spójny
                                  */
    queue[k] = start_vertex;
    if (k != n-1)
        queue[k+1] = -1;
    k++;

    for (int i = 0; i < n; i++) {
        if (queue[i] == -1) {
            free (visited);
            free (queue);
            return 1;
        }
        if (k == n) {
            free (visited);
            free (queue);
            return 0;
        }
        if (graph[queue[i]].weight == -1)
            continue;

        int *ifvisited = &visited[graph[queue[i]].vertex_index];   // jezeli = 1 to wierzchołek, z którym aktualnie badany wierzchołek ma krawędź był już odwiedzony
        if ( *ifvisited != 1) {
            queue[k] = graph[queue[i]].vertex_index;
            if (k != n-1)
                queue[k+1] = -1;
            k++;
            *ifvisited = 1;
        }

        tmp = graph[queue[i]].next;
        while (tmp != NULL) {
            if (visited[tmp->vertex_index] != 1) {
                visited[tmp->vertex_index] = 1;
                queue[k] = tmp->vertex_index;
                if (k != n-1)
                    queue[k+1] = -1;
                k++;
            }
            tmp = tmp->next;
        }
    }

    free (visited);
    free (queue);
    return 0;

}

dijkstra_t dijkstra (graph_t graph, int n, int start_vertex) {
    int *visited = calloc (n, sizeof *(visited));
    int *queue = calloc (n, sizeof *(queue));
    int k = 0;
    graph_t tmp;

    dijkstra_t d = dijkstra_init (n);
    if (d == NULL) {
        free (visited);
        free (queue);
        return NULL;
    }

    visited[start_vertex] = 1;
    queue[k] = start_vertex;
    if (k != n-1)
        queue[k+1] = -1;
    k++;

    for (int i = 0; i < n; i++) {
        if (queue[i] == -1) {
            free (visited);
            free (queue);
            return d;
        }
        if (graph[queue[i]].weight == -1)
            continue;

        if (visited[graph[queue[i]].vertex_index] != 1) {
            queue[k] = graph[queue[i]].vertex_index;
            if (k != n-1)
                queue[k+1] = -1;
            k++;
            visited[graph[queue[i]].vertex_index] = 1;
        }

        /* DIJKSTRA */
        double *edge_vertex_sp = &d[graph[queue[i]].vertex_index].shortest_path;       // sp - shortest_path   długość najkrótszej ścieżki od wierzchołka startowego do wierzchołka, z którym aktualnie
                                                                                       //                      badany wierzchołek ma krawędź

        double *current_vertex_sp = &d[queue[i]].shortest_path;                        // dlugosc najkrotszej sciezki od wierzcholka startowego do aktualnie badanego wierzcholka
        double *edge_weight = &graph[queue[i]].weight;                                 // waga przejścia z aktualnie badanego wierzchołka na wierzchołek, z którym ma krawędź

        int *edge_vertex_lvi = &d[graph[queue[i]].vertex_index].last_vertex_index;     // lvi - last_vertex_index   indeks poprzedniego wierzchołka, z którego wcześniej przeszliśmy na ten wierzchołek, z 
                                                                                       //                           którym aktualnie badany wierzchołek ma krawędź

        if ( (*edge_vertex_sp) == 0 || (*edge_vertex_sp) > (*current_vertex_sp) + (*edge_weight) ) {
            *edge_vertex_sp = (*current_vertex_sp) + (*edge_weight);
            *edge_vertex_lvi = queue[i];
        }
        /* DIJKSTRA */

        tmp = graph[queue[i]].next;
        while (tmp != NULL) {
            if (visited[tmp->vertex_index] != 1) {
                visited[tmp->vertex_index] = 1;
                queue[k] = tmp->vertex_index;
                if (k != n-1)
                    queue[k+1] = -1;
                k++;
            }

            /* DIJKSTRA */
            edge_vertex_sp = &d[tmp->vertex_index].shortest_path;
            current_vertex_sp = &d[queue[i]].shortest_path;
            edge_weight = &tmp->weight;
            edge_vertex_lvi = &d[tmp->vertex_index].last_vertex_index;

            if ( (*edge_vertex_sp) == 0 || (*edge_vertex_sp) > (*current_vertex_sp) + (*edge_weight) ) {
                *edge_vertex_sp = (*current_vertex_sp) + (*edge_weight);
                *edge_vertex_lvi = queue[i];
            }
            /* DIJKSTRA */

            tmp = tmp->next;
        }
    }
    
    free (visited);
    free (queue);
    return d;
}






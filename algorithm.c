#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"

#include "store.h"


int bfs (graph_t g, int start_vertex) {
    edge_t edge = g->edge;
    int n = g->rows * g->columns;  
    int *visited = calloc (n, sizeof *(visited));
    int *queue = calloc (n, sizeof *(queue));    
    int k = 0;
    edge_t tmp;

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
        if (edge[queue[i]].weight == -1 && edge[queue[i]].vertex_index == -1)  // waga -1 i wierzchołek na który przechodzimy z badanego -1 czyli nie ma krawędzi
            continue;

        int current = edge[queue[i]].vertex_index;   // indeks wierzchołka, z którym aktualnie badany wierzchołek ma krawędź - jeżeli nie był odwiedzony to dodajemy do kolejki */
        if (visited[current] != 1) {
            queue[k] = current;
            if (k != n-1)
                queue[k+1] = -1;
            k++;
            visited[current] = 1;
        }

        tmp = edge[queue[i]].next;
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

dijkstra_t dijkstra (graph_t g, int start_vertex) {
    edge_t edge = g->edge;
    int n = g->rows * g->columns;
    int *visited = calloc (n, sizeof *(visited));
    int *queue = calloc (n, sizeof *(queue));
    int k = 0;
    edge_t tmp;

    dijkstra_t d = dijkstra_init (n);
    if (d == NULL) {
        free (visited);
        free (queue);
        lastError = MEMORY_ERR;
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
        if (edge[queue[i]].weight == -1 && edge[queue[i]].vertex_index == -1)
            continue;
        
        int current = edge[queue[i]].vertex_index;
        if (visited[current] != 1) {
            queue[k] = current;
            if (k != n-1)
                queue[k+1] = -1;
            k++;
            visited[current] = 1;
        }


        double *edge_vertex_sp = &d[edge[queue[i]].vertex_index].shortest_path;       // sp - shortest_path   długość najkrótszej ścieżki od wierzchołka startowego do wierzchołka, z którym aktualnie
                                                                                       //                      badany wierzchołek ma krawędź

        double *current_vertex_sp = &d[queue[i]].shortest_path;                        // dlugosc najkrotszej sciezki od wierzcholka startowego do aktualnie badanego wierzcholka
        double *edge_weight = &edge[queue[i]].weight;                                 // waga przejścia z aktualnie badanego wierzchołka na wierzchołek, z którym ma krawędź

        int *edge_vertex_lvi = &d[edge[queue[i]].vertex_index].last_vertex_index;     // lvi - last_vertex_index   indeks poprzedniego wierzchołka, z którego wcześniej przeszliśmy na ten wierzchołek, z 
                                                                                       //                           którym aktualnie badany wierzchołek ma krawędź
        if ( (*edge_weight) <= 0) { // waga krawędzi powinna być większa od 0
            lastError = FORMAT_ERR;
            free (visited);
            free (queue);
            free (d);
            return NULL;
        }

        if ( (*edge_vertex_sp) == 0 || (*edge_vertex_sp) > (*current_vertex_sp) + (*edge_weight) ) {
            *edge_vertex_sp = (*current_vertex_sp) + (*edge_weight);
            *edge_vertex_lvi = queue[i];
        }


        tmp = edge[queue[i]].next;
        while (tmp != NULL) {
            if (visited[tmp->vertex_index] != 1) {
                visited[tmp->vertex_index] = 1;
                queue[k] = tmp->vertex_index;
                if (k != n-1)
                    queue[k+1] = -1;
                k++;
            }

    
            edge_vertex_sp = &d[tmp->vertex_index].shortest_path;
            current_vertex_sp = &d[queue[i]].shortest_path;
            edge_weight = &tmp->weight;
            edge_vertex_lvi = &d[tmp->vertex_index].last_vertex_index;
            
            if ( (*edge_weight) <= 0) {
                lastError = FORMAT_ERR;
                free (visited);
                free (queue);
                free (d);
                return NULL;
            }
            
            if ( (*edge_vertex_sp) == 0 || (*edge_vertex_sp) > (*current_vertex_sp) + (*edge_weight) ) {
                *edge_vertex_sp = (*current_vertex_sp) + (*edge_weight);
                *edge_vertex_lvi = queue[i];
            }
        

            tmp = tmp->next;
        }
    }
    
    free (visited);
    free (queue);
    return d;
}






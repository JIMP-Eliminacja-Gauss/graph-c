#include "../store.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return -2;
    }

    graph_t graph = store_init(atoi(argv[1]));
    srand(time(NULL));

    int j;
    edge_t temp; 
    for (int i = 0; i < atoi(argv[1]); i++) {
        j = rand() % 10 + 1;
        printf("@@@rand_j = %d\n", j);
        while (j--) {
            if (store_init_edge(&(graph[i].head), rand() % atoi(argv[1]), 1) != 0) {
                return -1;
            }
        }

        printf("%d. SPath = %lf, LVIndex = %d\n", i, graph[i].shortest_path, graph[i].last_vertex_index);
        
        temp = graph[i].head;
        while (temp != NULL) {
            printf("\t Vindex = %d\n", temp -> vertex_index);
            temp = temp -> next;
        }
    }

    store_free(graph, atoi(argv[1]));

    return 0; 
}

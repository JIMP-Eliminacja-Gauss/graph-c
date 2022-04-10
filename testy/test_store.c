#include "../store.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return -2;
    }

    graph_t graph = store_init(atoi(argv[1]), atoi(argv[2]));
    srand(time(NULL));

    int j, nr;
    edge_t temp; 
    for (int i = 0; i < atoi(argv[1]) * atoi(argv[2]); i++) {
        j = rand() % 10 + 1;
        printf("@@@ Wylosowana liczba polaczen = %d\n", j);
        while (j--) {
            if (store_add_edge(graph -> edge, rand() % atoi(argv[1]), 1, i) != 0) {
                return -1;
            }
        }

        printf("Wierzcholek #%d:\n", i);

        nr = 1;
        temp = graph -> edge + i; 
        while (temp != NULL) {
            printf("\t %d. Polaczony wierzcholek = %d\n", nr++, temp -> vertex_index);
            temp = temp -> next;
        }
        printf("\n\n");
    }

    store_free(graph);

    return 0; 
}

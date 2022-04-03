#ifndef _FILE_H_
#define _FILE_H_

#include "store.h"

graph_desc_t file_read(char *file_name, int *rows, int *columns);

int file_create(char *file_name, graph_desc_t g);

#endif

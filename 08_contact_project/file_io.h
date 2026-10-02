#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdbool.h>
#include "list.h"

bool list_save_to_file(LinkedList *list,const char *filename);

bool list_load_from_file(LinkedList *list,const char *filename);

#endif
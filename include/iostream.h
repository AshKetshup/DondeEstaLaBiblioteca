#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <stdio.h>
#include "types.h"

int loadfromfile(struct world *, const char *fname);
int savetofile(struct world *, const char *fname);
void save_tree(FILE *, CLIENT_TREE *);

#endif

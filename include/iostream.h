#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <stdio.h>
#include "types.h"

int loadfromfile(struct world *);
int savetofile(struct world *);
void save_tree(FILE *, CLIENT_TREE *);

#endif

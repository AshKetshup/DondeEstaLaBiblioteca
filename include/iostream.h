#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <stdio.h>
#include "types.h"

int loadfromfile(struct world *, const char *);
int savetofile(const struct world *, const char *);

#endif
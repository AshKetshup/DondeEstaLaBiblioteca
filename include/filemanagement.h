#ifndef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

int loadfromfile(struct world *, const char *);
int savetofile(const struct world *, const char *);

// RETURNS ARRAY OF FILES IN DIRECTORY
char** saves_in_dir(const char*, const int, int *);
// ASKS INPUT FOR FILENAME AND CREATES BINARY FILE *.bin
int new_save(void);
// FREES WORLD LISTS EVERY *.bin FILE IN /SAVES GETS WORLD FROM SELECTED SAVE
int open_save(struct world *); 		
// SAVES WORLD INTO OPENED SAVE
int save_save(struct world *);
// FREES WORLD AND EXITS
int leave(struct world *);

#endif
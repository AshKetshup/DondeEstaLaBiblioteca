#ifndef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

int loadfromfile(struct world *, const char *);
int savetofile(struct world *, const char *);

// RETURNS ARRAY OF FILES IN DIRECTORY
char** saves_in_dir(const char*, const int, int *);
// ASKS INPUT FOR FILENAME AND CREATES BINARY FILE *.bin
void new_save(struct world *);
// FREES WORLD LISTS EVERY *.bin FILE IN /SAVES GETS WORLD FROM SELECTED SAVE
void open_save(struct world *); 		
// SAVES WORLD INTO OPENED SAVE
void save_save(struct world *);
// FREES WORLD AND EXITS
int leave(struct world *);

#endif

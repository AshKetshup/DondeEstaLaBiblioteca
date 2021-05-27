#include "iostream.h"
#include <stdio.h>
#include <stdint.h>
#include "types.h"
#include "utils.h"
#include "sism.h"

//------------------------------------------------------------------------------
// FOR DEBUG PURPOSES ONLY
#include <inttypes.h>
#include "debug.h"
//------------------------------------------------------------------------------

int loadfromfile(struct world* w, const char* fname) {
	FILE *f = fopen(fname, "r");

	if (!f)
		return __ERROR_FILE;
	
	// TODO: Ler os dados e Relações


	fclose(f);
}


int loadfromfile(struct world *w, const char *fname) {
	FILE *f = fopen(fname, "w");

	if (!f)
		return __ERROR_FILE;

	// TODO: Escrever os dados e Relações

	fclose(f);
}
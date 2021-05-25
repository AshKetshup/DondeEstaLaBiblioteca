
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "debug.h"




// TODO
void free_list() {}
void free_tree() {}

/* Inicialização da estrutura WORLD. */
void init_world(struct world *w) {
	memset(w, 0, sizeof *w);
}

/* Libertação de recursos da estrutura WORLD 
	TODO: Adaptar para o nosso caso.
*/
void free_world(struct world *w) {
	free_list(w->books);
	free_tree(w->clients);
	free_list(w->orders);
}

// void free_world(struct world *w) {
// 	free(w->uc);
// 	for (uint32_t i = 0; i < w->count.courses; ++i)
// 		free(w->courses[i].uc);
// 	free(w->courses);

// 	for (uint32_t i = 0; i < w->count.professors; ++i)
// 		free(w->professors[i].uc);
// 	free(w->professors);

// 	for (uint32_t i = 0; i < w->count.students; ++i)
// 		free(w->students[i].eval);
// 	free(w->students);
// }


/* Método geral - conversão de date_t para string */
char *datetostr(char *s, date_t date) {
	sprintf(s, "%02" PRIu8 ".%02" PRIu8 ".%04" PRIu16,
		date.day,
		date.month,
		date.year
	);
	return s;
}


const char const *strofdate(date_t date) {
	char s[11];
	sprintf(s, "/%02" PRIu8 "/%02" PRIu8 "%04" PRIu16,
		date.day,
		date.month,
		date.year
	);
	return (const char const *) s;
}



#include "types.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "debug.h"




// TODO
// void free_list() {}
// void free_tree() {}

/* Inicialização da estrutura WORLD. */
void init_world(struct world *w) {
    memset(w, 0, sizeof *w);
}

/* Libertação de recursos da estrutura WORLD 
    TODO: Adaptar para o nosso caso.
*/
void free_world(struct world *w) {
    free_book_list(w->books);
    free_clients_tree(w->clients);
    free_order_queue(w->orders);
}

void free_book_list(BOOK_NODE *v)
{
    BOOK_NODE *aux;
    while (v != NULL)
    {
        aux = v;
        v = v->next;
        free(aux);
    }
}

void free_order_list(ORDER_NODE *v)
{
    ORDER_NODE *aux;
    while (v != NULL)
    {
        aux = v;
        v = v->next;
        free(aux);
    }
}

void free_clients_tree(CLIENT_TREE *c)
{
    if (c == NULL)
        return;
    free_order_list(c->info.buy_history);
    free_clients_tree(c->left);
    free_clients_tree(c->right);
}

void free_order_queue(ORDER_QUEUE *q)
{
    free_order_list(q->head);
}

/* Método geral - conversão de date_t para string */
const char *date_to_str(char *s, date_t date) {
    sprintf(s, "%02" PRIu8 ".%02" PRIu8 ".%04" PRIu16,
        date.day,
        date.month,
        date.year
    );
    return s;
}
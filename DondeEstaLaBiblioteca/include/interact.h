#ifndef INTERACT_H
#define INTERACT_H

#include "types.h"

void tui_show_order(OrderInfo const *const, struct world *);
void tui_set_order(struct world *);

void tui_show_client(ClientInfo const *const, struct world *, int);
void tui_get_client(struct world*);
void tui_set_client(struct world*);
void tui_refresh_client(struct world*, ClientInfo *);

void tui_show_book(BookInfo const *const, struct world *);
void tui_get_book(struct world *);
void tui_set_book(struct world *);
void tui_refresh_book(struct world *, BookInfo *);

#endif
#ifndef INTERACT_H
#define INTERACT_H

#include "types.h"

void tui_show_order(OrderInfo const *const);
void tui_get_order(struct world *);
void tui_set_order(struct world *);
void tui_refresh_order(struct world *);

void tui_show_client(ClientInfo const* const);
void tui_get_client(struct world*);
void tui_set_client(struct world*);
void tui_refresh_client(struct world*);

void tui_show_book(BookInfo const *const);
void tui_get_book(struct world *);
void tui_set_book(struct world *);
void tui_refresh_book(struct world *);

#endif
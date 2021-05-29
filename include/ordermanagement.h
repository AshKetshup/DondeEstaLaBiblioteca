#ifndef ORDERMANAGMENT_H
#define ORDERMANAGMENT_H

#include "types.h"

ORDER_NODE *new_book(OrderInfo *);
int count_books(ORDER_NODE *);

void append_order(ORDER_QUEUE *, OrderInfo *);
void remove_order(ORDER_QUEUE *, uint32_t);

#endif
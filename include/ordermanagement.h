#ifndef ORDERMANAGMENT_H
#define ORDERMANAGMENT_H

#include "types.h"

ORDER_NODE *new_order(OrderInfo *);
int count_orders(ORDER_NODE *);

ORDER_NODE *order_by_id(ORDER_NODE *, uint32_t);

void append_order_node(ORDER_NODE *, OrderInfo *);
void remove_order_node(ORDER_NODE *, uint32_t);

void append_order_queue(ORDER_QUEUE *, OrderInfo *);
void remove_order_queue(ORDER_QUEUE *, uint32_t);

#endif
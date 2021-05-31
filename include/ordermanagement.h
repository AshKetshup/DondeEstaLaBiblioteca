#ifndef ORDERMANAGMENT_H
#define ORDERMANAGMENT_H

#include "types.h"

ORDER_NODE *new_order(OrderInfo *);
int count_orders(ORDER_NODE *);

ORDER_NODE *order_by_id(ORDER_NODE *, uint32_t);

ORDER_NODE *append_order_node(ORDER_NODE *, OrderInfo *);
ORDER_NODE *remove_order_node(ORDER_NODE *, ORDER_NODE *);

ORDER_QUEUE *append_order_queue(ORDER_QUEUE *, OrderInfo *);
ORDER_QUEUE *remove_order_queue(ORDER_QUEUE *);

#endif

#ifndef ORDERMANAGMENT_H
#define ORDERMANAGMENT_H

#include "types.h"

void append_order(ORDER_QUEUE *, OrderInfo);
void remove_order(ORDER_QUEUE *, uint32_t);

#endif
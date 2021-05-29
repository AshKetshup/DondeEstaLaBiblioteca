#include <string.h>
#include "ordermanagement.h"


ORDER_NODE *new_order(OrderInfo *order) {
    ORDER_NODE *node = malloc(sizeof(ORDER_NODE));
    node->info = *order;
    node->next = NULL;
    return node;
}


int count_orders(ORDER_NODE *node) {
    if (node == NULL)
        return 0;
 
    return 1 + count(node->next);
}


void append_order(ORDER_QUEUE *list, OrderInfo *order) {
    ORDER_NODE *node = new_order(order);
    if (list->last == NULL) {
        list->head = list->last = node;
        return;
    }
    list->last = list->last->next = node;
}


void remove_order(ORDER_QUEUE *list) {
    if (list->head == NULL)
        return NULL;
    ORDER_NODE *curr = list->head;
    list->head = list->head->next;
    free(curr);
    return list;
}

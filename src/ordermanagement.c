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
 
    return 1 + count_orders(node->next);
}


ORDER_NODE *order_by_id(ORDER_NODE *node, unsigned id) {
    ORDER_NODE *curr = node;
    while (curr != NULL) {
        if (curr->info.id == id)
            return curr;
    
        curr = curr->next;
    }
    return NULL;    
}


ORDER_NODE *append_order_node(ORDER_NODE *list, OrderInfo *order) {
    ORDER_NODE *node = new_order(order);
    if (list == NULL)
        return node;

    ORDER_NODE *head = list;
    while (list->next != NULL)
        list = list->next;

    list->next = node;
    return head;
}


ORDER_NODE *remove_order_node(ORDER_NODE *head, ORDER_NODE *exclude) {
    if (head == NULL)
        return NULL;

    // Primeiro elemento
    if (head->info.id == exclude->info.id) {
        head = exclude->next;
        free(exclude);
        return head;
    }

    ORDER_NODE *temp = head;
    while (temp->next != NULL) {
        if (temp->next == exclude) {
            temp->next = exclude->next;
            free(exclude);
            break;
        }

        temp = temp->next;
    }

    return head;
}


ORDER_QUEUE *append_order_queue(ORDER_QUEUE *list, OrderInfo *order) {
    ORDER_NODE *node = new_order(order);
    if (list->last == NULL)
        list->head = list->last = node;
    else
        list->last = list->last->next = node;
    
    return list;
}


ORDER_QUEUE *remove_order_queue(ORDER_QUEUE *list) {
    if (list->head == NULL)
        return NULL;
        
    ORDER_NODE *curr = list->head;
    list->head = list->head->next;
    free(curr);

    return list;
}

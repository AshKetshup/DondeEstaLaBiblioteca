#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef enum {
    TBook,
    TOrder
} type_t;

union {
    BookInfo book;
    OrderInfo order;
} data_t;

typedef struct node_t {
    type_t type;
    data_t data;
    struct node_t *next;
} linkedlist;

linkedlist *new_node(data_t);
linkedlist *add_node(linkedlist *, data_t *);


#endif
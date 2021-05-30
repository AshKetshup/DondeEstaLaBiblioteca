#include <stdio.h>
#include "linkedlist.h"
#include "types.h"


// #define make(T)
    typedef struct ##T_n {
        T data;
        struct ##T_n *next;
    } ##T_node

    ##T_node *##T_new_node(T data) {
        linkedlist *node = malloc(T *);
        node->data = data;
        node->next = NULL;
        return node;
    }

    ##T_node *##T_add_node(##T_node *list, T data) {
        if (list == NULL)
            return ##T_new_node(data);
        ##T_node *head = list;
        while (list->next != NULL) {
            list = list->next;
        }
        list->next = ##T_new_node(node);
        return head;
    }

    ##T_node *##T_remove_node(##T_node *head, ##T_node node) {
        ##T_node *indirect = &head;
        while ((*indirect) != node)
            indirect = &(*indirect)->next;
        *indirect = node->next;
        free(node);
    }

    




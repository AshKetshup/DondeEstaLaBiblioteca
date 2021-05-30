#include <string.h>
#include "bookmanagement.h"


BOOK_NODE *new_book(BookInfo *book) {
    BOOK_NODE *node = malloc(sizeof(BOOK_NODE));
    node->info = *book;
    node->next = NULL;
    return node;
}


int count_books(BOOK_NODE *node) {
    if (node == NULL)
        return 0;

    return 1 + count(node->next);
}


BOOK_NODE *book_by_isbn(BOOK_NODE *list, char isbn[ISBNDIM]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.ISBN, isbn))
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_title(BOOK_NODE *list, char title[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strstr(curr->info.title, title))
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_author(BOOK_NODE *list, char author[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.fst_author, author))
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_publisher(BOOK_NODE *list, char publisher[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strstr(curr->info.publisher, publisher))
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_sciarea(BOOK_NODE *list, char sci_area[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.sci_area, sci_area))
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *append_book(BOOK_NODE *list, BookInfo *book) {
    BOOK_NODE *node = new_book(book);
    if (list == NULL)
        return node;

    BOOK_NODE *head = list;
    while (list->next != NULL)
        list = list->next;

    list->next = node;
    return head;
}


BOOK_NODE *remove_book(BOOK_NODE *list, char isbn[ISBNDIM]) {
    if (list == NULL)
        return NULL;

    BOOK_NODE *head = list;
    if (!strcmp(list->info.ISBN, isbn)) {
        head = list->next;
        free(list);
        return head;
    }

    BOOK_NODE *prev = list;
    list = list->next;

    while (list != NULL) {
        if (!strcmp(list->info.ISBN, isbn)) {
            prev->next = list->next;
            free(list);
            break;
        }
        prev = list;
        list = list->next;
    }
    
    return head;
}


BOOK_NODE *edit_book(BOOK_NODE *node, BookInfo *update) {
    if (node == NULL)
        return NULL;
    node->info = *update;
    return node;
}

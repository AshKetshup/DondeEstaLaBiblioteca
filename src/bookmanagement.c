#include <string.h>
#include "bookmanagement.h"


BOOK_NODE *new_book(BookInfo book) {
    BOOK_NODE *node = malloc(sizeof(BOOK_NODE));
    node->info = book;
    node->next = NULL;
    return node;
}


BOOK_NODE *book_by_isbn(BOOK_NODE *list, char isbn[ISBNDIM]) {
    while (list != NULL) {
        if (!strcmp(list->info.isbn, isbn))
            return list;
    }
    return NULL;
}


BOOK_NODE *book_by_title(BOOK_NODE *list, char title[STRMAX]) {
    while (list != NULL) {
        if (strstr(list->info.title, title)) {
            return list;
        }
    }
    return NULL;
}


BOOK_NODE *book_by_author(BOOK_NODE *list, char author[STRMAX]) {
    while (list != NULL) {
        if (!strcmp(list->info.fst_author, author))
            return list;
    }
    return NULL;
}


BOOK_NODE *book_by_publisher(BOOK_NODE *list, char publisher[STRMAX]) {
    while (list != NULL) {
        if (strstr(list->info.publisher, publisher))
            return list;
    }
    return NULL;
}


BOOK_NODE *book_by_sciarea(BOOK_NODE *list, char sci_area[STRMAX]) {
    while (list != NULL) {
        if (!strcmp(list->info.isbn, isbn))
            return list;
    }
    return NULL;
}


BOOK_NODE *append_book(BOOK_NODE *list, BookInfo book) {
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


BOOK_NODE *edit_book(BOOK_NODE *node, BookInfo update) {
    if (node == NULL)
        return NULL;
    node->data = update;
    return node;
}

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

    return 1 + count_books(node->next);
}


int count_books_with_title(BOOK_NODE *b, char *title) {
    int count = 0;

    while (b != NULL) {
        if (strstr(title, b->info.title) != NULL)
            ++count;

        b = b->next;
    }
        
    return count;
}


int count_books_with_author(BOOK_NODE *b, char *author) {
    int count = 0;

    while (b != NULL) {
        if ((strcmp(b->info.fst_author, author) == 0) || (strcmp(b->info.snd_author, author) == 0))
            ++count;

        b = b->next;
    }
        
    return count;
}


int count_books_from_year(BOOK_NODE *b, int year) {
    int count = 0;

    while (b != NULL) {
        if (b->info.year == year)
            ++count;

        b = b->next;
    }
        
    return count;
}


int count_books_with_publisher(BOOK_NODE *b, char *publisher) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.publisher, publisher) == 0)
            ++count;

        b = b->next;
    }
        
    return count;
}


int count_books_with_sciarea(BOOK_NODE *b, char *area) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.sci_area, area) == 0)
            ++count;

        b = b->next;
    }
        
    return count;
}


void add_books_with_title(BOOK_NODE *b, BOOK_NODE **array, const char *title) {
    int count = 0;

    while (b != NULL) {
        if (strstr(b->info.title, title) != NULL) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}


void add_books_with_author(BOOK_NODE *b, BOOK_NODE **array, const char *author) {
    int count = 0;

    while (b != NULL) {
        if ((strcmp(b->info.fst_author, author) == 0) || (strcmp(b->info.snd_author, author) == 0)) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}


void add_books_from_year(BOOK_NODE *b, BOOK_NODE **array, const int year) {
    int count = 0;

    while (b != NULL) {
        if (b->info.year == year) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}


void add_books_with_publisher(BOOK_NODE *b, BOOK_NODE **array, const char *publisher) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.publisher, publisher) == 0) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}


void add_books_with_sciarea(BOOK_NODE *b, BOOK_NODE **array, const char *sciarea) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.sci_area, sciarea) == 0) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}




BOOK_NODE *book_by_isbn(BOOK_NODE *list, const char isbn[ISBNDIM]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strcmp(curr->info.ISBN, isbn) == 0)
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_title(BOOK_NODE *list, const char title[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strstr(curr->info.title, title) != NULL)
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_author(BOOK_NODE *list, const char author[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strcmp(curr->info.fst_author, author) == 0)
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_publisher(BOOK_NODE *list, const char publisher[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strcmp(curr->info.publisher, publisher) == 0)
            return curr;

        curr = curr->next;
    }
    return NULL;
}


BOOK_NODE *book_by_sciarea(BOOK_NODE *list, const char sci_area[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strcmp(curr->info.sci_area, sci_area) == 0)
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


BOOK_NODE *remove_book(BOOK_NODE *list, const char isbn[ISBNDIM]) {
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

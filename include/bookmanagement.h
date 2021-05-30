#ifndef BOOKMANAGMENT_H
#define BOOKMANAGMENT_H

#include "types.h"

BOOK_NODE *new_book(BookInfo *);
int count_books(BOOK_NODE *);
int count_books_with_title(BOOK_NODE *, char [STRMAX]);
int count_books_with_author(BOOK_NODE *, char [STRMAX]);
int count_books_from_year(BOOK_NODE *, int);
int count_books_with_publisher(BOOK_NODE *, char [STRMAX]);
int count_books_with_area(BOOK_NODE *, char [STRMAX]);

void add_books_with_title(BOOK_NODE *, BOOK_NODE **, const char *);
void add_books_with_author(BOOK_NODE *, BOOK_NODE **, const char *);
void add_books_from_year(BOOK_NODE *, BOOK_NODE **, const int);
void add_books_with_publisher(BOOK_NODE *, BOOK_NODE **, const char *);
void add_books_with_area(BOOK_NODE *, BOOK_NODE **, const char *);

BOOK_NODE *book_by_isbn(BOOK_NODE *, const char [ISBNDIM]);
BOOK_NODE *book_by_title(BOOK_NODE *, const char [STRMAX]);
BOOK_NODE *book_by_author(BOOK_NODE *, const char [STRMAX]);
BOOK_NODE *book_by_year(BOOK_NODE *, const uint16_t);
BOOK_NODE *book_by_publisher(BOOK_NODE *, const char[STRMAX]);
BOOK_NODE *book_by_sciarea(BOOK_NODE *, const char[STRMAX]);

BOOK_NODE *append_book(BOOK_NODE *, BookInfo *);
BOOK_NODE *remove_book(BOOK_NODE *, const char[ISBNDIM]);
BOOK_NODE *edit_book(BOOK_NODE *, BookInfo *);

#endif
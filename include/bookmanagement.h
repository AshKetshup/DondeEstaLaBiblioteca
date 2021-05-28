#ifndef BOOKMANAGMENT_H
#define BOOKMANAGMENT_H

#include "types.h"

BOOK_NODE *book_by_isbn(BOOK_NODE *, char [ISBNDIM]);
BOOK_NODE *book_by_title(BOOK_NODE *, char [STRMAX]);
BOOK_NODE *book_by_author(BOOK_NODE *, char [STRMAX]);
BOOK_NODE *book_by_publisher(BOOK_NODE *, char [STRMAX]);
BOOK_NODE *book_by_sciarea(BOOK_NODE *, char [STRMAX]);

BOOK_NODE *append_book(BOOK_NODE *, BookInfo );
BOOK_NODE *remove_book(BOOK_NODE *, char [ISBNDIM]);
BOOK_NODE *edit_book(BOOK_NODE *, BookInfo );


#endif
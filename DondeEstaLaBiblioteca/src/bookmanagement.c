#include <string.h>
#include "bookmanagement.h"

//criar novo livro
BOOK_NODE *new_book(BookInfo *book) {
    BOOK_NODE *node = malloc(sizeof(BOOK_NODE));
    node->info = *book;
    node->next = NULL;
    return node;
}

//Contador de Livros
int count_books(BOOK_NODE *node) {
    if (node == NULL)
        return 0;

    return 1 + count(node->next);
}

//Contador de Livros com um dado Titulo
int count_books_with_title(BOOK_NODE *b, char *title) {
    int count = 0;

    while (b != NULL) {
        if (strstr(title, b->info.title) != NULL)
            ++count;

        b = b->next;
    }
        
    return count;
}

//Contador de Livros com um dado Autor
int count_books_with_author(BOOK_NODE *b, char *author) {
    int count = 0;

    while (b != NULL) {
        if ((strcmp(b->info.fst_author, author) == 0) || (strcmp(b->info.snd_author, author) == 0))
            ++count;

        b = b->next;
    }
        
    return count;
}

//Contador de Livros de um dado ano de publicação
int count_books_from_year(BOOK_NODE *b, int year) {
    int count = 0;

    while (b != NULL) {
        if (b->info.year == year)
            ++count;

        b = b->next;
    }
        
    return count;
}

//Contador de Livros com uma dada Editora
int count_books_with_publisher(BOOK_NODE *b, char *publisher) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.publisher, publisher) == 0)
            ++count;

        b = b->next;
    }
        
    return count;
}

//Contador de Livros com uma dada Área Científica
int count_books_with_sciarea(BOOK_NODE *b, char *area) {
    int count = 0;

    while (b != NULL) {
        if (strcmp(b->info.sci_area, area) == 0)
            ++count;

        b = b->next;
    }
        
    return count;
}

//Controi um Array de BOOK_NODES com um dado Titulo
void add_books_with_title(BOOK_NODE *b, BOOK_NODE **array, char *title) {
    int count = 0;

    while (b != NULL) {
        if (strstr(title, b->info.title) != NULL) {
            array[count] = b;
            ++count;
        }

        b = b->next;
    }

    return;
}

//Controi um Array de BOOK_NODES com um dado Autor
void add_books_with_author(BOOK_NODE *b, BOOK_NODE **array, char *author) {
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

//Controi um Array de BOOK_NODES com um dado Ano de Publicação
void add_books_with_year(BOOK_NODE *b, BOOK_NODE **array, int year) {
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

//Controi um Array de BOOK_NODES com uma dada Editora
void add_books_with_publisher(BOOK_NODE *b, BOOK_NODE **array, char *publisher) {
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

//Controi um Array de BOOK_NODES com uma dada Area Científica
void add_books_with_sciarea(BOOK_NODE *b, BOOK_NODE **array, char *sciarea) {
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



//PEsquisa os Livros por ISBN
BOOK_NODE *book_by_isbn(BOOK_NODE *list, char isbn[ISBNDIM]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.ISBN, isbn))
            return curr;

        curr = curr->next;
    }
    return NULL;
}

//PEsquisa os Livros por Titulo
BOOK_NODE *book_by_title(BOOK_NODE *list, char title[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strstr(curr->info.title, title))
            return curr;

        curr = curr->next;
    }
    return NULL;
}

//PEsquisa os Livros por Autor
BOOK_NODE *book_by_author(BOOK_NODE *list, char author[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.fst_author, author))
            return curr;

        curr = curr->next;
    }
    return NULL;
}

//PEsquisa os Livros por Editora
BOOK_NODE *book_by_publisher(BOOK_NODE *list, char publisher[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (strstr(curr->info.publisher, publisher))
            return curr;

        curr = curr->next;
    }
    return NULL;
}

//PEsquisa os Livros por Área Científica
BOOK_NODE *book_by_sciarea(BOOK_NODE *list, char sci_area[STRMAX]) {
    BOOK_NODE *curr = list;
    while (curr != NULL) {
        if (!strcmp(curr->info.sci_area, sci_area))
            return curr;

        curr = curr->next;
    }
    return NULL;
}

//Inserir Livro
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

// Inserir livro ordenando por ISBN
BOOK_NODE *append_sorted_books(BOOK_NODE *list, BookInfo *book) {
    BOOK_NODE *node = new_book(book);
    if (list == NULL)
        return node;
    BOOK_NODE *head = list;    
    while (list->next != NULL && ((int)(node->info.isbn)<(int)(list->next->info.isbn)))
        list = list->next;
    node->next = list->next;    
    list->next = node;
    return head;
}
 //Ordenar a lista de livros por ISBN
BOOK_NODE *sort_books(BOOK_NODE *list) {
   BOOK_NODE *head = list;    
   while (list!=NULL){
        BOOK_NODE *head2 = list->next, AUX;    
        while (head2!=NULL){
            if((int)(list->info.isbn)>(int)(list->info.isbn)){
            AUX = list->next;
            list->next = head2->next;
            head2->next = AUX;
            }
            head2 = head2->next;
        }
    list =list->next;
   }
}

//Remover LIvro
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

//Alterar Livro
BOOK_NODE *edit_book(BOOK_NODE *node, BookInfo *update) {
    if (node == NULL)
        return NULL;
    node->info = *update;
    return node;
}

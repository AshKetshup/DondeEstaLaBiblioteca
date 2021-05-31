#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include "ordermanagement.h"
#include "bookmanagement.h"
#include "clientmanagement.h"
#include "interact.h"
#include "utils.h"
#include "tui.h"
#include "input.h"
#include "types.h"


// ENCOMENDA
void tui_show_order(OrderInfo const *const order, struct world *w) {
    if (order != NULL) {
        char s[11];

        tui_title("\t           ENCOMENDA");
        tui_write("\t             ID: %" PRIu32 "\n", order->id);
        tui_write("\t     Quantidade: %" PRIu16 "\n", order->amount);
        tui_write("\t    Preço Total: %f\n",          order->total_price);
        tui_write("\t    Efetuada em: %s\n",          date_to_str(s, order->date));

        tui_show_book(&(book_by_isbn(w->books, order->ISBN)->info));
        tui_show_client(&(client_by_nif(w->clients, order->NIF)->info), w, 0);
    }

    return;
}


void tui_set_order(struct world *w) {
    tui_title("CRIAR ENCOMENDA");
    OrderInfo new;
    int count;
    srand(time(NULL));

    // Gera um ID
    do
        new.id = (uint32_t) (rand() / ((float) RAND_MAX / UINT32_MAX));
    while (order_by_id(w->orders->head, new.id) != NULL);

    // Pede ISBN
    BOOK_NODE *book;
    do {
        if (prompt_string("Insira ISBN: ", new.ISBN, ISBNDIM) == 0)
            return;
        
        book = book_by_isbn(w->books, new.ISBN);
        if (book == NULL)
            tui_write_error("Livro com o ISBN %s não existe.\n", new.ISBN);
    } while (book == NULL);

    new.total_price = book->info.price;

    // Pede quantidade
    count = 0;
    int amount, n;
    amount = n = prompt_id("Insira quantidade: ");
    while (n != 0) {
        n /= 10;     // n = n/10
        ++count;
    }
    
    if (count == 0)
        return;
    new.amount = amount; 

    // Calcula preço
    new.total_price *= new.amount;

    // Obtem a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    new.date.day = tm.tm_mday;
    new.date.month = tm.tm_mon + 1;
    new.date.year = tm.tm_year + 1900;

    // Pede NIF
    count = 0;
    uint32_t nif;
    do {
        uint32_t n;
        nif = n = prompt_uint32("Insira o NIF: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0)
            return;
        if (count != 9)
            tui_write_error("NIF não valido.");
    } while (count != 9);
    new.NIF = nif;

    // Atualiza cliente
    append_order_node(client_by_nif(w->clients, new.NIF)->info.buy_history, &new);

    // Atualiza Geral
    append_order_queue(w->orders, &new);
    return;
}


void tui_del_order(struct world *w) {
    remove_order_queue(w->orders);
    tui_write("Proxima encomenda na fila apagada");
    return;
}

// LIVRO
void tui_show_book(BookInfo const *const book) {
    if (book != NULL) {
        tui_title("\t               LIVRO");
        tui_write("\t             ISBN: %s\n",     book->ISBN);
        tui_write("\t           Titulo: %s\n",     book->title);
        tui_write("\t        Autor(es): %s, %s\n", book->fst_author, book->snd_author);
        tui_write("\t          Editora: %s\n",     book->publisher);
        tui_write("\tAno de lançamento: %d\n",     book->year);
        tui_write("\t  Area Cientifica: %s\n",     book->sci_area);
        tui_write("\t           Idioma: %s\n",     book->idiom);
        tui_write("\t            Stock: %d\n",     book->stock_amount);
        tui_write("\t            Preço: %f\n",     book->price);
    }

    return;
}


void tui_get_book(struct world *w) {
    struct item menu[] = {
        {.text = "Pesquisar por ISBN", .func = NULL},
        {.text = "Pesquisar por Titulo", .func = NULL},
        {.text = "Pesquisar por Autor", .func = NULL},
        {.text = "Pesquisar por Ano de Publicação", .func = NULL},
        {.text = "Pesquisar por Editora", .func = NULL},
        {.text = "Pesquisar por Área Cientifica", .func = NULL},
        {.text = "VOLTAR", .func = NULL},
        {.text = NULL, .func = NULL}};

    int opt;
    do {
        println();
        tui_title("CONSULTA DE CLIENTES");
        show_menu(menu);
        exec_menu(w, menu, &opt, "Opção?");

        switch (opt) {
        // Pesquisar por isbn
            case 0: {
                char isbn[ISBNDIM];
                prompt_string("ISBN a pesquisar: ", isbn, ISBNDIM);
                if (strlen(isbn) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    BOOK_NODE *ptr = book_by_isbn(w->books, isbn);
                    if (ptr != NULL)
                        tui_show_book(&(ptr->info));
                    else
                        tui_write("Não existe livro com ISBN '%s'.\n", isbn);
                }
                break;
            }

            // Pesquisar por titulo
            case 1: {
                char titulo[STRMAX];
                if (prompt_string("Titulo a pesquisar: ", titulo, STRMAX) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int bookswithtitle = count_books_with_title(w->books, titulo);
                    if (bookswithtitle != 0) {
                        BOOK_NODE *ptr[bookswithtitle];
                        add_books_with_title(w->books, ptr, titulo);
                        for (int i = 0; i < bookswithtitle; i++)
                            tui_show_book(&(ptr[i]->info));
                    }
                    else
                        tui_write("Não existe livro com titulo '%s'.\n", titulo);
                }
                break;
            }

            case 2: {
                char autor[STRMAX];
                if (prompt_string("Autor a pesquisar: ", autor, STRMAX) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int bookswithauthor = count_books_with_author(w->books, autor);
                    if (bookswithauthor != 0) {
                        BOOK_NODE *ptr[bookswithauthor];
                        add_books_with_author(w->books, ptr, autor);
                        for (int i = 0; i < bookswithauthor; i++)
                            tui_show_book(&(ptr[i]->info));
                    }
                    else
                        tui_write("Não existe livro com autor '%s'.\n", autor);
                }
                break;
            }

            // Pesquisar por numero
            case 3: {
                int count = 0;
                uint16_t year, n;
                year = n = prompt_id("Ano a pesquisar: ");
                while (n != 0) {
                    n /= 10; // n = n/10
                    ++count;
                }

                if (count != 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int booksfromyear = count_books_from_year(w->books, year);
                    if (booksfromyear != 0) {
                        BOOK_NODE *ptr[booksfromyear];
                        add_books_from_year(w->books, ptr, year);
                        for (int i = 0; i < booksfromyear; i++)
                            tui_show_book(&(ptr[i]->info));
                    }
                    else
                        tui_write("Não existe cliente com numero '%d'.\n", year);
                }
                break;
            }

            case 4: {
                char editora[STRMAX];
                if (prompt_string("Editora a pesquisar: ", editora, STRMAX) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int bookswithpublisher = count_books_with_publisher(w->books, editora);
                    if (bookswithpublisher != 0) {
                        BOOK_NODE *ptr[bookswithpublisher];
                        add_books_with_publisher(w->books, ptr, editora);
                        for (int i = 0; i < bookswithpublisher; i++)
                            tui_show_book(&(ptr[i]->info));
                    }
                    else
                        tui_write("Não existe livro com editora '%s'.\n", editora);
                }
                break;
            }

            case 5: {
                char area[STRMAX];
                if (prompt_string("Área virtual a pesquisar: ", area, STRMAX) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int bookswitharea = count_books_with_sciarea(w->books, area);
                    if (bookswitharea != 0) {
                        BOOK_NODE *ptr[bookswitharea];
                        add_books_with_sciarea(w->books, ptr, area);
                        for (int i = 0; i < bookswitharea; i++)
                            tui_show_book(&(ptr[i]->info));
                    }
                    else
                        tui_write("Não existe livro com área cientifica '%s'.\n", area);
                }
                break;
            }
        }
    } while (opt != size_menu(menu) - 1);
    
}


void tui_set_book(struct world *w) {
    tui_title("CRIAR LIVRO");
    BookInfo new;
    BOOK_NODE *book;

    // Pede ISBN
    int len;
    do {
        len = prompt_string("Insira ISBN: ", new.ISBN, ISBNDIM);
        if (len == 0)
            return;

        book = book_by_isbn(w->books, new.ISBN);
        if (book != NULL)
            tui_write_error("Livro com o ISBN %s já existe.\n", new.ISBN);

        if (len != 14)
            tui_write_error("ISBN invalido.\n");
    } while (book != NULL && len != 14);
    

    // Pede titulo
    do {
        if (prompt_string("Insira titulo: ", new.title, STRMAX) == 0)
            return;

        book = book_by_title(w->books, new.title);
    } while (book != NULL);

    // Pede autor(es)
    {
        char author1[STRMAX];
        if (prompt_string("Insira autor: ", author1, STRMAX) == 0)
            return;
        strcpy(new.fst_author, author1);
        
        char author2[STRMAX];
        if (prompt_string("(opcional) Insira 2º autor: ", author2, STRMAX) != 0)
            strcpy(new.snd_author, author2);
    }

    // Pede editora
    if (prompt_string("Insira editora: ", new.publisher, STRMAX) == 0)
        return;

    // Pede area scientifica
    if (prompt_string("Insira area cientifica: ", new.sci_area, STRMAX) == 0)
        return;

    // Pede Idioma
    if (prompt_string("Insira o codigo de linguagem (ISO 639-1): ", new.idiom, IDIOMDIM) == 0)
        return;

    // Pede ano 
    int count = 0;
    uint16_t year;
    do {
        uint16_t n;
        year = n = prompt_id("Insira o ano de lançamento: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0)
            return;
        if (count != 4)
            tui_write_error("Ano deve ter 4 digitos. ex: 2004");
    } while (count != 4);
    new.year = year;

    // Pede preço
    new.price = prompt_float("Insira o preço (€/unid): ");

    // Pede Stock
    uint16_t amount, n;
    amount = n = prompt_id("Quantidade em stock: ");
    while (n != 0) {
        n /= 10;     // n = n/10
        ++count;
    }
    if (count == 0)
        return;
    new.stock_amount = amount;

    // Atualiza Geral
    w->books = append_book(w->books, &new);
    return;
}


void tui_del_book(struct world *w) {
    char isbn[ISBNDIM];
    prompt_string("ISBN a remover: ", isbn, ISBNDIM);
    if (strlen(isbn) == 0)
        tui_write_info("Remoção cancelada.\n");
    else
    {
        BOOK_NODE *ptr = book_by_isbn(w->books, isbn);
        if (ptr != NULL)
            w->books = remove_book(w->books, isbn);
        else
            tui_write("Não existe livro com ISBN '%s'.\n", isbn);
    }

    return;
}


void tui_refresh_book(struct world *w) {
    tui_title("EDITAR LIVRO");
    BookInfo info;
    BookInfo *ptr;

    char isbn[ISBNDIM];
    do {
        if (prompt_string("ISBN a editar: ", isbn, ISBNDIM) == 0)
            tui_write_info("Edição cancelada.\n");
        else {
            ptr = &(book_by_isbn(w->books, isbn)->info);
            if (ptr == NULL)
                tui_write("Não existe livro com ISBN '%s'.\n", isbn);
        }
    } while (ptr != NULL);

    tui_show_book(ptr);

    char title[STRMAX];
    if (prompt_string("(opcional) Editar titulo: ", title, STRMAX) != 0)
        strcpy(info.title, title);

    char autor_1[STRMAX];
    if (prompt_string("(opcional) Editar : ", title, STRMAX) != 0)
        strcpy(info.fst_author, autor_1);

    // Pede autor(es)
    char autor_2[STRMAX];
    if (prompt_string("(opcional) Editar autor 2: ", autor_2, STRMAX) != 0)
        strcpy(info.snd_author, autor_2);

    // Pede editora
    char editora[STRMAX];
    if (prompt_string("(opcional) Editar editora: ", editora, STRMAX) != 0)
        strcpy(info.publisher, editora);

    // Pede area scientifica
    char sciarea[STRMAX];
    if (prompt_string("(opcional) Editar área cientifica: ", sciarea, STRMAX) != 0)
        strcpy(info.sci_area, sciarea);

    // Pede Idioma
    char idioma[IDIOMDIM];
    if (prompt_string("(opcional) Editar codigo idioma (ISO 639-1): ", idioma, IDIOMDIM) != 0)
        strcpy(info.idiom, idioma);

    // Pede ano
    int count;
    uint16_t year;
    do {
        count = 0;
        uint16_t n;

        year = n = prompt_id("(opcional) Editar o ano de lançamento: ");
        while (n != 0) {
            n /= 10; // n = n/10
            ++count;
        }
        if (count == 0)
            break;
    } while (count != 4);

    if (count == 4)
        info.year = year;


    // Pede preço
    info.price = prompt_float("Editar o preço (€/unid): ");

    // Pede Stock
    uint16_t amount, n = prompt_id("(opcional) Quantidade em stock: ");
    while (n != 0) {
        n /= 10; // n = n/10
        ++count;
    }
    if (count != 0)
        info.stock_amount = amount;

    return;
}



// CLIENTE
void tui_show_client(ClientInfo const *const client, struct world *w, int on_off) {
    if (client != NULL) {
        tui_title("\t             CLIENTE");
        tui_write("\t            Nome: %s\n",          client->name);
        tui_write("\t             NIF: %" PRIu32 "\n", client->NIF);
        tui_write("\t          Morada: %s\n",          client->address);
        tui_write("\t        Telefone: %" PRIu32 "\n", client->telephone);

        if (on_off) {
            tui_write("\tLista de Compras: \n");
            iter_orders(client->buy_history, w, tui_show_order);
        }
    }

    return;
}


void tui_get_client(struct world *w) {
    struct item menu[] = {
        {.text = "Pesquisar por NIF", .func = NULL},
        {.text = "Pesquisar por Nome", .func = NULL},
        {.text = "Pesquisar por Morada", .func = NULL},
        {.text = "Pesquisar por Contacto", .func = NULL},
        {.text = "VOLTAR", .func = NULL},
        {.text = NULL, .func = NULL}};

    int opt;
    do {
        println();
        tui_title("CONSULTA DE CLIENTES");
        show_menu(menu);
        exec_menu(w, menu, &opt, "Opção?");

        switch (opt) {
        // Pesquisar por ID
            case 0: {
                uint32_t nif = prompt_uint32("NIF a pesquisar: ");
                if (nif == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    CLIENT_TREE *ptr = client_by_nif(w->clients, nif);
                    if (ptr != NULL)
                        tui_show_client(&ptr->info, w, 1);
                    else
                        tui_write_warning("ID não existe.\n");
                }
                break;
            }

            // Pesquisar por nome
            case 1: {
                char name[STRMAX];
                prompt_string("Nome a pesquisar: ", name, STRMAX);
                if (strlen(name) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    CLIENT_TREE *ptr = client_by_name(w->clients, name);
                    if (ptr != NULL)
                        tui_show_client(&ptr->info, w, 1);
                    else
                        tui_write("Não existe cliente com nome '%s'.\n", name);
                }
                break;
            }

            case 2: {
                char morada[STRMAX];
                prompt_string("Morada a pesquisar: ", morada, STRMAX);
                if (strlen(morada) == 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    int clientswithaddress = count_tree_with_address(w->clients, morada);
                    if (clientswithaddress != 0) {
                        CLIENT_TREE *ptr[clientswithaddress]; 
                        add_clients_node_with_address(w->clients, ptr, morada, 0);
                        for (int i = 0; i < clientswithaddress; i++)
                            tui_show_client(&(ptr[i]->info), w, 0);
                    }
                    else
                        tui_write("Não existe cliente com morada '%s'.\n", morada);
                }
                break;
            }

            // Pesquisar por numero
            case 3: {
                uint32_t number, n;
                int count = 0;
                number = n = prompt_uint32("Numero a pesquisar: ");
                while (n != 0) {
                    n /= 10; // n = n/10
                    ++count;
                }

                if (count != 0)
                    tui_write_info("Pesquisa cancelada.\n");
                else {
                    CLIENT_TREE *ptr = client_by_telephone(w->clients, number);
                    if (ptr != NULL)
                        tui_show_client(&ptr->info, w, 1);
                    else
                        tui_write("Não existe cliente com numero '%d'.\n", number);
                }
                break;
            }
        }
    } while (opt != size_menu(menu) - 1);

    return;
}


void tui_set_client(struct world *w) {
    tui_title("NOVO CLIENTE");
    ClientInfo new;

    // Pede nome
    if (prompt_string("Insira nome: ", new.name, STRMAX) == 0)
        return;

    // Pede NIF
    int count;
    uint32_t nif;
    do {
        uint32_t n;
        count = 0;
        nif = n = prompt_uint32("Insira o NIF: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0)
            return;
        if (count != 9)
            tui_write_error("NIF não valido.");
    } while (count != 9);
    new.NIF = nif;

    // Pede morada
    if (prompt_string("Insira morada: ", new.address, STRMAX) == 0)
        return;

    // Pede numero de telefone
    count = 0;
    uint32_t number;
    do {
        uint32_t n;
        number = n = prompt_uint32("Insira o número de telefone: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count != 0)
            return;
        if (count != 9)
            tui_write_error("Número de telefone não valido.");
    } while (count != 9);
    new.telephone = number;

    w->clients = add_client(w->clients, &new);

    return;
}


void tui_del_client(struct world *w) {
    // Pede NIF
    int count;
    uint32_t nif;
    do {
        uint32_t n;
        count = 0;
        nif = n = prompt_uint32("Insira o NIF: ");
        
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0) {
            tui_write_info("Remoção cancelada.\n");
            return;
        }
        if (count != 9)
            tui_write_error("NIF não valido.");
    } while (count != 9);

    CLIENT_TREE *ptr = client_by_nif(w->clients, nif);
    if (ptr != NULL)
        w->clients = remove_client(w->clients, ptr);
    else
        tui_write("Não existe cliente com NIF '%" PRIu32 "'.\n", nif);
    
    return;
}


void tui_refresh_client(struct world *w) {
    tui_title("EDITAR CLIENTE");
    ClientInfo info;
    CLIENT_TREE *ptr;
    

    // Pede NIF
    int count;
    uint32_t nif;
    do {
        count = 0;
        uint32_t n;
        nif = n = prompt_uint32("Selecionar NIF: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0)
            return;
        if (count != 9 )
            tui_write_error("NIF não valido.");
        ptr = client_by_nif(w->clients, nif);
        if (ptr == NULL)
            tui_write("Não existe cliente com NIF '%" PRIu32 "'.\n", nif);

    } while (count != 9 && ptr == NULL);

    tui_show_client(&ptr->info, w, 0);
    // Pede nome
    char name[STRMAX];
    if (prompt_string("(opcional) Editar nome: ", name, STRMAX) != 0)
        strcpy(info.name, name);
    
    // Pede morada
    char morada[STRMAX];
    if (prompt_string("(opcional) Editar morada: ", morada, STRMAX) != 0)
        strcpy(info.address, morada);

    
    // Pede contacto 
    count = 0;
    uint32_t numero;
    do {
        uint32_t n;
        numero = n = prompt_uint32("Editar contacto: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count == 0)
            break;
        if (count != 9)
            tui_write_error("NIF não valido.");
    } while (count != 9);
    if (count != 0)
        info.telephone = numero;

    edit_client(ptr, &info);

    return;
}
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


void tui_show_order(OrderInfo const *const order, struct world *w) {
    if (order != NULL) {
        char s[11];

        tui_title("\t           ENCOMENDA");
        tui_write("\t             ID: %" PRIu32 "\n", order->id);
        tui_write("\t     Quantidade: %" PRIu16 "\n", order->amount);
        tui_write("\t    Preço Total: %f\n",          order->total_price);
        tui_write("\t    Efetuada em: %s\n",          date_to_string(s, order->date));

        tui_show_book(book_by_isbn(w->books, order->ISBN), w);
        tui_show_client(client_by_nif(w->clients, order->NIF), w);
    }

    return;
}


void tui_set_order(struct world *w) {
    tui_title("CRIAR ENCOMENDA");
    OrderInfo new;
    srand(time(NULL));

    // Gera um ID
    do
        new.id = rand() / ((uint32_t) RAND_MAX / UINT32_MAX);
    while (order_by_id(w->orders, new.id) != NULL);

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
    new.amount = prompt_id("Insira quantidade: ");

    // Calcula preço
    new.total_price *= new.amount;

    // Obtem a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    new.date = {
        .day = tm.tm_mday,
        .month = tm.tm_mon + 1,
        .year = tm.tm_year + 1900
    };

    // Pede NIF
    int count;
    uint32_t nif;
    do {
        uint32_t n;
        nif, n = prompt_uint32("Insira o NIF: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count != 0)
            return;
        if (count != 9)
            tui_write_error("NIF não valido.");
    } while (count != 9);
    new.NIF = nif;

    // Atualiza cliente
    append_order_list(client_by_nif(w->clients, new.NIF)->info.buy_history, &new);

    // Atualiza Geral
    append_order_queue(w->orders, &new);
    return;
}


void tui_show_book(BookInfo const *const book, struct world *w) {
    if (book != NULL) {
        tui_title("\t              LIVRO");
        tui_write("\t            ISBN: %s\n",     book->ISBN);
        tui_write("\t          Titulo: %s\n",     book->title);
        tui_write("\t Area Cientifica: %s\n",     book->sci_area);
        tui_write("\t       Autor(es): %s, %s\n", book->fst_author, book->snd_author);
        tui_write("\t         Editora: %s\n",     book->publisher);
    }

    return;
}


void tui_set_book(struct world *w)
{
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
            tui_write_error("ISBN invalido.");
    } while (book != NULL && len != 14);
    

    // Pede titulo
    do {
        if (prompt_string("Insira titulo: ", new.title, STRMAX) == 0)
            return;

        book = book_by_title(w->books, new.title);
    } while (book != NULL);

    // Pede autor(es)
    int author_amount;
    do {
        char* authors;
        if (prompt_string("Insira autor(es) (separado por ,): ", authors, STRMAX) == 0)
            return;
        char **token = strtokenizer(authors, ",", &n);
        if (author_amount == 0)
            return;
        strcpy(new.fst_author, token[0]);
        if (author_amount == 2)
            strcpy(new.fst_author, token[1]);
        if (author_amount > 2)
            tui_write_error("O sistema apenas pode receber 2 autores");

        freestrvec(token, n);
    } while (author_amount > 2);

    // Pede editora
    if (prompt_string("Insira editora: ", new.publisher, STRMAX) == 0)
        return;

    // Pede area scientifica
    if (prompt_string("Insira area cientifica: ", new.sci_area, STRMAX) == 0)
        return;

    // Pede Idioma
    if (prompt_string("Insira o codigo de linguagem (ISO 639-1): " new.idiom, IDIOMDIM, ) == 0)
        return;

    // Pede ano 
    int count = 0;
    do {
        u_int16_t n;
        year, n = prompt_id("Insira o ano de lançamento: ");
        while (n != 0) {
            n /= 10;     // n = n/10
            ++count;
        }

        if (count != 0)
            return;
        if (count != 4)
            tui_write_error("Ano deve ter 4 digitos. ex: 2004");
    } while (count != 4);
    new.year = year;

    // Pede preço
    new.price = prompt_float("Insira o preço (€/unid): ");

    // Pede Stock
    u_int16_t amount, n = prompt_id("Quantidade em stock: ");
    while (n != 0) {
        n /= 10;     // n = n/10
        ++count;
    }
    if (count != 0)
        return;
    new.stock_amount = amount

    // Atualiza Geral
    append_book(w->books, &new);
    return;
}


void tui_show_client(ClientInfo const *const client, struct world *w, int on_off) {
    if (client != NULL) {
        tui_title("\t             CLIENTE");
        tui_write("\t             NIF: %" PRIu32 "\n", client->NIF);
        tui_write("\t          Morada: %s\n",          client->address);
        tui_write("\t        Telefone: %" PRIu32 "\n", client->telephone);
        tui_write("\tLista de Compras: \n");

        if (on_off)
            iter_orders(client->buy_history, w, tui_show_order);
    }

    return;
}
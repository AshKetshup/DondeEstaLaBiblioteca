#include <stdio.h>
#include <stdint.h>
#include "iostream.h"
#include "types.h"
#include "utils.h"
#include "sism.h"

#include "bookmanagement.h"
#include "ordermanagement.h"
#include "clientmanagement.h"

//------------------------------------------------------------------------------
// FOR DEBUG PURPOSES ONLY
#include <inttypes.h>
#include "debug.h"
//------------------------------------------------------------------------------

#define F_CLIENTS   "clients.dat"
#define F_ORDER     "order.dat"
#define F_BOOKS     "books.dat"

int loadfromfile(struct world* w) {
    FILE *f = fopen(F_BOOKS, "r");
    if (!f)
        return __ERROR_FILE;
    BookInfo book;
    while (!feof(f)) {
        fread(&book, sizeof(BookInfo), 1, f);
        append_book(w->books, &book);
    }
    fclose(f);

    f = fopen(F_ORDER, "r");
    if (!f)
        return __ERROR_FILE;
    OrderInfo order;
    while (!feof(f)) {
        fread(&order, sizeof(OrderInfo), 1, f);
        append_order_node(w->orders->head, &order);
    }
    fclose(f);

    f = fopen(F_CLIENTS, "r");
    if (!f)
        return __ERROR_FILE;
    while (!feof(f)) {
        unsigned count;
        unsigned id;
        ClientInfo client;
        fread(&client.NIF, sizeof(unsigned), 1, f);
        fread(client.name, STRMAX * sizeof(char), 1, f);
        fread(client.address, STRMAX * sizeof(char), 1, f);
        fread(&client.telephone, sizeof(unsigned), 1, f);
        fread(&count, sizeof(unsigned), 1, f);
        for (int i = 0; i < count; i++) {
            fread(&id, sizeof(unsigned), 1, f);
            append_order_node(client.buy_history, &(order_by_id(w->orders->head, id)->info));
        }
        add_client(w->clients, &client);
    }
    fclose(f);

    return __ERROR_SUCCESS;
}


void save_tree(FILE *f, CLIENT_TREE *tree) {
    unsigned count;
    unsigned id;
    fwrite(&tree->info.NIF, sizeof(unsigned), 1, f);
    fwrite(tree->info.name, STRMAX * sizeof(char), 1, f);
    fwrite(tree->info.address, STRMAX * sizeof(char), 1, f);
    fwrite(&tree->info.telephone, sizeof(unsigned), 1, f);
    count = (unsigned) count_orders(tree->info.buy_history);
    fwrite(&count, sizeof(unsigned), 1, f);
    ORDER_NODE *order = tree->info.buy_history;
    for (int i = 0; i < count; i++) {
        fwrite(&order->info.id, sizeof(unsigned), 1, f);
        order = order->next;
    }
    save_tree(f, tree->left);
    save_tree(f, tree->right);
}


int savetofile(struct world *w) {
    FILE *f = fopen(F_BOOKS, "w");
    if (!f)
        return __ERROR_FILE;
    BOOK_NODE *book = w->books;
    while (book != NULL) {
        fwrite(&book->info, sizeof(BookInfo), 1, f);
        book = book->next;
    }
    fclose(f);

    f = fopen(F_ORDER, "w");
    if (!f)
        return __ERROR_FILE;
    ORDER_NODE *order = w->orders->head;
    while (order != NULL) {
        fwrite(&order->info, sizeof(OrderInfo), 1, f);
        order = order->next;
    }
    fclose(f);

    f = fopen(F_CLIENTS, "w");
    if (!f)
        return __ERROR_FILE;
    save_tree(f, w->clients);
    fclose(f);
    return __ERROR_SUCCESS;
}

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "sism.h"


#define STRMAX   256            // Valor predefenido como maximo de String
#define ISBNDIM  14             // Dimensão de qualquer ISBN
#define IDIOMDIM 3              // Dimensão de Language Code ISO 639-1


/* === TIPOS GERAIS === */
/* Data */
typedef struct {
    uint16_t year;
    uint8_t  month, day;
} date_t;


/* Tipo da Encomenda */
typedef enum {
    Buy, Sell
} order_type;


/* === ESTRUTURAS DE DADOS === */
/* Encomenda */
typedef struct {
    uint32_t    id;                     // ID da compra
    order_type  type;                   // (Compra ou Venda)
    char        ISBN[ISBNDIM];          // ISBN unico por Livro
    float       total_price;            // Preço Total
    date_t      date;                   // Data em que a encomenda foi efetuada
    uint32_t    NIF;                    // NIF correspondente ao Cliente
    uint16_t    amount;                 // Quantidade de Livros encomendados
} OrderInfo;


/* Cliente */
typedef struct {
    uint32_t    NIF;                    // NIF (unico por cliente)
    char        name[STRMAX];           // Nome do Cliente
    char        address[STRMAX];        // Morada do Cliente
    OrderInfo   *buy_history;           // Vetor dinâmico de compras
} ClientInfo;


/* Livro */
typedef struct {
    char     ISBN[ISBNDIM];             // ISBN unico de cada livro
    char     title[STRMAX];             // Titulo do Livro
    char     idiom[IDIOMDIM];           // Idioma do livro pelo codigo de linguagem ISO 639-1
    char     fst_author[STRMAX];        // Nome do primeiro autor
    char     snd_author[STRMAX];        // Nome do segundo autor
    char     publisher[STRMAX];         // Nome da Editora
    char     sci_area[STRMAX];          // Nome da Area Cientifica
    float    price;                     // Valor do Livro
    uint16_t year;                      // Ano a que foi lançado
    uint16_t stock_amount;              // Stock disponivel
} BookInfo;


/* === Manipuladores === */
// Manipulador de Livros (Lista Ligada)
typedef struct book_node {
    BookInfo info;              // Informação do Livro
    struct book_node *next;     // Próximo livro na Lista
} BOOK_NODE;


// Manipulador de Encomendas (Fila/Queue)
typedef struct order_node {
    OrderInfo info;             // Informação da Encomenda
    struct order_node *next;    // Proxima encomenda na Fila
} ORDER_NODE;


typedef struct order_q {
    ORDER_NODE *head;
    ORDER_NODE *last;
} ORDER_QUEUE;


// Manipulador de Clientes (Arvore de Pesquisa Balanceada)
typedef struct client_tree
{
    ClientInfo info;            // Informação do Cliente
    struct client_tree *left;   // Nodo à esquerda
    struct client_tree *right;  // Nodo à direita
} CLIENT_TREE;



/* === "THE WORLD" === */
struct world {
    struct {
        uint32_t
            books,          // Contador de livros
            clients,        // Contador de clientes
            buys,           // Contador de compras
            sells,          // Contador de vendas
            orders;         // Contador de encomendas
    } count;

    BOOK_NODE   *books;     // Lista ligada de Livros
    CLIENT_TREE *clients;   // Arvore binaria de pesquisa balanceada de Clientes
    ORDER_NODE  *orders;    // Fila de Encomendas

    SISM status;            // State Machine (SISM System)
};

/* === Metodos Gerais === */
char* date_to_string(char*, date_t);

/* Inicialização, atualização e finalização de "world" */
void init_world(struct world*);
void refresh_world(struct world*);
void free_world(struct world*);

#endif
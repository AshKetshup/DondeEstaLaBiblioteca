#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdbool.h>
#include "sism.h"


#define STRMAX   256            // Valor predefenido como maximo de String
#define ISBNDIM  14             // Dimensão de qualquer ISBN
#define IDIOMDIM 3              // Dimensão de Language Code ISO 639-1

/* === TIPOS GERAIS === */
/* Data */
typedef struct
{
    unsigned short year;
    unsigned short month, day;
} date_t;



/* === ESTRUTURAS DE DADOS === */
/* Encomenda */
typedef struct {
    unsigned    id;                     // ID da compra
    char        ISBN[ISBNDIM];          // ISBN unico por Livro
    unsigned    NIF;                    // NIF correspondente ao Cliente
    float       total_price;            // Preço Total
    date_t      date;                   // Data em que a encomenda foi efetuada
    unsigned short amount;              // Quantidade de Livros encomendados
} OrderInfo;

// Manipulador de Encomendas Pessoais
typedef struct order_node
{
    OrderInfo info;          // Informação da Encomenda
    struct order_node *next; // Proxima encomenda na Fila
} ORDER_NODE;

/* Cliente */
typedef struct {
    unsigned    NIF;                    // NIF (unico por cliente)
    char        name[STRMAX];           // Nome do Cliente
    char        address[STRMAX];        // Morada do Cliente
    unsigned    telephone;              // Numero de Telefone
    ORDER_NODE  *buy_history;           // Vetor dinâmico de compras
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
    unsigned short year;                      // Ano a que foi lançado
    unsigned short stock_amount;              // Stock disponivel
} BookInfo;

/* === Manipuladores === */
// Manipulador de Livros (Lista Ligada)
typedef struct book_node
{
    BookInfo info;          // Informação do Livro
    struct book_node *next; // Próximo livro na Lista
} BOOK_NODE;

// Manipulador de Clientes (Arvore de Pesquisa Balanceada)
typedef struct client_tree
{
    ClientInfo info;           // Informação do Cliente
    struct client_tree *left;  // Nodo à esquerda
    struct client_tree *right; // Nodo à direita
} CLIENT_TREE;

// Manipulador de Encomendas gerais (Fila/Queue)
typedef struct order_q
{
    ORDER_NODE *head;
    ORDER_NODE *last;
} ORDER_QUEUE;

/* === "THE WORLD" === */
struct world {
    struct {
        unsigned
            books,          // Contador de livros
            clients,        // Contador de clientes
            buys,           // Contador de compras
            sells,          // Contador de vendas
            orders;         // Contador de encomendas
    } count;

    BOOK_NODE   *books;     // Lista ligada de Livros
    CLIENT_TREE *clients;   // Arvore binaria de pesquisa balanceada de Clientes
    ORDER_QUEUE *orders;    // Fila de Encomendas

    SISM status;            // State Machine (SISM System)
};

/* === Metodos Gerais === */
const char *date_to_str(char *, date_t);

/* Inicialização, atualização e finalização de "world" */
void init_world(struct world*);
void refresh_world(struct world*);
void free_world(struct world*);

void free_book_list(BOOK_NODE *);
void free_order_list(ORDER_NODE *);
void free_clients_tree(CLIENT_TREE *);
void free_order_queue(ORDER_QUEUE *);

#endif

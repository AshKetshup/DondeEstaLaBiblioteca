#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "sism.h"

#define STRMAX 256				// Valor predefenido como maximo de String
#define ISBNDIM 14 				// Dimensão de qualquer ISBN
#define IDIOMDIM 3				// Dimensão de Language Code ISO 639-1

/* === TIPOS GERAIS === */
/* Data */
typedef struct {
	uint16_t year;
	uint8_t month, day;
} date_t;

/* Tipo da Encomenda */
typedef enum {
	Buy, Sell
} order_type;

/* === ESTRUTURAS DE DADOS === */
/* Encomenda */
typedef struct {
	char ISBN[ISBNDIM];			// ISBN unico por Livro
	float total_price;			// Preço Total
	order_type type;			// (Compra ou Venda)
	date_t date;				// Data em que a encomenda foi efetuada
	uint32_t NIF;				// NIF correspondente ao Cliente
	uint16_t amount; 			// Quantidade de Livros encomendados
} OrderInfo;

/* Cliente */
typedef struct {
	uint32_t NIF;				// NIF (unico por cliente)
	char name[STRMAX];			// Nome do Cliente
	char address[STRMAX];		// Morada do Cliente
	OrderInfo *buy_history;		// Vetor dinamico de compras
} ClientInfo;

/* Livro */
typedef struct {
	char ISBN[ISBNDIM];			// ISBN unico de cada livro
	char title[STRMAX];			// Titulo do Livro
	char idiom[IDIOMDIM];		// Idioma do livro pelo codigo de linguagem ISO 639-1
	char fst_author[STRMAX];	// Nome do primeiro autor
	char snd_author[STRMAX];	// Nome do segundo autor
	char publisher[STRMAX];		// Nome da Editora
	char sci_area[STRMAX];		// Nome da Area Cientifica
	float price;				// Valor do Livro
	uint16_t year;				// Ano a que foi lançado
	uint16_t stock_amount;		// Stock disponivel
} BookInfo;

/* === Manipuladores === */
// Manipulador de Livros (Lista Ligada)
struct BookNode {
	BookInfo INFO; 				// Informação do Livro
	struct BookNode *next;		// Próximo livro na Lista
};
typedef struct BookNode *BookManip;

// Manipulador de Encomendas (Fila/Queue)
struct OrderNode {
	OrderInfo INFO; 			// Informação da Encomenda
	struct OrderNode *next;		// Proxima encomenda na Fila
};
typedef struct OrderNode *OrderManip;

// Manipulador de Clientes (Arvore de Pesquisa Balanceada)
struct ClientNode {
	ClientInfo INFO; 			// Informação do Cliente
	struct ClientNode *left;	// Nodo à esquerda
	struct ClientNode *right;	// Nodo à direita
};
typedef struct ClientNode *ClientManip;


/* === "THE WORLD" === */
struct world {
	struct {
		uint32_t
			books,		  // Contador de livros
			clients,	  // Contador de clientes
			buys,		  // Contador de compras
			sells, 		  // Contador de vendas
			orders; 	  // Contador de encomendas
	} count;

	BookManip *books;	  // Lista ligada de Livros
	ClientManip *clients; // Arvore binaria de pesquisa balanceada de Clientes
	OrderManip *orders;   // Fila de Encomendas

	SISM status; 		  // State Machine (SISM System)
};

/* === Metodos Gerais === */
char* date_to_string(char*, date_t);

/* Inicialização, atualização e finalização de "world" */ 
void init_world(struct world*);
void refresh_world(struct world*);
void free_world(struct world*);

#endif
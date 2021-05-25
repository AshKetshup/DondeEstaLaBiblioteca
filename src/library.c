#include <stdio.h>
#include "types.h"
#include "tui.h"
#include "sism.h"
#include "debug.h"
#include "utils.h"

static const char *WORLD_FILE = "library.save";

int main_tui(struct world *);
void tui_livros(struct world *);
void tui_clientes(struct world *);
void tui_encomendas(struct world *);
void tui_ficheiro(struct world *);
void tui_sobre(struct world *);

int main(int argc, char const *argv[]) {
	// 1. Inicialização do mundo
	struct world w;
	init_world(&w);
	start_app(&w.status, argc, argv);
	debug("Operation mode: %X.\n", w.status.operation_mode);

	// 2. Carregamento de dados pela memoria permanente
	w.status.io = loadfromfile(&w, WORLD_FILE);
	debug("loadfromfile returned %X.\n", w.status.io);

	// 3. Execução do programa conforme o Operation Mode.
	
	return 0;
}


// Menu Principal
int main_tui(struct world *w) {
	struct item menu[] = {
		{.text = "Gerir Livros", .func = tui_livros},
		{.text = "Gerir Clientes", .func = tui_clientes},
		{.text = "Gerir Encomendas", .func = tui_encomendas},
		{.text = "Ficheiro", .func = tui_ficheiro},
		{.text = "SOBRE", .func = tui_sobre},
		{.text = "SAIR", .func = NULL},
		{.text = NULL, .func = NULL}};

	int opt;
	do {
		title_menu("Menu Principal");
		show_menu(menu);
		exec_menu(w, menu, &opt, "Opção: ");
	} while (opt != size_menu(menu) - 1);
	
	return w->status.error;
}


// Menu Livros
void tui_livros(struct world *w) {
	struct item menu[] = {
		{.text = "Inserir", .func = NULL},
		{.text = "Remover", .func = NULL},
		{.text = "Alterar", .func = NULL},
		{.text = "Consultar", .func = NULL},
		{.text = "VOLTAR", .func = NULL},
		{.text =  NULL, .func = NULL}
	};

	int opt;
	do {
		title_menu("LIVROS");
		show_menu(menu);
		exec_menu(w, menu, &opt, "Opção: ");
	} while (opt != size_menu(menu) - 1);
}


// Menu Clientes
void tui_clientes(struct world *w) {
	struct item menu[] = {
		{.text = "Inserir", .func = NULL},
		{.text = "Remover", .func = NULL},
		{.text = "Consultar", .func = NULL},
		{.text = "VOLTAR", .func = NULL},
		{.text = NULL, .func = NULL}
	};

	int opt;
	do {
		title_menu("CLIENTES");
		show_menu(menu);
		exec_menu(w, menu, &opt, "Opção: ");
	} while (opt != size_menu(menu) - 1);
}


// Menu Encomendas
void tui_encomendas(struct world *w) {
	struct item menu[] = {
		{.text = "Inserir", .func = NULL},
		{.text = "Remover", .func = NULL},
		{.text = "VOLTAR", .func = NULL},
		{.text = NULL, .func = NULL}
	};

	int opt;
	do {
		title_menu("ENCOMENDAS");
		show_menu(menu);
		exec_menu(w, menu, &opt, "Opção: ");
	} while (opt != size_menu(menu) - 1);
}


// Menu Ficheiro
void tui_ficheiro(struct world *w) {
	struct item menu[] = {
		{.text = "Novo", .func = NULL},
		{.text = "Abrir", .func = NULL},
		{.text = "Guardar", .func = NULL},
		{.text = "VOLTAR", .func = NULL},
		{.text = NULL, .func = NULL}};

	int opt;
	do {
		title_menu("ENCOMENDAS");
		show_menu(menu);
		exec_menu(w, menu, &opt, "Opção: ");
	} while (opt != size_menu(menu) - 1);
}


// Tela Sobre a aplicação
void tui_sobre(struct world *w) {
	tui_write("\n\n");
	tui_write("       DondeEstaLaBiblioteca       ");
	tui_write("Um gerenciador de livrarias.\n\n");
	tui_write("Version: 1.0.0\n");
	tui_write("   Date: %s %s\n", __DATE__, __TIME__);
	tui_write("Authors: Diogo Castanheira Simões");
	tui_write("    		and");
	tui_write("		    João Pedro M. Freire\n");
	tui_write("\n\n");

	getch();
}
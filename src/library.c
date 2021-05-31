#include <stdio.h>
#include "types.h"
#include "tui.h"
#include "sism.h"
#include "debug.h"
#include "utils.h"
#include "interact.h"
#include "iostream.h"
#include "filemanagement.h"

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
    w.status.io = loadfromfile(&w, "library.save");
    debug("loadfromfile returned %X.\n", w.status.io);

    // 3. Execução do programa conforme o Operation Mode.
    // main_tui(&w);
    tui_ficheiro(&w);

    // 4. Guarda nos ficheiros ao sair
    w.status.io = savetofile(&w, "library.save");
    debug("savetofile returned %X.\n", w.status.io);

    return w.status.error;
}

// Menu Ficheiro
void tui_ficheiro(struct world *w)
{
    struct item menu[] = {
        {.text = "Novo", .func = new_save},
        {.text = "Abrir", .func = open_save},
        {.text = "Guardar", .func = save_save},
        {.text = "SAIR", .func = NULL},
        {.text = NULL, .func = NULL}
    };

    int opt;
    do {
        title_menu("FICHEIRO");
        show_menu(menu);
        exec_menu(w, menu, &opt, "Opção: ");
        if (opt == 1)
            main_tui(w);
    } while (opt != size_menu(menu) - 1);
}

// Menu Principal
int main_tui(struct world *w) {
    struct item menu[] = {
        {.text = "Gerir Livros", .func = tui_livros},
        {.text = "Gerir Clientes", .func = tui_clientes},
        {.text = "Gerir Encomendas", .func = tui_encomendas},
        {.text = "SOBRE", .func = tui_sobre},
        {.text = "VOLTAR", .func = NULL},
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
        {.text = "Inserir", .func = tui_set_book},
        {.text = "Remover", .func = tui_del_book},
        {.text = "Alterar", .func = tui_refresh_book},
        {.text = "Consultar", .func = tui_get_book},
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
        {.text = "Inserir", .func = tui_set_client},
        {.text = "Remover", .func = tui_del_client},
        {.text = "Alterar", .func = tui_refresh_client},
        {.text = "Consultar", .func = tui_get_client},
        {.text = "VOLTAR", .func = NULL},
        {.text = NULL, .func = NULL}};

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
        {.text = "Inserir", .func = tui_set_order},
        {.text = "Remover", .func = tui_del_order},
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


// Tela Sobre a aplicação
void tui_sobre(struct world *w) {
    tui_write("\n\n");
    tui_write("       DondeEstaLaBiblioteca       ");
    tui_write("Um gerenciador de livrarias.\n\n");
    tui_write("Version: 1.0.0\n");
    tui_write("   Date: %s %s\n", __DATE__, __TIME__);
    tui_write("Authors: Diogo Castanheira Simões");
    tui_write("		    João Pedro M. Freire\n");
    tui_write("\n\n");

    getch();
}

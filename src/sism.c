#include "sism.h"
#include <string.h>

/* Verifica se é indicado o modo de debug.
   Pode estar em qualquer posição, não verifica a sintaxe dos comandos. */
/*
int check_debug(int argc, char const **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            return 1;
        }
    }
    return 0;
}
*/

/* Função encarregue de iniciar o SISM e arrancar a app. */
void start_app(SISM *machine, int argc, char const **argv)
{
   /*
      Assumimos inicialmente que o programa vai correr no terminal.
      Caso haja argumentos em contrário, mudamos o Operation Mode em conformidade.
      Também se assume de início que o programa irá correr com sucesso.
    */

   /* Definição inicial das flags */
    machine->error = __ERROR_SUCCESS;
    machine->operation_mode = __OPERMODE_TERMINAL;
    machine->flow = __NEXT_CONTINUE;
    machine->io = 1;

    /* Interpretação dos argumentos
        SINTAXE:
        cmd:  app [<--tui | --gui>] [options]
        arg:   1          2             3
        - Se só for recebido 1 argumento, o programa deverá correr em modo TUI normal.
        - Se for recebido mais que 1 argumento, o 2º deve ser analisado:
            * Se for '--tui', o Operation Mode é definido como TUI alternativo;
            * Se for '--gui', o Operation Mode é definido como Graphical User Interface;
            * Se não for nenhum dos anteriores, é modo consola.
        */
    if (argc == 1)
        machine->operation_mode = __OPERMODE_TUI;
    else
    {
        if (strcmp(argv[1], "--tui") == 0)
            machine->operation_mode = __OPERMODE_TUIPLUS;
        else if (strcmp(argv[1], "--gui") == 0)
            machine->operation_mode = __OPERMODE_GUI;
        else
            machine->operation_mode = __OPERMODE_TERMINAL;
    }
}

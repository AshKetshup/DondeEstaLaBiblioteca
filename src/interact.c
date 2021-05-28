#include "interact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utils.h"
#include "tui.h"
#include "input.h"


void tui_show_order(order const *const ptr) {
    if (ptr != NULL) {
        tui_write("\t         ID: %" PRIu32 "\n", ptr->id);
        tui_write("\t       ISBN: %s\n", ptr->ISBN);
        // Titulo do livro.
        // Autor
        // Editora
        tui_write("\t Quantidade: %" PRIu16 "\n", ptr->amount);
        tui_write("\tPreço Total: %f", ptr->total_price);
        tui_write("\tEfetuada em: %" PRIu8 ".%" PRIu8 ".%" PRIu16, 
            ptr->date.day, 
            ptr->date.month, 
            ptr->date.year
        );
        // TODO
    }
}
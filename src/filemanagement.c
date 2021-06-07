#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "filemanagement.h"
#include "input.h"
#include "utils.h"
#include "tui.h"
#include "iostream.h"

char* SAVE_NAME;

char** saves_in_dir(const char* directory, const int p, int *n) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    *n = 0;

    // Calcula a quantidade de saves
    int saves_amount = 0;
    while ((dir = readdir(d)) != NULL)
        if (strstr(dir->d_name, ".save"))
            ++saves_amount;
    rewinddir(d);

    if (saves_amount != 0) {
        closedir(d);
        return NULL;
    }

    // Atribui ao array respetivos valores 
    int i = 0;
    char** filesList = (char**) malloc (saves_amount * sizeof(char*));
    while ((dir = readdir(d)) != NULL)
        if (strstr(dir->d_name, ".save")) {
            filesList[i] = (char*) malloc (strlen(dir->d_name)+1);
            strcpy(filesList[i], dir->d_name);
            i++;
        }
    *n = i;
    closedir(d);

    // Imprime o array caso p_bool != 0
    for (i = 0; i <= saves_amount && p != 0; i++)
        if (p == 1)
            tui_write("%s   ", filesList[i]);
        else if (p == 2)
            tui_write("%d > %s\n", i, filesList[i]);

    return filesList;
}


void new_save(struct world *w) {
    char new_savefile[STRMAX];
    FILE* fptr = NULL;
    int amount;

    tui_title("Saves disponiveis:");
    char** files = saves_in_dir("../saves", 1, &amount);
    if (files == NULL)
        tui_write_info("Não existem saves no diretorio.");

    size_t len = prompt_string("(opcional) Novo nome de save: ", new_savefile, STRMAX);

    int n = 0;
    if (len == 0) {
        for (int i = 0; i < amount; i++) {
            char str[STRMAX];
            sprintf(str, "save_%d.save", n);
            if (strcmp(files[i], str) == 0)
                n++;
        }
        sprintf(new_savefile, "save_%d", n);
    }

    sprintf(new_savefile, "../saves/%s.save", new_savefile);
    
    fopen(new_savefile, "wb");
    fclose(fptr);
}


void open_save(struct world *w) {
    int selected;
    int amount;

    tui_title("Saves disponiveis:\n");
    char** files = saves_in_dir("../saves", 1, &amount);
    if (files == NULL)
        tui_write_info("Não existem saves no diretorio.");
    
    selected = prompt_id("Selecione:\n");
    if (strcmp(SAVE_NAME, files[selected]) != 0) {
        if (loadfromfile(w, files[selected])) {
            SAVE_NAME = files[selected];
            return;
        }
    }
}


void save_save(struct world *w) {
    if (SAVE_NAME != NULL)
        savetofile(w, SAVE_NAME);
}

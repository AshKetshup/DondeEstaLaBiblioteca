#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "filemanagement.h"
#include "utils.h"
#include "tui.h"

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
            saves_amount++;
    rewinddir(d);

    char** filesList = (char**) malloc (saves_amount * sizeof(char*));

    // Atribui ao array respetivos valores 
    int i = 0;
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
            printf("%s   ", filesList[i]);
        else if (p == 2)
            printf("%d. %s\n", i, filesList[i]);

    return filesList;
}


int new_save(void) {
    char new_savefile[STRMAX];
    FILE* fptr = NULL;
    int amount;

    printf("Available saves:\n");
    char** files = saves_in_dir("../saves", 1, &amount);


    printf("New save name:\n");
    fgets(new_savefile, STRMAX, stdin);
    clear_buffer(stdin);

    int n = 0;
    if ((strcmp(new_savefile, "\n") == 0)) {
        for (size_t i = 0; i < amount; i++) {
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
    
    return 1;
}


int open_save(struct world *w) {
    int selected;
    int amount;

    printf("Available saves:\n");
    char** files = saves_in_dir("../saves", 2, &amount);
    
    printf("Option: ");
    scanf("%d", &selected);
    clear_buffer(stdin);

    if (strcmp(SAVE_NAME, files[selected]) != 0) {
        if (loadfromfile(w, files[selected])) {
            SAVE_NAME = files[selected];
            return 1;
        }
    } else {
        return 1;
    }

    
    return 0;
}


int save_save(struct world *w) {
    if (SAVE_NAME != NULL)
        return savetofile(w, SAVE_NAME);
    return 0;
}

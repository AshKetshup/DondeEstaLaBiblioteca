#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/* Limpa o buffer de entrada.
   A usar depois de um scanf e antes da leitura de uma string do stdin. */
void clear_buffer(FILE *stream) {
    char c;
    while (c = fgetc(stream), (c != EOF) && (c != '\n'))
        ;
}


/* Elimina o LF final de uma string obtida por fgets. */
void strlf(char *s) {
    for (; *s != '\0'; s++)
        ;
    s--;
    *s = '\0';
}


/* Devolve quantos bytes tem um ficheiro */
long fsize(FILE *f) {
    fseek(f, 0L, SEEK_END);
    return ftell(f);
}


/* Alternativa ao strstr */
int strcontains(const char *substr, const char *str) {
    return (strstr(str, substr) != NULL);
}


/* Converte uma letra (char) em maiúscula */
char charupr(char c) {
    return ((c > 'a') && (c < 'z') ? c - 'a' + 'A' : c);
}


/* Lê o pressionar de uma tecla */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

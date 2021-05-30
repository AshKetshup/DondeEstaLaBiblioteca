#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void clear_buffer(FILE *);
void strlf(char *);
long fsize(FILE *);
int strcontains(const char *, const char *);
char charupr(char);
int getch(void);
char **strtokenizer(char *, const char *, int *);
void freestrvec(char **, int);

#endif
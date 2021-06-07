#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "utils.h"

#include "debug.h"

static void accept_string(FILE *stream, char *const dest, size_t const size) {
    (void)fgets(dest, size, stream);
    size_t len = strlen(dest);

    if (dest[len - 1] != '\n')
        clear_buffer(stdin);
    else
        dest[len - 1] = '\0';
}

size_t prompt_string(const char *const promptmsg, char *const dest, size_t const size) {
    char buffer[size + 1];

    printf("%s", promptmsg);
    accept_string(stdin, buffer, size + 1);
    strncpy(dest, buffer, size);

    return strlen(buffer);
}

unsigned short prompt_id(const char *const promptmsg)
{
    char buffer[16] = {0};
    bool valid = false;
    unsigned short result = 0;

    while (!valid) {
        printf("%s", promptmsg);
        accept_string(stdin, buffer, 16);

        int len = 0;
        int res = sscanf(buffer, "%hu%n", &result, &len);
        if (res != 1 || len != strlen(buffer))
            continue; // Invalid integer
        else
            valid = true;
    }

    return result;
}

float prompt_float(const char *const promptmsg)
{
    char buffer[16] = {0};
    bool valid = false;
    float result = 0.f;

    while (!valid)
    {
        printf("%s", promptmsg);
        accept_string(stdin, buffer, 16);

        int len = 0;
        int res = sscanf(buffer, "%f%n", &result, &len);
        if (res != 1 || len != strlen(buffer))
            continue; // Invalid integer
        else
            valid = true;
    }

    return result;
}

unsigned prompt_uint32(const char *const promptmsg)
{
    char buffer[16] = {0};
    bool valid = false;
    unsigned result = 0;

    while (!valid)
    {
        printf("%s", promptmsg);
        accept_string(stdin, buffer, 16);

        int len = 0;
        int res = sscanf(buffer, "%u%n", &result, &len);
        if (res != 1 || len != strlen(buffer))
            continue; // Invalid integer
        else
            valid = true;
    }

    return result;
}

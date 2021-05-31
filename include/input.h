#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>

size_t prompt_string(
    const char *const promptmsg,
    char *const dest,
    size_t const size);

unsigned short prompt_id(const char *const promptmsg);
float prompt_float(const char *const promptmsg);
unsigned prompt_uint32(const char *const promptmsg);

#endif

#ifndef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

CLIENT_TREE *client_by_nif(CLIENT_TREE *, const uint32_t);
CLIENT_TREE *client_by_name(CLIENT_TREE *, const char*);




#endif
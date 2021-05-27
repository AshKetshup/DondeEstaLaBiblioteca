#ifdef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

ClientInfo client_by_nif(CLIENT_TREE*, const uint32_int);
ClientInfo client_by_name(CLIENT_TREE*, const char*);




#endif
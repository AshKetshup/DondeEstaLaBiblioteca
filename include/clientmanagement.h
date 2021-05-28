#ifndef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

CLIENT_TREE *client_by_nif(CLIENT_TREE *, const uint32_t);
CLIENT_TREE *client_by_name(CLIENT_TREE *, char [STRMAX]);
CLIENT_TREE *client_by_address(CLIENT_TREE *, char [STRMAX]);

CLIENT_TREE *add_client(CLIENT_TREE *, ClientInfo *);
CLIENT_TREE *remove_client(CLIENT_TREE *, const uint32_t);
CLIENT_TREE *edit_client(CLIENT_TREE *, ClientInfo *);


#endif
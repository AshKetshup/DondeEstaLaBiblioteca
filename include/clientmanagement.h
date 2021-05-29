#ifndef CLIENTMANAGMENT_H
#define CLIENTMANAGMENT_H

#include "types.h"

CLIENT_TREE *new_client(ClientInfo *);
int count_tree(CLIENT_TREE *);

int add_clients_to_array(CLIENT_TREE *, ClientInfo *, int);
ClientInfo *serialize_clients(CLIENT_TREE *);
CLIENT_TREE *deserialize_clients(ClientInfo [], int);

int get_balance(CLIENT_TREE *);
int tree_height(CLIENT_TREE *);
CLIENT_TREE *balance_tree(CLIENT_TREE *);

CLIENT_TREE *rotationRight(CLIENT_TREE *);
CLIENT_TREE *rotationLeft(CLIENT_TREE *);

CLIENT_TREE *client_by_nif(CLIENT_TREE *, const uint32_t);
CLIENT_TREE *client_by_name(CLIENT_TREE *, char [STRMAX]);
CLIENT_TREE *client_by_address(CLIENT_TREE *, char [STRMAX]);

CLIENT_TREE *free_client(CLIENT_TREE *);
CLIENT_TREE *add_client(CLIENT_TREE *, ClientInfo *);
CLIENT_TREE *next_minimum_client(CLIENT_TREE *, uint32_t);
CLIENT_TREE *remove_client(CLIENT_TREE *);
CLIENT_TREE *edit_client(CLIENT_TREE *, ClientInfo *);

#endif
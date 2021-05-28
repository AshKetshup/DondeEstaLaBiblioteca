#include <string.h>
#include "clientmanagement.h"


CLIENT_TREE *new_client(ClientInfo *client) {
    CLIENT_TREE *node = malloc(sizeof(CLIENT_TREE));
    node->info = *client;
    node->left = node->right = NULL;
    return node;
}


int is_balanced(CLIENT_TREE *tree) {
    return 1;
}


CLIENT_TREE *balance_tree(CLIENT_TREE *tree) {
    return tree;
}


CLIENT_TREE *client_by_nif(CLIENT_TREE *tree, const uint32_t nif) {

}


CLIENT_TREE *client_by_name(CLIENT_TREE *tree, char name[STRMAX]) {

}


CLIENT_TREE *client_by_address(CLIENT_TREE *tree, char address[STRMAX]) {

}


CLIENT_TREE *add_client(CLIENT_TREE *tree, ClientInfo *client) {
    if (tree == NULL)
        return new_client(client);
    if (client->NIF < tree->left->info.NIF)
        tree->left = add_client(tree->left, client);
    else
        tree->right = add_client(tree->right, client);
    return tree;
}


CLIENT_TREE *remove_client(CLIENT_TREE *tree, const uint32_t nif) {
    if (tree == NULL)
        return NULL;
    if (client->NIF < tree->left->info.NIF)
        tree->left = remove_client(tree->left, nif);
    else if (client->NIF > tree->left->info.NIF)
        tree->right = remove_client(tree->right, nif);
    else {
        
    }
    return tree;
}


CLIENT_TREE *edit_client(CLIENT_TREE *tree, ClientInfo *update) {
    if (tree == NULL)
        return NULL;
    tree->info = *update;
    return balance_tree(tree);
}

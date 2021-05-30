#include <string.h>
#include "clientmanagement.h"


CLIENT_TREE *new_client(ClientInfo *client) {
    CLIENT_TREE *node = malloc(sizeof(CLIENT_TREE));

    node->info = *client;
    node->left = node->right = NULL;
    
    return node;
}


int count_tree(CLIENT_TREE *tree) {
    if (tree == NULL)
        return 0;

    return 1 + count_tree(tree->right) + count_tree(tree->left);
}

int count_tree_with_address(CLIENT_TREE *tree, char *address) {
    if (tree == NULL)
        return 0;

    return 
        (strstr(address, tree->info.address) != NULL) +
        count_tree_with_address(tree->right, address) +
        count_tree_with_address(tree->left, address);
}


/* ========== SERIALIZATION / DESERIALIZATION ========== */


int add_clients_to_array(CLIENT_TREE *node, ClientInfo *array, int i) {
    if (node == NULL)
        return i;

    array[i] = node->info;

    return add_clients_to_array(node->right, array, add_clients_to_array(node->left, array, ++i));
}

int add_clients_node_with_address(CLIENT_TREE *node, CLIENT_TREE **array, char *address, int i) {
    if (node == NULL)
        return i;

    if (strstr(address, node->info.address) != NULL)
        array[i] = node;

    return 
        add_clients_node_with_address(
            node->right, 
            array, 
            address, 
            add_clients_node_with_address(
                node->left, array, address, ++i
            )
        );
}


ClientInfo *serialize_clients(CLIENT_TREE *client) {
    ClientInfo *serial;

    serial = malloc(count_tree(client) * sizeof(ClientInfo));
    add_clients_to_array(client, serial, 0);

    return serial;
}


CLIENT_TREE *deserialize_clients(ClientInfo *info, int count) {
    CLIENT_TREE *tree = NULL;

    for (size_t i = 0; i < count; i++)
        add_client(tree, info+i);

    return tree;
}


int get_balance(CLIENT_TREE *tree) {
    if (tree == NULL)
        return -1;

    return tree_height(tree->left) - tree_height(tree->right);
}


int tree_height(CLIENT_TREE *tree) {
    if (tree == NULL)
        return -1;

    int e = tree_height(tree->left);
    int d = tree_height(tree->right);
    
    return 1 + ((e > d) ? e : d);
}


CLIENT_TREE *balance_tree(CLIENT_TREE *tree) {
    if (tree == NULL)
        return NULL;

    int balance = get_balance(tree);

    if (balance < -1) {
        if (get_balance(tree->right) > 1)
            tree->right = rotationRight(tree->left);
        tree = rotationLeft(tree);
    }

    if (balance > 1) {
        if (get_balance(tree->left) < -1)
            tree->left = rotationLeft(tree->left);
        tree = rotationRight(tree);
    }

    tree->left = balance_tree(tree->left);
    tree->right = balance_tree(tree->right);

    return tree;
}


CLIENT_TREE *rotationRight(CLIENT_TREE *raiz) {
    if (raiz == NULL)
        return NULL;
        
    CLIENT_TREE *temp = raiz->left;
    raiz->left = temp->right;
    temp->right = raiz;
    raiz = temp;

    return raiz;
}


CLIENT_TREE *rotationLeft(CLIENT_TREE *raiz) {
    if (raiz == NULL)
        return NULL;
        
    CLIENT_TREE *temp = raiz->right;
    raiz->right = temp->left;
    temp->left = raiz;
    raiz = temp;

    return raiz;
}


CLIENT_TREE *client_by_nif(CLIENT_TREE *tree, const uint32_t nif) {
    if (tree == NULL)
        return NULL;

    if (nif < tree->info.NIF)
        tree->left = client_by_nif(tree->left, nif);
    else if (nif > tree->info.NIF)
        tree->right = client_by_nif(tree->right, nif);
    else
        return tree;
}


CLIENT_TREE *client_by_name(CLIENT_TREE *tree, const char name[STRMAX]) {
    if (tree == NULL)
        return NULL;

    if (strcmp(tree->info.name, name) == 0)
        return tree;

    CLIENT_TREE *left = client_by_name(tree->left, name);
    if (left != NULL)
        return left;

    return client_by_name(tree->right, name);
}


CLIENT_TREE *client_by_address(CLIENT_TREE *tree, const char address[STRMAX]) {
    if (tree == NULL)
        return NULL;

    if (strstr(tree->info.address, address) != NULL)
        return tree;

    CLIENT_TREE *left = client_by_address(tree->left, address);
    if (left != NULL)
        return left;

    return client_by_address(tree->right, address);
}


CLIENT_TREE *client_by_telephone(CLIENT_TREE *tree, const uint32_t number) {
    if (tree == NULL)
        return NULL;

    if (tree->info.telephone == number)
        return tree;

    CLIENT_TREE *left = client_by_telephone(tree->left, number);
    if (left != NULL)
        return left;

    return client_by_telephone(tree->right, number);
}


CLIENT_TREE *free_client(CLIENT_TREE *client) {
    client->left = NULL;
    client->right = NULL;
    free(client);
    
    client = NULL;
    return client;
}


CLIENT_TREE *add_client(CLIENT_TREE *tree, ClientInfo *client) {
    if (tree == NULL)
        return new_client(client);

    if (client->NIF < tree->left->info.NIF)
        tree->left = add_client(tree->left, client);
    else
        tree->right = add_client(tree->right, client);
    
    return balance_tree(tree);
}


CLIENT_TREE *next_minimum_client(CLIENT_TREE *tree, uint32_t nif) {
    if (tree->left == NULL)
        return tree;
    
    if (tree->info.NIF > nif)
        return next_minimum_client(tree->left, nif);

    return next_minimum_client(tree->right, nif);
}


CLIENT_TREE *remove_client(CLIENT_TREE *tree, CLIENT_TREE *target) {
    if (tree == NULL)
        return NULL;

    if (tree->left == NULL && tree->right == NULL) {
        tree = free_client(tree);
        return tree;
    }

    if (tree->left == NULL) {
        CLIENT_TREE *aux = tree;
        tree = tree->left;
        aux = free_client(aux);
        return tree;
    }

    if (tree->right == NULL) {
        CLIENT_TREE *aux = tree;
        tree = tree->right;
        aux = free_client(aux);
        return tree;
    }

    CLIENT_TREE *aux = next_minimum_client(tree, tree->info.NIF);
    tree->info = aux->info;
    aux = remove_client(tree, aux);

    return tree;
}


CLIENT_TREE *edit_client(CLIENT_TREE *tree, ClientInfo *update) {
    if (tree == NULL)
        return NULL;

    tree->info = *update;

    return balance_tree(tree);
}
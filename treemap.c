#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* newNode = createTreeNode(key, value);
    if (newNode == NULL) {
    // Error de asignación de memoria
    return;
    }

    if(tree->root == NULL) {
        tree->root = newNode;
    } else {
        TreeNode* temp = tree->root;
        while(1) {
            if(tree->lower_than(key, temp->pair->key)) {
                if(temp->left == NULL) {
                    temp->left = newNode;
                    newNode->parent = temp;
                    break;
                } else {
                    temp = temp->left;
                }
            } else if(tree->lower_than(temp->pair->key, key)) {
                if(temp->right == NULL) {
                    temp->right = newNode;
                    newNode->parent = temp;
                    break;
                } else {
                    temp = temp->right;
                }
            } else {  // Si la clave ya existe, actualizamos el dato
                temp->pair->value = value;
                free(newNode);  // Liberamos el nodo que ya no vamos a utilizar
                tree->current = temp;
                break;
            }
        }
    }
    tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode* parent = node->parent;

    //Si el nodo es una hoja
    if (node->left == NULL && node->right == NULL) {
        if (parent != NULL) {
            if (parent->left == node) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            tree->root = NULL;
            tree->current = NULL;
        }
        free(node);
        if (parent != NULL) {
            if (parent->left == NULL && parent->right == NULL) {
                parent->parent = NULL;
            }
        }
    }

    //Si el nodo tiene un solo hijo
    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        if (parent != NULL) {
            if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            if (child != NULL) {
                child->parent = parent;
            }
        } else {
            tree->root = child;
            if (child != NULL) {
                child->parent = NULL;
            }
        }
        free(node);
    }
    

    //Si el nodo tiene dos hijos
    else {
        TreeNode* successor = minimum(node->right);
        node->pair->key = successor->pair->key;
        node->pair->value = successor->pair->value;
        removeNode(tree, successor);
    }
    tree->current = NULL;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}

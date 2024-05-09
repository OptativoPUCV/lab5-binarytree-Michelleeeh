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
    /*while(x->left != NULL) {
        x = x->left;
    }
    return x;*/
}


void removeNode(TreeMap * tree, TreeNode* node) {
    /*if(node->left == NULL && node->right == NULL) {
        if(node->parent == NULL) {
            tree->root = NULL;
            
        } else {
            if(node->parent->left == node) {
                node->parent->left = NULL;
                
            } else {
                node->parent->right = NULL;
                
            }
        }
        free(node->pair->key);
        free(node->pair->value);
        free(node->pair);
        free(node);
    } */
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

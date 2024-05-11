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
    if(node == NULL) return;
    
    if(node->left == NULL && node->right == NULL) {
        if(node->parent == NULL) {
            tree->root = NULL;
            
        } else {
            if(node->parent->left == node) {
                node->parent->left = NULL;
                
            } else {
                node->parent->right = NULL;
            }  
        }
        
        free(node);
        
    } else {
        if(node->left != NULL && node->right != NULL) {
            TreeNode* min = minimum(node->right);
            node->pair->key = min->pair->key;
            node->pair->value = min->pair->value;
            removeNode(tree, min);
            
} else {
            TreeNode* child = (node->left != NULL) ? node->left : node->right;
            if(node->parent == NULL) {
                tree->root = child;
                child->parent = NULL;
            } else {
                if(node->parent->left == node) {
                    node->parent->left = child;
                    if(child != NULL)
                        child->parent = node->parent;
                } else {
                    node->parent->right = child;
                    if(child != NULL)
                        child->parent = node->parent;
                }   
            }
            free(node->pair->key);
            free(node->pair->value);
            free(node->pair);
            free(node);    
        }
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* node = tree->root;
    while(node != NULL) {
        if(is_equal(tree, key, node->pair->key)) {
            tree->current = node;
            return node->pair;
            
        } else {
            if(tree->lower_than(key, node->pair->key)) {
                node = node->left;
                
            } else {
                node = node->right;
            }  
        }
    }
    return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
    TreeNode* node = tree->root;
    TreeNode* ub = NULL;
    
    while(node != NULL) {
        if(tree->lower_than(key, node->pair->key)) {
            ub = node;
            node = node->left;
        } else if (tree->lower_than(node->pair->key, key)) {
            node = node->right;
        } else {
            ub = node;
            node = node->right;
        }
    }
        
    if(ub != NULL) {
        tree->current = ub;
        return ub->pair;
    } else {
        return NULL;
    }
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* node = tree->root;
    if(node == NULL) return NULL;
    tree->current = minimum(node);
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode* node = tree->current;
    if(node == NULL) return NULL;
    if(node->right != NULL) {
        tree->current = minimum(node->right);
        return tree->current->pair;
    } else {
        TreeNode* parent = node->parent;
        while(parent != NULL && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        tree->current = parent;
        if(parent != NULL) return parent->pair;
        else return NULL;
    }
}
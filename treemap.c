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
    TreeMap * new = (TreeMap *) malloc (sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if(tree == NULL) return;
    TreeNode *aux = tree->root;
    while(aux != NULL)
    {
        if(is_equal(tree, key, aux->pair->key)) return;
        if(tree->lower_than(key, aux->pair->key) == 1)
        {
            if(aux->left != NULL) 
            {
                aux = aux->left;
            }
            else
            {
                aux->left = createTreeNode(key, value);
                aux->left->parent = aux;
                tree->current = aux->left;
            }
        }
        else
        {
            if(aux->right != NULL) 
            {
                aux = aux->right;
            }
            else
            {
                aux->right = createTreeNode(key, value);
                aux->right->parent = aux;
                tree->current = aux->right;
            }
        }
    }

}

TreeNode * minimum(TreeNode * x){
    while (x->left != NULL)
        x = x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode *parent = node->parent;
    TreeNode *hijoIzq = node->left;
    TreeNode *hijoDer = node->right;
    if(hijoIzq == NULL && hijoDer == NULL){
        if(tree->lower_than(node->pair->key, parent->pair->key) == 1)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
        node->left = NULL;
        node->pair = NULL;
        node->right = NULL;
        node->parent = NULL;
    }
    else if(hijoIzq != NULL && hijoDer != NULL)
    {
        TreeNode *min = minimum(hijoDer);
        node->pair = min->pair;
        if(min->right != NULL){removeNode(tree, min);}
    }
    else
    {
        TreeNode *hijo = NULL;
        if(hijoIzq != NULL)
        {
            hijo = hijoIzq;
        }
        else
        {
            hijo = hijoDer;
        }
        node->pair = hijo->pair;
        node->right = hijo->right;
        node->left = hijo->left;
    }
    return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL) return NULL;
    TreeNode *aux = tree->root;

    while (aux != NULL) {
        tree->current = aux;
        if (tree->lower_than(aux->pair->key, key) == 1) 
        {
            aux = aux->right;
        }
        else if (tree->lower_than(key, aux->pair->key) == 1) 
        {
            aux = aux->left;
        }
        else break;
    }

    if (aux == NULL) return NULL;
    tree->current = aux;
    
    return aux->pair;
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

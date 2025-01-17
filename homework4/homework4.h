#ifndef _HOMEWORK4_H_
#define _HOMEWORK4_H_

typedef struct BSTNode {
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BST {
    int size;
    BSTNode* root;
} BST;

int power(int, int);

void addnode(BST*, int);

BST* createBST(int*, int);

#endif
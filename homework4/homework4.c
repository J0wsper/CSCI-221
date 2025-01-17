#include <stdio.h>
#include <stdlib.h>
#include "homework4.h"

// int removal(set* s, int value) {
//     node* query = s->root;
//     node* prev = NULL;

//     //Root case
//     if (query->value == value) {
        
//         //If there is only one element in the s, free it immediately.
//         if (s->size == 1) {
//             free(query);
//             s->size--;
//             return 1;
//         }
        
//         /*Otherwise, make the left node of the root the new root and search for a home for the right
//         branch of the root.
//         */
//         node* right_child = query->right;
//         node* current = s->root->left;
//         s->root->left = s->root;
//         while (current->right != NULL || current->left != NULL) {
            
//             //If we've found an appropriate spot for child_right, remove query and return.
//             if (current->right == NULL && current->value < right_child->value) {
//                 current->right = right_child;
//                 free(query);
//                 s->size--;
//                 return 1;
//             }
//             else if (current->left == NULL && current->value > right_child->value) {
//                 current->left = right_child;
//                 free(query);
//                 s->size--;
//                 return 1;
//             }
            
//             //Otherwise, continue iterating
//             if (right_child->value > current->value) {
//                 current = current->right;
//             }
//             else {
//                 current = current->left;
//             }
//         }
//     }

//     //If you're not trying to delete the root, search for that value.
//     while (query->value !=  value) {

//         //If the value isn't in the s, return a sentinel value.
//         if (query->right == NULL && query->left == NULL) {
//             return 0;
//         }
//         if (value > query->value) {
//             prev = query;
//             query = query->right;
//         }
//         else {
//             prev = query;
//             query = query->left;
//         }
//     }

//     //We can pass one child off to prev immediately.
//     if (prev->right == query && query->right != NULL) {
//         prev->right = query->right;
//         query->right = NULL;
//     }
//     else if (prev->left == query && query->left != NULL) {
//         prev->left = query->left;
//         query->left = NULL;
//     }

//     //If this results in query having no children or if query was a leaf node to begin with, delete it.
//     if (query->left == NULL && query->right == NULL) {
//         if (query == prev->right) {
//             prev->right = NULL;
//         }
//         else {
//             prev->left = NULL;
//         }
//         free(query);
//         s->size--;
//         return 1;
//     }

//     //Finally, if query had 2 children, we need to find a home for the other child.
//     node* current = prev;
//     node* child = NULL;
//     if (query->left != NULL) {
//         child = query->left;
//     }
//     else {
//         child = query->right;
//     }
//     while (query->left != NULL || query->right != NULL) {
//         if (current->value < child->value && current->right == NULL) {
//             current->right = child;
//             break;
//         }
//         else if (current->value > child->value && current->left == NULL) {
//             current->left = child;
//             break;
//         }

//         if (child->value > current->value) {
//             current = current->right;
//         }
//         else {
//             current = current->left;
//         }
//     }
//     free(query);
//     s->size--;
//     return 1;
// }

/*

WHITE-BOX TESTING

From the above code, we can tell that there are a few cases we would like to test: 

- The tree is empty

In this case, we want the tree to remain unchanged and return a '0' regardless of the input 'value'.

This test case was chosen because we do not want our function to segmentation fault when it attempts
to dereference NULL pointers as this would crash our program. Therefore, we need to ensure that it does
not have this behavior.

- The tree has one element

The expected behavior is that if we pass the function the one value that is in the tree, it removes
that value and returns a 1, resulting in an empty tree. If the value is not in the tree, it should return
a 0 and keep the tree unchanged.

This test case was chosen because there is a conditional branch to check whether the selected node is
the root node when the tree has size 1. Additionally, we want to check the case where the tree has 
no root value to ensure that no segmentation faults occur.

- Removing a node that has no children (a 'leaf' node)

The expected behavior is that the structure of the tree remains unchanged and that the leaf node is
freed. The parent node should then receive a NULL pointer as its new child. The function should also
return 1 in this case.

This test case was chosen because there is another conditional branch to check whether a selected node
is a leaf node. Therefore, we want to ensure that it works correctly and does not result in segmentation
faults when we attempt to remove nodes near that one in the future.

- Removing a node that has one child

The expected behavior is that the child of the removed node is passed off to the parent of the removed
node, maintaining the tree structure. This means that the children of the removed node are still accessible
later and does not create two disconnected graphs.

This test case was chosen because there is another conditional branch to check whether a node has a 
single child. We also want to ensure that when this happens, we do not create two disconnected graphs
or else all the children of the removed node become inaccessible.

- Removing a node that has two children

The expected behavior is that the one child of the removed node is passed off to the parent while the
function checks the rest of the tree for somewhere else to place the second child. This means that
both children should still be accessible following the removal.

This test case was chosen because it is the most difficult case to implement, as well as the one that
has the most code associated with it. Therefore, this case also has the greatest room for error. We
want to ensure that both children are still accessible while maintaining the BST structure, a task
that means we have to find a home for the second child.

- Removing the 'root' node

The expected behavior is that the root node is removed and replaced with one of its children which becomes
the new root node. Like the two children case, the root node's children should remain accessible following
the root's removal.

This test case was chosen because it has great potential to ruin the BST structure, as the root node
is the one that has the most children.

*/

//double* relu(double* input, int length)

/*

BLACK-BOX TESTING

For this, we can derive a few test cases without examining the code:

- The array is empty

If the function attempts to index an empty array, it will likely result in segmentation faults. Therefore,
we should examine this test case to ensure relu won't make our program crash. The expected behavior is
that we want our array to remain unchanged.

- The array contains only zeroes

This is to ensure that there is no undefined behavior at the breakpoint between the two cases we expect
our function to execute. The expected output is that the array should remain unchanged.

- The array contains only negative numbers

This checks the case where we go through the conditional that checks whether an element is negative
every single time. This then examines a key part of the behavior of the function. The expected output
of this is an array of the same length that contains only zeroes.

- The array contains positive and negative numbers

This checks both conditionals, ensuring that there is no undefined behavior when alternating between
positive and negative numbers. The expected behavior is that the length of the array remains unchanged,
while all of the negative numbers are replaced with zeroes and the positive numbers remain unchanged.

- The array contains only positive numbers

This checks the final conditional, ensuring that it works properly. The expected behavior is that the
array remains the same length with the same elements.

*/

int power(int x, int y) {
    if (y == 0) {
        return 1;
    }
    int r = 1;
    while (y > 1) {
        if (y % 2 == 1) {
        r = x * r;
        }
        x = x * x;
        y = y / 2;
    }
    return r * x;
}

/*

BUGS IN THE POWER FUNCTION

The main bug that I located was that raising a number to the power of 0 returned the input number rather
than 1. This can be fixed by a simple check at the beginning of the poewr function. Beyond that, the
function seems to work as intended for all non-negative inputs.

*/

void addnode(BST* inputTree, int value) {
    BSTNode* newnode = malloc(sizeof(BSTNode));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    if (inputTree->root == NULL) {
        inputTree->root = newnode;
    } 
    else {
        BSTNode* ptr = inputTree->root;
        while (ptr != NULL || ptr->value != value){
            if (value > ptr->value){
                if (ptr->right == NULL){
                    ptr->right = newnode;
                    break;
                }
                ptr = ptr->right;
            } 
            else if (value < ptr->value) {
                if (ptr->left == NULL){
                    ptr->left = newnode;
                    break;
                }
                ptr = ptr->left;
            } 
            else {
                return;
            }
        }
    }
    inputTree->size++;
}

BST* createBST(int array[], int size){
    BST* tree = malloc(sizeof(BST*));
    tree->size = 0;
    tree->root = NULL;
    for (int i=0; i < size; i++) {
        addnode(tree, array[i]);
    }
    return tree;
}

/*

BUGS IN THE createBST FUNCTION:

- SCOPING: One bug that is immediately apparent is that the tree created by createBST will be uninitialized as
soon as the program exits the function because malloc is not being used. 

- UNINITIALIZED ROOT: The root of tree is used uninitialized which will result in errors.
This can be fixed by assigning the root as NULL.

- UNSIGNED INTEGERS: The BSTNode struct only takes unsigned integers as its values while createBST
can take an array of signed integers as input. This will result in data type errors. To fix this, either
make it so that the node can accept signed integers or that the input array can only be unsigned. I
chose to fix this by allowing signed integers in the nodes.

- NEWNODE HAS UNINITIALIZED CHILDREN: In the addnode function, nodes are added to the tree without
initializing their children as NULL. This will result in problems when attempting to add new content
to the tree.

*/
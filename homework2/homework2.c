/* Answer to Shell questions:
1. 
You could enter the following shell command:
    cd ../csci221/labs
The ../ keyword takes you to the parent directory of your current working directory. This allows you
to circumvent the need for entering the global directory.

2. Because my computer uses bash, to get more information on the ls command you can enter the following
line into the terminal:
    ls --help
This is similiar to the `man` command we learned about. It will also give information about all of the
possible flags that a particular command can take. In the case of ls, -s gives the size of each file
in the current working directory.

3. To do this, we can use a grep, wc and a pipe. For example, this file--formerly--contained two instances
of the word 'This'. To get the number of instances, we could use the following command:
    grep 'This' homework2.c | wc
And it would correctly print that the word has been seen twice.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node {
    int value;
    struct bst_node* left;
    struct bst_node* right;
} bst_node;

typedef struct bst {
    int size;
    struct bst_node* root;
} bst;

void insert(bst* tree, int value) {
    bst_node* current = tree->root;
    bst_node* new_node = malloc(sizeof(bst_node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    for (int i = 0; i < tree->size; i++) {
        if (value > current->value) {
            if (current->right == NULL) {
                current->right = new_node;
                tree->size++;
                return;
            }
            else {
                current = current->right;
            }
        }
        else {
            if (current->left == NULL) {
                current->left = new_node;
                tree->size++;
                return;
            }
            else {
                current = current->left;
            }
        }
    }
    free(new_node);
}

bst* create_bst(int arr[], int length) {
    bst* tree = malloc(sizeof(bst));
    bst_node* root = malloc(sizeof(bst_node));
    root->value = arr[0];
    root->left = NULL;
    root->right = NULL;
    tree->root = root;
    tree->size = 1;
    //printf("tree created.\n");

    //Loop to go through the array elements.
    for (int i = 1; i < length; i++) {
        bst_node* current = tree->root;
        bst_node* new_node = malloc(sizeof(bst_node));
        new_node->value = arr[i];
        new_node->left = NULL;
        new_node->right = NULL;

        //Loop to scan the tree.
        for (int j = 0; j < tree->size; j++) {
            if (new_node->value > current->value) {
                if (current->right == NULL) {
                    current->right = new_node;
                    tree->size++;
                    break;
                }
                else {
                    current = current->right;
                    continue;
                }
            }
            else {
                if (current->left == NULL) {
                    current->left = new_node;
                    tree->size++;
                    break;
                }
                else {
                    current = current->left;
                    continue;
                }
            }
        }
    }
    return tree;
}

//This function was for my own debugging. It isn't for the homework.
void search_tree(bst* tree, int value) {
    bst_node* current = tree->root;
    for (int i = 0; i < tree->size; i++) {
        printf("current value: %i\n", current->value);
        if (current->value == value) {
            printf("value found. quitting\n");
            return;
        }
        else if (value > current->value) {
            if (current->right == NULL) {
                printf("value not in tree\n");
                return;
            }
            else {
                current = current->right;
                continue;
            }
        }
        else {
            if (current->left == NULL) {
                printf("value not in tree\n");
                return;
            }
            else {
                current = current->left;
                continue;
            }
        }
    }
}

int removal(bst* tree, int value) {
    bst_node* query = tree->root;
    bst_node* prev = NULL;

    //Root case
    if (query->value == value) {
        
        //If there is only one element in the tree, free it immediately.
        if (tree->size == 1) {
            free(query);
            tree->size--;
            return 1;
        }
        
        /*Otherwise, make the left node of the root the new root and search for a home for the right
        branch of the root.
        */
        bst_node* right_child = query->right;
        bst_node* current = tree->root->left;
        tree->root->left = tree->root;
        while (current->right != NULL || current->left != NULL) {
            
            //If we've found an appropriate spot for child_right, remove query and return.
            if (current->right == NULL && current->value < right_child->value) {
                current->right = right_child;
                free(query);
                tree->size--;
                return 1;
            }
            else if (current->left == NULL && current->value > right_child->value) {
                current->left = right_child;
                free(query);
                tree->size--;
                return 1;
            }
            
            //Otherwise, continue iterating
            if (right_child->value > current->value) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
    }

    //If you're not trying to delete the root, search for that value.
    while (query->value !=  value) {

        //If the value isn't in the tree, return a sentinel value.
        if (query->right == NULL && query->left == NULL) {
            return 0;
        }
        if (value > query->value) {
            prev = query;
            query = query->right;
        }
        else {
            prev = query;
            query = query->left;
        }
    }

    //We can pass one child off to prev immediately.
    if (prev->right == query && query->right != NULL) {
        prev->right = query->right;
        query->right = NULL;
    }
    else if (prev->left == query && query->left != NULL) {
        prev->left = query->left;
        query->left = NULL;
    }

    //If this results in query having no children or if query was a leaf node to begin with, delete it.
    if (query->left == NULL && query->right == NULL) {
        if (query == prev->right) {
            prev->right = NULL;
        }
        else {
            prev->left = NULL;
        }
        free(query);
        tree->size--;
        return 1;
    }

    //Finally, if query had 2 children, we need to find a home for the other child.
    bst_node* current = prev;
    bst_node* child = NULL;
    if (query->left != NULL) {
        child = query->left;
    }
    else {
        child = query->right;
    }
    while (query->left != NULL || query->right != NULL) {
        if (current->value < child->value && current->right == NULL) {
            current->right = child;
            break;
        }
        else if (current->value > child->value && current->left == NULL) {
            current->left = child;
            break;
        }

        if (child->value > current->value) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    free(query);
    tree->size--;
    return 1;
}

typedef struct double_array {
    int* arr1;
    int* arr2;
    int length;
} double_array;

double_array* find_divisors(int* arr1, int* arr2, int length1, int length2) {
    double_array* returned_arr = malloc(sizeof(double_array));
    returned_arr->length = 0;
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (arr1[i]%arr2[j] == 0) {
                returned_arr->length++;
            }
        }
    }
    int* dividends = malloc(returned_arr->length*sizeof(int));
    int* divisors = malloc(returned_arr->length*sizeof(int));
    returned_arr->arr1 = dividends;
    returned_arr->arr2 = divisors;
    int count = 0;
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (arr1[i] >= arr2[j] && arr1[i]%arr2[j] == 0) {
                returned_arr->arr1[count] = arr1[i];
                returned_arr->arr2[count] = arr2[j];
                count++;
            }
        }
    }
    return returned_arr;
}


int main() {
    int arr1[7] = {121,89,33,200,27,64,18};
    int arr2[10] = {3,6,17,11,100,84,21,4,9,12};
    double_array* test_arr = find_divisors(arr1, arr2, 7, 10);
    /*printf("arr1:\n");
    for (int i = 0; i < test_arr->length; i++) {
        printf("value %i: %i\n", i, test_arr->arr1[i]);
    }
    printf("arr2:\n");
    for (int j = 0; j < test_arr->length; j++) {
        printf("value %i: %i\n", j, test_arr->arr2[j]);
    }*/
    return 0;
}
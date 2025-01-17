#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "homework3.h"

void insert(set* s, int value) {
    node* current = s->root;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    for (int i = 0; i < s->size; i++) {
        if (current->value == new_node->value) {
            free(new_node);
            return;
        }
        if (value > current->value) {
            if (current->right == NULL) {
                current->right = new_node;
                s->size++;
                return;
            }
            else {
                current = current->right;
            }
        }
        else {
            if (current->left == NULL) {
                current->left = new_node;
                s->size++;
                return;
            }
            else {
                current = current->left;
            }
        }
    }
    free(new_node);
}

set* create(int arr[], int length) {
    set* s = malloc(sizeof(set));
    node* root = malloc(sizeof(node));
    root->value = arr[0];
    root->left = NULL;
    root->right = NULL;
    s->root = root;
    s->size = 1;

    //Loop to go through the array elements.
    for (int i = 1; i < length; i++) {
        node* current = s->root;
        node* new_node = malloc(sizeof(node));
        new_node->value = arr[i];
        new_node->left = NULL;
        new_node->right = NULL;

        //Loop to scan the s.
        for (int j = 0; j < s->size; j++) {
            if (current->value == new_node->value) {
                break;
            }
            if (new_node->value > current->value) {
                if (current->right == NULL) {
                    current->right = new_node;
                    s->size++;
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
                    s->size++;
                    break;
                }
                else {
                    current = current->left;
                    continue;
                }
            }
        }
    }
    return s;
}

//This function was for my own debugging. It isn't for the homework.
void search_set(set* s, int value) {
    node* current = s->root;
    for (int i = 0; i < s->size; i++) {
        printf("current value: %i\n", current->value);
        if (current->value == value) {
            printf("value found. quitting\n");
            return;
        }
        else if (value > current->value) {
            if (current->right == NULL) {
                printf("value not in s\n");
                return;
            }
            else {
                current = current->right;
                continue;
            }
        }
        else {
            if (current->left == NULL) {
                printf("value not in s\n");
                return;
            }
            else {
                current = current->left;
                continue;
            }
        }
    }
}

int removal(set* s, int value) {
    node* query = s->root;
    node* prev = NULL;

    //Root case
    if (query->value == value) {
        
        //If there is only one element in the s, free it immediately.
        if (s->size == 1) {
            free(query);
            s->size--;
            return 1;
        }
        
        /*Otherwise, make the left node of the root the new root and search for a home for the right
        branch of the root.
        */
        node* right_child = query->right;
        node* current = s->root->left;
        s->root->left = s->root;
        while (current->right != NULL || current->left != NULL) {
            
            //If we've found an appropriate spot for child_right, remove query and return.
            if (current->right == NULL && current->value < right_child->value) {
                current->right = right_child;
                free(query);
                s->size--;
                return 1;
            }
            else if (current->left == NULL && current->value > right_child->value) {
                current->left = right_child;
                free(query);
                s->size--;
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

        //If the value isn't in the s, return a sentinel value.
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
        s->size--;
        return 1;
    }

    //Finally, if query had 2 children, we need to find a home for the other child.
    node* current = prev;
    node* child = NULL;
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
    s->size--;
    return 1;
}

int empty(set* s){
    if (s->size <= 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int contains(set* s, int val) {
    node* current = s->root;
    while (current != NULL) {
        if (current->value == val) {
            return 1;
        }
        if (current->value < val) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return 0;
}

void delete(set* s) {
    if (s->size <= 0) {
        return;
    }
    node* curr = s->root;
    while (s->size > 0) {
        if (curr->left == NULL && curr->right == NULL) {
            node* removed = curr;
            curr = s->root;
            free(removed);
            s->size--;
        }
        if (curr->left != NULL) {
            curr = curr->left;
        }
        else if (curr->right != NULL) {
            curr = curr->left;
        }
    }
}

int choose(set* s) {
    srand(time(NULL));
    node* curr = s->root;
    while (curr != NULL) {
        if (curr->left == NULL && curr->right == NULL) {
            return curr->value;
        }
        int terminate = rand()%3;
        printf("%i\n", terminate);
        if (terminate == 0) {
            return curr->value;
        }
        if (curr->right != NULL && curr->left != NULL) {
            int decider = rand()%2;
            printf("%i\n", decider);
            if (decider == 1) {
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
            continue;
        }
        if (curr->right != NULL) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }
    return -1;
}
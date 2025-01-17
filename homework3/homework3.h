#ifndef _HOMEWORK3_H_
#define _HOMEWORK3_H_

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} node;

typedef struct set {
    int size;
    struct node* root;
} set;

/** Function that takes an array and its length and returns a set containing the elements in that array.
*/
set* create(int arr[], int);

/** Function that takes a set and frees the memory associated with that set. For some reeason, whenever
 * I tried naming this function 'delete', I got a very strange error. This function is delete.
*/
void delete(set*);

/** Function that takes a set and an integer and returns whether or not that integer is in the set,
 * with a '1' for true and a '0' for false.
*/
int contains(set*, int);

/** Takes a set and an integer and places that integer into the set if it is not there already.*/
void insert(set*, int);

/** Debugging function that takes a set and an integer and prints the pathway it took to get to that
 * integer.
*/
void search_set(set*, int);

/** Takes a set and an int and removes any elements with that value if they're in the set. Returns
 * 1 if the removal is successful and 0 otherwise.
*/
int removal(set*, int);

/** Takes a set and tells you whether it is empty or not.*/
int empty(set*);

/** Takes a set and returns a random value in the set.*/
int choose(set*);

#endif
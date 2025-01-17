#include <stdio.h>
#include <stdlib.h>
#include "homework4.h"

int main() {
    //(3,2) works
    //(3,3) works
    //(4,3) works
    //(4,4) works
    //(4,0) breaks; returns 4 instead of 1
    //(0,4) works
    //(0,3) works
    //(0,0) breaks; returns 0 instead of 1
    //(9,4) works
    //(9,1) works
    //(1,9) works
    //(1,0) works
    //(4,1) works
    //(1,4) works
    int test = power(1,4);
    //In order: works
    //Out of order: works
    //Multiple values: works
    int test_arr[5] = {1,3,4,2,5};
    BST* test_tree = createBST(test_arr,5);
    //Empty tree: works
    //Adding a same value: works
    //Adding a negative value: works
    addnode(test_tree, -2);
    printf("%i\n", test);
    free(test_tree);
    return 0;
}
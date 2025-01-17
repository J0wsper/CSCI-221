#include <stdlib.h>
#include <stdio.h>
#include "homework3.h"

int main() {
    int test_arr[1] = {2};
    set* a = create(test_arr, 1);
    printf("%d\n", choose(a));
    insert(a, 2);
    printf("%d\n", choose(a));
    printf("%d\n", empty(a));
    printf("%d\n", contains(a, 2));
    printf("%d\n", contains(a, 3));

    //Remove is a special, pre-defined function, I changed the name to prevent errors. They are functionally identical
    removal(a, 2);
    printf("%d\n", empty(a));
    delete(a);
    return 0;
}
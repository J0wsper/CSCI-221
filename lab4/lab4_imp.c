#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node* next;
} node;

typedef struct LL {
  struct node* first;
  struct node* last;
  int length;
} LL;

void prepend(LL* list, int value) {
  node* new = malloc(sizeof(node));
  new->value = value;
  new->next = NULL;
  if (list->first == NULL) {
    list->first = new;
    list->last = new;
    list->length = 1;
  } else {
    new->next = list->first;
    list->first = new;
    list->length++;
  }
}

/*

BUGS

There are a few bugs in this code. For one, 'size' is not a property of the linked list; 'length' is
the true name. Additionally, 'size_t' is not a data-type that is defined in this code despite being
passed as an argument. Furthermore, 'created' is not scoped properly and will be uninitialized as soon
as the program exits create_list() because it was not assigned using malloc, meaning it is effectively
useless. 'Append()' is also not a function that is defined anywhere here, meaning it will throw up errors.
The struct is also not called 'linked list' nor does it require 'struct' when it is being passed to malloc.
Furthermore, 'size' is an uninitialized variable and as such cannot be passed alone into malloc, nor
is it even required because we are only creating one linked list.

*/
LL* create_list(int value, size_t copies) {
  LL created;
  created.size = 0;
  for(int i = 0; i < copies; i++) {
    append(value, &created);
  }
  LL* pointer = malloc(sizeof(struct linked_list) * size);
  pointer = &created;
  return (pointer);
}

/*

BUGS

This function has severe memory leaks. Furthermore, it has no case testing; for example, if the index
is 0, then prev will be uninitialized and will result in a segmentation fault when you dereference
it at the end. In a similar vein, if the index is at the end of the list, this will also result in a
segmentation fault as you dereference current->next. Furthermore, it does not change the length of
the linked list which will result in errors for whoever next tries to work with it. Finally, if an invalid
length is passed to the function, it will cause the program to crash severely with a segmentation fault.
*/

void remove_from_list(LL* list, int index) {
  node* current = list->first;
  node* prev;
  for (int i = 0; i < index; i++) {
    prev = current;
    current = current->next;
  }
  prev->next = current->next;
}

void print_list(LL* list) {
    if (list->length <= 0) {
        return;
    }
    node* curr = list->first;
    int i = 0;
    while (curr != NULL) {
        printf("value at %i: %i\n", i, curr->value);
        curr = curr->next;
        i++;
    }
}

int main() {
    LL* test_list = malloc(sizeof(LL));
    test_list->last = NULL;
    test_list->first = NULL;
    test_list->length = 0;
    /*

    WHITE-BOX TESTING

    Control flow testing: we see that there is an if/else statement in prepend(). Because of this, we
    we want to check that the code in both branches is correct. Because the condition is that the list
    is empty, we have two tests: one where the list is initially empty and one where it has more than
    0 elements.
    */
    prepend(test_list, 6);
    prepend(test_list, 2);
    /*
    
    BLACK-BOX TESTING

    In order to do black-box testing on list_remove(), we can think of a few test cases: using list_remove()
    on an empty LL, using it on an LL that does not contain value, using it on an LL that contains multiple
    instances of the same value, using it on an LL that begins/ends with the value, etc... These are
    a few test cases I can think of without looking at the code.

    */
    print_list(test_list);
    return 0;
    free(test_list);
}

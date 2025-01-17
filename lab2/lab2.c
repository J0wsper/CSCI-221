//The shell always opens to the root directory, typically C:/Users/brams in my case.

/*To find a specific item with just its name and no knowledge of its directory,
one could use the 'find' keyword in the following way:
    find brams -name <filename>
this would search every directory below brams (my root directory) for the specified filename.
*/

/*to print out the contents of two files into a third, new file, we could do the following:
    cat <filename1> <filename2> > output.txt
this takes the stdout of cat and puts it into the newly-created output.txt file.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
  int value;
  struct list_node* next;
  struct list_node* prev;
} list_node;

typedef struct doubly_linked_list {
    int length;
    struct list_node* head;
    struct list_node* tail;
} doubly_linked_list;

typedef struct arr_with_length {
    int length;
    int* arr;
} arr_with_length;

//Puts the linker node in front of the rear_node
void front_link(list_node* linker, list_node* rear_node) {
    linker->prev = rear_node;
    rear_node->next = linker;
}


//Puts the linker node behind the front_node
void rear_link(list_node* linker, list_node* front_node) {
    linker->next = front_node;
    front_node->prev = linker;
}

void insert(doubly_linked_list* list, int index, int value) {
    list_node* new_node = malloc(sizeof(list_node));
    new_node->value = value;
    list_node* current = list->head;
    for (int i = 0; i < list->length; i++) {
        if (index == i) {
            if (current == list->head) {
                rear_link(new_node, current);
                list->head = new_node;
            }
            else {
                front_link(new_node, current->prev);
                rear_link(new_node, current);
            }
            list->length++;
            return;
        }
        else if (index >= list-> length) {
            front_link(new_node, list->tail);
            list->tail = new_node;
            list->length++;
            return;
        }
        current = current->next;
    }
    free(new_node);
}

doubly_linked_list* replicate(int value, int size) {
    doubly_linked_list* list = malloc(sizeof(doubly_linked_list));
    list->length = 0;
    for (int i = 0; i < size; i++) {
        list_node* node = malloc(sizeof(list_node));
        node->value = value;
        if (i == 0) {
            list->head = node;
            list->tail = node;
        }
        else {
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
        list->length++;
    }
    return list;
}


void remove_all(doubly_linked_list* list, int value) {
    list_node* current = list->head;
    for (int i = 0; i < list->length; i++) {
        if (current->value == value) {
            list_node* next = current->next;
            if (current != list->tail) {
                current->next->prev = current->prev;
            }
            else {
                list->tail = current->prev;
            }
            if (current != list->head) {
                current->prev->next = current->next;
            }
            else {
                list->head = current->next;
            }
            current = next;
            list->length--;
            i--;
        }
        else {
            current = current->next;
        }
    }
}

arr_with_length* filter_evens(int arr[], int length) {
    int evens = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i]%2 == 0) {
            evens++;
        }
    }
    int* evens_arr = malloc(sizeof(evens));
    int index = 0;
    for (int j = 0; j < length; j++) {
        if (arr[j]%2 == 0) {
            evens_arr[index] = arr[j];
            index++;
        }  
    }
    arr_with_length* returned_arr = malloc(sizeof(arr_with_length));
    returned_arr->length = evens;
    returned_arr->arr = evens_arr;
    return returned_arr;
}

void print_list(doubly_linked_list list) {
    list_node* current = list.head;
    printf("list printing\n");
    int iterations = 0;
    for (int i = 0; i < list.length; i++) {
        printf("value: %i. position: %i\n", current->value, iterations);
        if (current != list.tail) {
            current = current->next;
        }
        iterations++;
    }
    return;
}

void list_kill(doubly_linked_list* list) {
    list_node* current = list->head;
    for (int i = 0; i < list->length; i++) {
        if (current != list->tail) {
            current = current->next;
            free(current->prev);
        }
        else {
            free(current);
        }
    }   
    free(list);
}

int main() {
    doubly_linked_list* test_list = replicate(5,5);
    insert(test_list, 5, 3);
    print_list(*test_list);
    list_kill(test_list);
    return 0;
}

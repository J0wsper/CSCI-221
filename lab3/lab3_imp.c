#include <stdlib.h>
#include <stdio.h>
#include "lab3_imp.h"

int string_length(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* copy_string(char* str) {
    int len = string_length(str);
    char* copy = malloc(len * sizeof(char));
    for (int i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    return copy;
}

queue* create_queue() {
    queue* new_queue = malloc(sizeof(queue));
    new_queue->size = 0;
    new_queue->head = NULL;
    return new_queue;
}

void enqueue(queue* q, int value) {
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    if (q->size == 0) {
        q->head = new_node;
    } 
    else {
        new_node->next = q->head;
        q->head = new_node;
    }
    q->size++;
}

int dequeue(queue* q) {
    if (q->size <= 0) {
        return -1;
    }
    node* removed = q->head;
    if (q->head->next != NULL) {
        q->head = removed->next;
    }
    q->size--;
    int val = removed->value;
    free(removed);
    return val;
}

void delete_queue(queue* q) {
    node* curr = q->head;
    while (curr->next != NULL) {
        node* removed = curr;
        curr = curr->next;
        free(removed);
    }
    free(curr);
    free(q);
}

void print_queue(queue* q) {
    int index = 0;
    node* curr = q->head;
    while (curr != NULL) {
        printf("Node value at index %i: %i\n", index, curr->value);
        curr = curr->next;
        index++;
    }

}

void merge(queue* q, int* arr, int len) {
    for (int i = 0; i < len; i++) {
        node* new_node = malloc(sizeof(node));
        new_node->value = arr[i];
        if (q->size >= 0) {
            new_node->next = q->head;
        }
        q->head = new_node;
        q->size++;
    }
}

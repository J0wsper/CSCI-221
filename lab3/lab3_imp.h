#ifndef _LAB3_H_
#define _LAB3_H_

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct queue {
    int size;
    node* head;
} queue;

/** Takes no arguments and returns an empty queue*/
queue* create_queue();

/** Takes a pointer to a queue and a value and adds a node with that value to the top of the queue*/
void enqueue(queue*, int);

/** Takes a queue and removes the top node of the queue, returning that node's value*/
int dequeue(queue*);

/** Takes a queue and frees all of its associated memory*/
void delete_queue(queue*);

/** Takes a queue and prints every value in that queue*/
void print_queue(queue*);

/** Takes a queue, an array and the length of that array and adds the array elements to the queue, first element on the bottom*/
void merge(queue*, int*, int);

#endif //_LAB3_H_
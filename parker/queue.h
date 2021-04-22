// #ifndef QUEUE_H_
// #define QUEUE_H_

// typedef struct Node
// {
//     struct Node *next;
//     int *client_socket;
// } Node;

// #endif

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

struct node {
    struct node* next;
    int *client_socket;
};
typedef struct node node_t;

void enqueue(int *client_socket);
int* dequeue();

#endif
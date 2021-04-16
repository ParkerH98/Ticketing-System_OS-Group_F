#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct Node
{
    struct Node *next;
    int *client_socket;
} Node;

#endif
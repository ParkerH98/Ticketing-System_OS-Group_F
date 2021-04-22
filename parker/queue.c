// #include "queue.h"
#include <stdio.h>
// #include <stdlib.h>

// Node *head = NULL;
// Node *tail = NULL;

// void enqueue(int *client_socket)
// {
//     Node *new_node = malloc(sizeof(Node));
//     new_node->client_socket = client_socket;
//     new_node->next = NULL;
//     if (tail == NULL) {
//         head = new_node;
//     } else
//     {
//         tail->next = new_node;
//     }
//     tail = new_node;
// }

// int * dequeue()
// {
//     if (head == NULL)
//     {
//         return NULL;
//     }
//     else
//     {
//         int *result = head->client_socket;
//         Node *temp = head;
//         head = head->next;
//         if (head == NULL) { tail = NULL; }
//         free(temp);
//         return result;
//     }
// }

#include <stdlib.h>
#include "queue.h"

node_t *head = NULL;
node_t *tail = NULL;

void enqueue(int *client_socket)
{
    printf("ENQUEUE");
    node_t *newnode = malloc(sizeof(node_t));
    newnode->client_socket = client_socket;
    newnode->next = NULL;
    if (tail == NULL)
    {
        head = newnode;
    }
    else
    {
        tail->next = newnode;
    }
    tail = newnode;
}

//returns NULL if the queue is empty.
//Returns the pointer to a client_socket, if there is one to get
int *dequeue()
{
    if (head == NULL)
    {
        // printf("NULLL");
        return NULL;
    }
    else
    {
        printf("NOT NULLL");
        int *result = head->client_socket;
        node_t *temp = head;
        head = head->next;
        if (head == NULL)
        {
            tail = NULL;
        }
        free(temp);
        return result;
    }
}
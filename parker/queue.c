#include <stdio.h> // print statements
#include <stdlib.h> // malloc

#define QUEUE_SIZE 6

int intArray[QUEUE_SIZE];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek()
{
    return intArray[front];
}

int isEmpty()
{
    if (itemCount == 0)
    {
        return 1;
    }

    return 0;
}

int isFull()
{
    if (itemCount == QUEUE_SIZE)
    {
        return 1;
    }
    return 0;
}

int size()
{
    return itemCount;
}

void insert(int *data)
{
    if (itemCount != QUEUE_SIZE)
    {
        if (rear == QUEUE_SIZE - 1)
        {
            rear = -1;
        }

        intArray[++rear] = *data;
        itemCount++;
    }
    printf("QUEUE: Count --> %d\n", itemCount);
}

int *removeData()
{
    if (itemCount == 0)
    {
        return NULL;
    }

    int *data = malloc(sizeof(int));
    data = &intArray[front++];

    if (front == QUEUE_SIZE)
    {
        front = 0;
    }

    itemCount--;
    return data;
}

void printQueue()
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        printf(" %d -->", intArray[i]);
    }
}
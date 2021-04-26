#include <stdio.h> // print statements
#include <stdlib.h> // malloc

#define QUEUE_SIZE 6

int intArray[QUEUE_SIZE];
int head = 0;
int tail = -1;
int count = 0;

int peek()
{
    return intArray[head];
}

int isEmpty()
{
    if (count == 0)
    {
        return 1;
    }

    return 0;
}

int isFull()
{
    if (count == QUEUE_SIZE)
    {
        return 1;
    }
    return 0;
}

int size()
{
    return count;
}

void insert(int *data)
{
    if (count != QUEUE_SIZE)
    {
        if (tail == QUEUE_SIZE - 1)
        {
            tail = -1;
        }

        intArray[++tail] = *data;
        count++;
    }
    printf("QUEUE: Count --> %d\n", count);
}

int *removeData()
{
    if (count == 0)
    {
        return NULL;
    }

    int *data = malloc(sizeof(int));
    data = &intArray[head++];

    if (head == QUEUE_SIZE)
    {
        head = 0;
    }

    count--;
    return data;
}

void printQueue()
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        printf(" %d -->", intArray[i]);
    }
}
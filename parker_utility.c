#include "header.h"

// sem_t wrt;
// pthread_mutex_t mutex;
// int read_count = 0;

void writer()
{
    sem_wait(wrt);

    // CRITICAL SECTION
    // write operation here

    sem_post(wrt);
}

void reader()
{
    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&mutex);
    read_count++;

    // If this is the first reader, then it will block the writer
    if (read_count == 1)
    {
        sem_wait(wrt);
    }
    pthread_mutex_unlock(&mutex);

    // read operation here

    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&mutex);
    read_count--;

    // if this is the last reader, it will signal the writer
    if (read_count == 0)
    {
        sem_post(wrt);
    }
    pthread_mutex_unlock(&mutex);
}

// int main()
// {
//     pthread_mutex_init(&mutex, NULL);
//     sem_init(wrt, 0, 1);

//     pthread_mutex_destroy(&mutex);
//     sem_destroy(wrt);

//     return 0;
// }

int intArray[QUEUE_SIZE];
int head = 0;
int tail = -1;
int count = 0;

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

int printRandoms(int lower, int upper)
{
    // int i;
    // for (i = 0; i < count; i++)
    // {
    srand(time(NULL));
    int num = (rand() % (upper - lower + 1)) + lower;
    printf("%d ", num);
    // }

    return num;
}

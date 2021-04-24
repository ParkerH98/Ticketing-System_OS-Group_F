#include "../header.h"

sem_t wrt;
pthread_mutex_t mutex;
int read_count = 0;

void writer()
{
    sem_wait(&wrt);


    // CRITICAL SECTION
    // write operation here


    sem_post(&wrt);
}


void reader()
{
    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&mutex);
    read_count++;

    // If this is the first reader, then it will block the writer
    if (read_count == 1)
    {
        sem_wait(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
   

    // read operation here


    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&mutex);
    read_count--;

    // if this is the last reader, it will signal the writer
    if (read_count == 0)
    {
        sem_post(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
}

// int main()
// {
//     pthread_mutex_init(&mutex, NULL);
//     sem_init(&wrt, 0, 1);

//     pthread_mutex_destroy(&mutex);
//     sem_destroy(&wrt);

//     return 0;
// }
#include "parker_server.c"
#include "parker_utility.c"
#include "parker_rasheed.c"

// Usage Instructions:
// make s && ./s

int main()
{
    // initializes the mutex used when inserting/removing to/from the thread pool
    pthread_mutex_init(&mutex, NULL); 

    // creates NUM_SERVER number of processes that are servers
    for (int i = 0; i < NUM_SERVERS; i++)
    {
        if (fork() == 0)
        {
            serverSocket_SendReceive(PORT + i);
            exit(0);
        }
    }
    for (int i = 0; i < NUM_SERVERS; i++)
        wait(NULL);

    return 0;
}
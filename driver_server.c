#include "parker_server.c"
#include "parker_utility.c"
#include "rasheed.c"

void createTrainFiles();

// Usage Instructions:
// make s && ./s

int main()
{
    createTrainFiles();

    FILE *summary_fp = fopen("summary.txt", "w");
    fclose(summary_fp);

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
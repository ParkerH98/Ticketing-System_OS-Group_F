// Name: Parker Hague
// Email: phague@okstate.edu
// Group: F

#include "header.h"



/* -------------------------------------------------------------------------- */
/*                          SYNCHRONIZATION FUNCTIONS                         */
/* -------------------------------------------------------------------------- */



/*
Example reference of semaphores to handle writing in the 
critical section. Writer in the reader/writer problem.

@return void
*/
void writer()
{
    sem_wait(wrt);

    /* ---------------------------- CRITICAL SECTION ---------------------------- */

    /* -------------------------- write operation here -------------------------- */

    sem_post(wrt);
}



/*
Example reference of semaphores and mutex to handle multiple readers. 
Reader in the reader/writer problem.

@return void
*/
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

    /* --------------------------- read operation here -------------------------- */

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



/* -------------------------------------------------------------------------- */
/*                         THREAD POOL QUEUE FUNCTIONS                        */
/* -------------------------------------------------------------------------- */

int intArray[QUEUE_SIZE];
int head = 0;
int tail = -1;
int count = 0;



/*
Inserts a client socket connection into the queue so it
can be handled by a thread in the thread pool.

@param client_socket is an int pointer to the client's socket connection
@return void
*/
void insertConnection(int *client_socket)
{
    // if queue isn't full
    if (count != QUEUE_SIZE)
    {
        if (tail == QUEUE_SIZE - 1)
        {
            tail = -1;
        }

        intArray[++tail] = *client_socket;
        count++;
    }
}



/*
If available, removes the client connection socket from the top of the queue.

@return an int pointer of the client's socket connection
*/
int *removeConnection()
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



/*
Gets a random port number between the lower and upper 
range.

@param lower is an int of the lower bound inclusive
@return upper is an int of the upper bound exclusive
*/
int randomPort(int lower, int upper)
{
    srand(getpid());
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


/* -------------------------------------------------------------------------- */
/*                             PRIORITY FUNCTIONS                             */
/* -------------------------------------------------------------------------- */

// one space for each possible thread in the program
Priority priorities[NUM_SERVERS * THREAD_NUMBER];
int priority_head = 0;
int priority_tail = -1;
int priority_count = 0;



/*
Removes a Priority struct from the top of the queue of available.
The removed Priority will be the one with the highest priority.

@return a Priority struct being the one with the highest priority
*/
Priority removePriority()
{
    // if empty return a NULL Priority
    if (priority_count == 0)
    {
        Priority p;
        return p;
    }

    Priority *data = malloc(sizeof(Priority));
    data = &priorities[priority_head++];

    if (priority_head == QUEUE_SIZE)
    {
        priority_head = 0;
    }

    priority_count--;
    return *data;
}



/*
Inserts Priority struct onto the queue.

@param data is a Priority struct containing the client socket and priority
@return void
*/
void insertPriority(Priority data)
{
    if (priority_count != QUEUE_SIZE)
    {
        if (priority_tail == QUEUE_SIZE - 1)
        {
            priority_tail = -1;
        }

        priorities[++priority_tail] = data;
        priority_count++;
    }
}



/*
Performs a bubble sort on the Priority queue to get the Priority
with the highest priority. 

@return void
*/
void sortPriority()
{
    for (int i = 0; i < (NUM_SERVERS * THREAD_NUMBER) - 1; i++)
    {
        for (int j = 0; j < (NUM_SERVERS * THREAD_NUMBER) - 1; j++)
        {
            if (priorities[j].priority < priorities[j + 1].priority)
            {
                Priority temp = priorities[j + 1];
                priorities[j + 1] = priorities[j];
                priorities[j] = temp;
            }
        }
    }

    /* -------------------------- starvation avoidance -------------------------- */
    for (int i = 0; i < count; i++)
    {
        // increments the priority of all the remaining Priorities in the queue
        // this avoids starvation because if a Priority is in the queue
        // long enough its priority is gurantted to eventually be the highest
        (priorities->priority)++;
    }
}



/*
The main priority function that is called by the serverHandleSelection().

@param priority is a Priority struct associated with the current client socket
@return a Priority struct with the highest priority
*/
Priority customerPriority(Priority priority)
{
    insertPriority(priority);
    sortPriority();
    Priority highest_priority = removePriority();

    return highest_priority;
}
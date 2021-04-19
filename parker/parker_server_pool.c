#include "../header.h"
#include "queue.h"
void *handleConnection(void *client_socket);
int errorCheck(int returned, const char *errMsg);
int *dequeue();
void enqueue(int *client_socket);

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void serverSocket_SendReceive(int port)
{
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    errorCheck(entrySocket = socket(PF_INET, SOCK_STREAM, 0), "Error creating socket"); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(port); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Sets IP to accept from any IP address
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // errorCheck(bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)), "Error in bind"); //Bind the address struct to the socket
    bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket

    // Listen on the socket
    errorCheck(listen(entrySocket, BACKLOG), "Error listening");

    printf("SERVER: Listening on port %d\n", port);

    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

        pthread_t thread;
        int *client = malloc(sizeof(int));
        *client = connectionSocket;

        pthread_mutex_lock(&mutex);
        enqueue(client);
        pthread_mutex_unlock(&mutex);
    }
}

void * threadFunction(void * arg)
{
    while (1)
    {
        // pthread_mutex_lock(&mutex);
        int *client = dequeue();
        // pthread_mutex_unlock(&mutex);

        if (client != NULL)
        {
            handleConnection(client);
        }
    }
}

void * handleConnection(void * client_socket)
{
    int client = *((int*)client_socket); // casts void pointer to int pointer
    free(client_socket);

    printf("SERVER: Connected to client.\n");

    char message[256] = "What option would you like?";
    send(client, message, sizeof(message) + 1, 0);

    char answer[2];
    recv(client, answer, sizeof(answer) + 1, 0); //Read the message from the server into the buffer
    printf("SERVER: Selection [%s] was chosen by the customer.\n", answer);
    close(client);
    return NULL;
}

int errorCheck(int returned, const char *errMsg)
{
    if (returned == -1)
    {
        perror(errMsg);
        exit(1);
    }
    else
        return 1;
}

int main()
{
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, threadFunction, NULL);
    }

        for (int i = 0; i < NUM_SERVERS; i++) // loop will run n times (n=5)
        {
            if (fork() == 0)
            {
                serverSocket_SendReceive(PORT + i);

                // printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
                exit(0);
            }
        }
    for (int i = 0; i < NUM_SERVERS; i++) // loop will run n times (n=5)
        wait(NULL);

    return 0;
}
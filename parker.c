#include "header.h"

//========================
//   parker_semaphore.c
//========================

void *handleConnection(void *client_socket);
int errorCheck(int returned, const char *errMsg);
void *waitForWork(void *);
int *removeData();
void insert(int *data);

pthread_mutex_t mutex;
pthread_cond_t condition_thread = PTHREAD_COND_INITIALIZER;


void serverSocket_SendReceive(int port)
{
    pthread_t thread_pool[THREAD_NUMBER];

    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        pthread_create(&thread_pool[i], NULL, waitForWork, NULL);
    }

    int entrySocket, connectionSocket; // socket file descriptors
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    errorCheck(entrySocket = socket(PF_INET, SOCK_STREAM, 0), "Error creating socket"); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(port);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                //Sets IP to accept from any IP address
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    errorCheck(bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)), "Error in bind"); //Bind the address struct to the socket

    errorCheck(listen(entrySocket, BACKLOG), "Error listening");

    printf("SERVER: Listening on port %d\n", port);

    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof(serverStorage);
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);
        printf("SERVER: Connected to client\n");

        int *client_socket = malloc(sizeof(int));
        *client_socket = connectionSocket;

        //make sure only one thread messes with the queue at a time
        pthread_mutex_lock(&mutex);
        insert(client_socket);
        pthread_cond_signal(&condition_thread);
        pthread_mutex_unlock(&mutex);
    }
}


void *waitForWork(void *arg)
{
    while (1)
    {
        int *client_socket;

        pthread_mutex_lock(&mutex);

        pthread_cond_wait(&condition_thread, &mutex);
        client_socket = removeData();

        pthread_mutex_unlock(&mutex);

        if (client_socket != NULL)
        {
            handleConnection(client_socket);
        }
    }
}


void *handleConnection(void *client)
{
    int client_socket = *((int *)client);

    printf("SERVER: Connected to client.\n");

    char message[256] = "\n========================\n    Reservation Menu\n========================\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n";
    send(client_socket, message, sizeof(message) + 1, 0);

    char selection[2];
    recv(client_socket, selection, sizeof(selection) + 1, 0); //Read the message from the server into the buffer
    printf("SERVER: Selection [%s] was chosen by the customer.\n", selection);
    fflush(stdout);

    initializeCust();

    if (selection == 1)
    {
        reserveSeats();
    }
    else if (selection == 2)
    {
        // inquiry();
    }
    else if (selection == 3)
    {
        // modifyReservation();
    }
    else if (selection == 4)
    {
        // cancelReservation();
    }
    else if (selection == 5)
    {
        exit(0);
    }

    close(client_socket);
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





//========================
//   parker_client.c
//========================

void clientSocket_SendReceive(int port)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // sets values: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(port);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");           //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("CLIENT: Connected at port %d\n", port);

    char received[256];
    read(clientSocket, received, sizeof(received) + 1);
    printf("%s\n", received);

    char selection[2];
    // scanf("%s", selection);
    // int num = (rand() % (11 - 0 + 1)) + 0;
    // sprintf(selection, "%d", num);
    strcpy(selection, "1");
    send(clientSocket, selection, sizeof(selection) + 1, 0);

    close(clientSocket);
}


int printRandoms(int lower, int upper)
{
    int i;
    // for (i = 0; i < count; i++)
    // {
    srand(time(NULL));
    int num = (rand() % (upper - lower + 1)) + lower;
    printf("%d ", num);
    // }

    return num;
}




//========================
//   parker_semaphore.c
//========================

// sem_t wrt;
// pthread_mutex_t mutex;
read_count = 0;

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




//========================
//   parker_semaphore.c
//========================

#define QUEUE_SIZE 6

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
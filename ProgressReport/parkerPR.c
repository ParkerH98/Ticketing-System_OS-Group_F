
#include "../header.h"

// this is a test for you guys
void *handleConnection(void *client_socket);
int errorCheck(int returned, const char *errMsg);

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

    char received[256];
    read(clientSocket, received, sizeof(received) + 1);
    printf("%s\n", received);

    char selection[2];
    // scanf("%s", selection);
    int num = (rand() % (11 - 0 + 1)) + 0;
    sprintf(selection, "%d", num);
    // strcpy(selection, "1");
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

// int main()
// {
//     // int port = printRandoms(PORT, PORT + 4);

//     clientSocket_SendReceive(PORT);
//     return 0;
// }


pthread_t thread_pool[THREAD_POOL_SIZE];

void serverSocket_SendReceive(int port)
{
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    entrySocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(port);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                //Sets IP to accept from any IP address
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    if (bindCheck < 0)
    {
        perror("[-]Error in bind");
        exit(1);
    }

    // Listen on the socket, with 5 max connection requests queued
    if (listen(entrySocket, BACKLOG) == 0)
    {
        printf("SERVER: Listening....\n");
    }
    else
    {
        printf("[-]Error in listening");
    }

    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;

        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);
        printf("SERVER: Connected to client.\n");

        char message[256] = "What option would you like?";
        send(connectionSocket, message, sizeof(message) + 1, 0);

        char answer[2];
        recv(connectionSocket, answer, sizeof(answer) + 1, 0); //Read the message from the server into the buffer
        printf("SERVER: Selection [%s] was chosen by the customer.\n", answer);
    }
}

void *handleConnection(void *client_socket)
{
    int client = *((int *)client_socket); // casts void pointer to int pointer
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
    return 1;
}

// int main()
// {
//     for (int i = 0; i < NUM_SERVERS; i++) // loop will run n times (n=5)
//     {
//         if (fork() == 0)
//         {
//             serverSocket_SendReceive(PORT + i);

//             // printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
//             exit(0);
//         }
//     }
//     for (int i = 0; i < NUM_SERVERS; i++) // loop will run n times (n=5)
//         wait(NULL);

//     return 0;
// }
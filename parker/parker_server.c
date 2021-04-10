#include "../header.h"

void serverSocket_SendReceive()
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
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                //Sets IP to accept from any IP address
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    if (bindCheck < 0)
    {
        perror("[-]Error in bind");
        exit(1);
    }

    // Listen on the socket, with 5 max connection requests queued
    if (listen(entrySocket, 5) == 0)
    {
        printf("SERVER: Listening....\n");
    }
    else
    {
        printf("[-]Error in listening");
    }

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

int main()
{
    serverSocket_SendReceive();
    return 0;
}
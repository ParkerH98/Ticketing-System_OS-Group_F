
#include "../header.h"


// this is a test for you guys

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

    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(port); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set IP address to localhost
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

int main()
{
    // int port = printRandoms(PORT, PORT + 4);

    clientSocket_SendReceive(PORT);
    return 0;
}


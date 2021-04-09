#include "../header.h"

/*
---------------------------------------------------------
THIS IS A FULLY WORKING TEST FUNCTION. THIS IS NOT IMPLEMENTED
IN THE PROGRAM. WE DECIDED TO USE JOONMO'S SERVER FUNCTION INSTEAD.

This function handles all socket connections on the server side.
This functions binds and then begins listening for incoming
client connections. The function then sends a result to the 
client.

Params: none
Return: void
*/
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

    // for (int i = 0; i < TESTING_LOOP; i++)
    // {
    //     // Accept call creates a new socket for the incoming connection
    //     addr_size = sizeof serverStorage;
    //     connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

    //     struct Query query;
    //     struct Query *queryPtr = &query;

    //     recv(connectionSocket, queryPtr, sizeof(struct Query), 0);                                                                      //Read the message from the server into the buffer
    //     printf("SERVER: Query received from assistant:\n\n%s\n%s\n%s\n", queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); //Print the received message

    //     struct EmployeeStructure employee;
    //     struct EmployeeStructure *employeePtr = &employee;

    //     employeePtr->id = 15000;
    //     strcpy(employeePtr->employeeName, "BRIAN BENSON");
    //     strcpy(employeePtr->jobTitle, "IS BUSINESS ANALYST");
    //     employeePtr->basePay = 78059.8;
    //     employeePtr->overtimePay = 0;
    //     employeePtr->benefit = 0;
    //     strcpy(employeePtr->status, "FT");
    //     employeePtr->satisfactionLevel = 0.37;
    //     employeePtr->numberProject = 2;
    //     employeePtr->averageMonthlyHours = 158;
    //     employeePtr->yearsInCompany = 3;
    //     employeePtr->workAccident = 0;
    //     employeePtr->promotionsLast5Years = 0;

    //     send(connectionSocket, employeePtr, sizeof(struct EmployeeStructure), 0);
    //     printf("\nSERVER: Result sent to assistant.\n\n");
    // }
}
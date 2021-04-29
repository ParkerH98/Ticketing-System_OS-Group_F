#include "header.h"

int *removeData();
void insert(int *data);
void cancellation(int *ticket);
void reserveSeats(struct Customer *customer);

pthread_mutex_t mutex;
pthread_cond_t condition_thread = PTHREAD_COND_INITIALIZER;

void serverHandleSelection(int selection, int client_socket)
{
    //==============================
    //    Make Ticket Reservation
    //==============================
    if (selection == 1)
    {
        struct Customer customer;
        struct Customer *customer_ptr = &customer;

        recv(client_socket, customer_ptr, sizeof(struct Customer), 0);

        printf("Order Received:\n");
        printf("ID: %d\n", customer.receipt_id);
        printf("Name: %s\n", customer_ptr->name);
        printf("DOB: %c\n", customer.dob);
        printf("Gender: %c\n", customer.gender);
        printf("Government ID: %d\n", customer.govt_id);
        printf("Travel Date: %d\n", customer.travel_date);
        printf("Number of Travelers: %d\n", customer.num_traveler);
        printf("Seats Chosen: \n");
        for (int i = 0; i < NUM_SEATS; i++)
        {
            printf("%d ", customer.seats[i]);
        }
        printf("\n\n");

        reserveSeats(customer_ptr);
    }


    //==============================
    //     Make Ticket Inquiry
    //==============================
    else if (selection == 2)
    {
        // inquiry();
    }


    //==============================
    //   Make Ticket Modification
    //==============================
    else if (selection == 3)
    {
        // modifyReservation();
    }


    //==============================
    //   Make Ticket Cancellation
    //==============================
    else if (selection == 4)
    {
        int *ticket_num = NULL;

        recv(client_socket, ticket_num, sizeof(ticket_num), 0);

        cancellation(ticket_num);
    }


    //==============================
    //       Exit The Program
    //==============================
    else if (selection == 5)
    {
        exit(0);
    }
}

void *handleConnection(void *client)
{
    int client_socket = *((int *)client);

    printf("SERVER: Connected to client.\n");

    char menu[256] = "\n========================\n    Reservation Menu\n========================\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n";
    send(client_socket, menu, sizeof(menu), 0);

    char selection[2];
    recv(client_socket, selection, sizeof(selection), 0);
    printf("SERVER: Selection [%s] was chosen by the customer.\n", selection);
    fflush(stdout);

    serverHandleSelection(atoi(selection), client_socket);

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
// Name: Parker Hague
// Email: phague@okstate.edu
// Group: F

#include "header.h"

void *handleConnection(void *client, int *port);
void *waitForWork(void *port);
int errorCheck(int returned, const char *errMsg);

pthread_mutex_t mutex;
pthread_cond_t condition_thread = PTHREAD_COND_INITIALIZER;



/* -------------------------------------------------------------------------- */
/*                              SERVER FUNCTIONS                              */
/* -------------------------------------------------------------------------- */



/*
This is the main server function. It handles all of the server
setup including listening and binding. It also all creates the
thread pool and spawns the threads that run the waitForWork() 
in the pool. As connections are accepted by the server, they're
placed onto the queue (insertConnection()) so a thread from the 
thread pool (waitForWork()) can handle the connection (handleConnection())

@param an int representing the port number that the server will run on
@return void
*/
void serverSocket_SendReceive(int port)
{
    // an array of threads representing the thread pool
    pthread_t thread_pool[THREAD_NUMBER];

    // each created thread will run the waitForWork() which will infinitely loop and check for connections
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        pthread_create(&thread_pool[i], NULL, waitForWork, &port);
    }

    // typedef the structs to clean up the server code
    typedef struct sockaddr_in SA_IN;
    typedef struct sockaddr SA;

    int entrySocket, connectionSocket, addr_size;
    SA_IN server_addr, client_addr;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    errorCheck(entrySocket = socket(PF_INET, SOCK_STREAM, 0), "Error creating socket"); // Create the socket

    // Configure settings of the server address struct
    server_addr.sin_family = AF_INET;                //Address family = Internet
    server_addr.sin_port = htons(port);              //Set port number, using htons function to use proper byte order
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //Sets IP to accept from any IP address

    // bind and listen
    errorCheck(bind(entrySocket, (struct sockaddr *)&server_addr, sizeof(server_addr)), "Error in bind"); //Bind the address struct to the socket
    errorCheck(listen(entrySocket, BACKLOG), "Error listening");

    printf("SERVER: Listening on port %d\n", port);

    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof(SA_IN);
        connectionSocket = accept(entrySocket, (SA *)&client_addr, (socklen_t *)&addr_size);
        printf("SERVER: Connected to client at port %d\n", port);

        int *client_socket = malloc(sizeof(int));
        *client_socket = connectionSocket;

        // locks the mutex so we can insert a connection onto the queue ~ needed for multithreaded synchronization
        pthread_mutex_lock(&mutex);

        insertConnection(client_socket);

        // signals the condition variable to quit waiting now that a connection is available
        // this was used to eliminate "busy waiting"
        pthread_cond_signal(&condition_thread);

        // unlocks or "releases" the mutex so another thread can use it
        pthread_mutex_unlock(&mutex);
    }
}



/*
This function is called by handleConnection() and carries out
the operations chosen by the client's selection. The possible 
operations include reserving, inquiring, modifying, and canceling
a ticket.

@param selection is an int representing the customer's menu selection
@param client_socket is an int containing the client socket connection
@return void
*/
void serverHandleSelection(int selection, int client_socket, int *port)
{
    while (1)
    {
        /* -------------------------------------------------------------------------- */
        /*                           MAKE TICKET RESERVATION                          */
        /* -------------------------------------------------------------------------- */
        if (selection == 1)
        {
            // assigning pointer copy because recv() wants a pointer to store the data in
            struct Customer customer;
            struct Customer *customer_ptr = &customer;

            // receives the Customer struct from the client
            recv(client_socket, customer_ptr, sizeof(struct Customer), 0);

            printf("\n\n===================Order Received===================\n");
            printf("Name: %s\n", customer.name);
            printf("DOB: %d\n", customer.dob);
            printf("Gender: %c\n", customer.gender);
            printf("Government ID: %d\n", customer.govt_id);
            printf("Travel Date: %d\n", customer.travel_date);
            printf("Number of Travelers: %d\n", customer.num_traveler);
            printf("Seats Chosen: \n\n");
            printf("===================");

            for (int i = 0; i < NUM_SEATS - 1; i++)
            {
                if (i % 10 == 0)
                    printf("\n");
                printf("%d ", customer.seats[i]);
            }
            printf("\n===================");
            printf("\n\n");

            Priority priority_attributes;
            priority_attributes.priority = customer.num_traveler;
            priority_attributes.client_socket = client_socket;

            priority_attributes = customerPriority(priority_attributes);

            reserveSeats(customer_ptr, priority_attributes.client_socket, port);

            sendReceiptToCust(customer, client_socket, port);

            // receives the client's selection and continues the loop if they don't choose to exit
            recv(client_socket, &selection, sizeof(selection), 0);
            continue;
        }

        /* -------------------------------------------------------------------------- */
        /*                             MAKE TICKET INQUIRY                            */
        /* -------------------------------------------------------------------------- */
        else if (selection == 2)
        {
            // receives the customer's ticket number
            int ticket_num;
            recv(client_socket, &ticket_num, sizeof(ticket_num), 0);

            inquiry(ticket_num, client_socket);

            // receives the client's selection and continues the loop if they don't choose to exit
            recv(client_socket, &selection, sizeof(selection), 0);
            continue;
        }

        /* -------------------------------------------------------------------------- */
        /*                          MAKE TICKET MODIFICATION                          */
        /* -------------------------------------------------------------------------- */
        else if (selection == 3)
        {
            // receives the customer's ticket number
            int ticket_num;
            recv(client_socket, &ticket_num, sizeof(ticket_num), 0);

            modify(ticket_num, client_socket, port);

            // receives the client's selection and continues the loop if they don't choose to exit
            recv(client_socket, &selection, sizeof(selection), 0);
            continue;
        }

        /* -------------------------------------------------------------------------- */
        /*                          MAKE TICKET CANCELLATION                          */
        /* -------------------------------------------------------------------------- */
        else if (selection == 4)
        {
            // receives the customer's ticket number
            int ticket_num;
            recv(client_socket, &ticket_num, sizeof(ticket_num), 0);

            printf("Ticket number received: %d\n", ticket_num);

            cancellation(&ticket_num, client_socket);

            // receives the client's selection and continues the loop if they don't choose to exit
            recv(client_socket, &selection, sizeof(selection), 0);
            continue;
        }

        /* -------------------------------------------------------------------------- */
        /*                              EXIT THE PROGRAM                              */
        /* -------------------------------------------------------------------------- */
        else if (selection == 5)
        {
            exit(0);
        }
    }
}



/*
This function is meant to clean up the server code and reduce
the number of 'if' and 'print' statements. It takes advantage
of the fact that most of the socket functions return -1 if 
there was an error.

@param returned is what the input function returns 
@param errMsg is the message you want to print if the input function fails
@return an int representing the success/failure
*/
int errorCheck(int returned, const char *errMsg)
{
    // prints error message if -1 is returned by the input function
    if (returned == -1)
    {
        perror(errMsg);
        exit(1);
    }
    else
        return 1;
}



/* -------------------------------------------------------------------------- */
/*                              THREAD FUNCTIONS                              */
/* -------------------------------------------------------------------------- */



/*
This function servers as the manager for the thread pool. This
function also handles the synchronization amongst all the threads.
The threads will wait in the thread pool. Once a client_socket
is put onto the queue, an available thread will begin to 
handle the client socket connection.

@param *arg because thread functions must accept and return pointers
@return void *
*/
void *waitForWork(void *port)
{
    // threads infinitely check for work while the program is active
    while (1)
    {
        int *client_socket;

        // locks a mutex so a thread can remove a client_socket from the queue (if it's available)
        // this is done for multithreaded synchronization
        pthread_mutex_lock(&mutex);

        // This uses a condition variable and mutex lock to allow the threads to not have to constantly
        // loop the while() and check for work. This eliminates "busy waiting" thus dramatically improving
        // the resources used by the server
        pthread_cond_wait(&condition_thread, &mutex);

        // client socket is being set to the client_socket at the top of the queue
        client_socket = removeConnection();

        // unlocks or "returns" the mutex to allow another thread to access the lock now that removal has finished
        pthread_mutex_unlock(&mutex);

        // if the client_socket is NULL then there isn't any connections currently available in the
        // queue, else, allow a thread to handle the connection since one was pulled from the queue
        if (client_socket != NULL)
        {
            handleConnection(client_socket, port);
        }
    }
}



/*
This function is executed by threads that handle the client 
conenctions. This function gets called in the waitForWork()
once a connection has been placed into the queue. This function 
sends the menu to the client and then calls serverHandleSelection()
to handle the user's menu selection.

@param void * referenceing the client socket connection
@return void * because it's a thread function
*/
void *handleConnection(void *client, int *port)
{
    // justs casts the input pointer socket to an integer
    int client_socket = *((int *)client);

    // sends the menu to the client
    char menu[256] = "\n\n\n========================\n    Reservation Menu\n========================\n\nPlease choose a selection.\n\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n";
    send(client_socket, menu, sizeof(menu), 0);

    // receives the clients menu selection
    char selection[2];
    recv(client_socket, selection, sizeof(selection), 0);

    // function handles the client's menu selection (reserve, inquire, modify, cancel, & exit)
    serverHandleSelection(atoi(selection), client_socket, port);

    close(client_socket);
    return NULL;
}
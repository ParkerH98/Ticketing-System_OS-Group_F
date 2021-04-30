#include "header.h"

int *removeData();
void insertConnection(int *data);
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
        // assigning poointer copy because recv() wants a pointer to store the data in
        struct Customer customer;
        struct Customer *customer_ptr = &customer;

        // receives the Customer struct from the client
        recv(client_socket, customer_ptr, sizeof(struct Customer), 0);

        printf("Order Received:\n");
        printf("ID: %d\n", customer.receipt_id);
        printf("Name: %s\n", customer_ptr->name);
        printf("DOB: %d\n", customer.dob);
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

        // assertion to check a string and int
        assert(strcmp(customer.name, "Parker") == 0);
        assert(customer.dob == 19980418);

        // funcion handles the file operations necessary to reserve seats
        
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
    // justs casts the input pointer socket to an integer
    int client_socket = *((int *)client);

    printf("SERVER: Connected to client.\n");

    // sends the menu to the client
    char menu[256] = "\n========================\n    Reservation Menu\n========================\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n";
    send(client_socket, menu, sizeof(menu), 0);

    // receives the clients menu selection
    char selection[2];
    recv(client_socket, selection, sizeof(selection), 0);

    printf("SERVER: Selection [%s] was chosen by the customer.\n\n", selection);
    fflush(stdout);

    // function handles the client's menu selection (reserve, inquire, modify, cancel, & exit)
    serverHandleSelection(atoi(selection), client_socket);

    close(client_socket);
    return NULL;
}


/*
-------------------------------------------------------------
This function is meant to clean up the server code and reduce
the number of 'if' and 'print' statements. It takes advantage
of the fact that most of the socket functions return -1 if 
there was an error.

@param returned is what the input function returns 
@param errMsg is the message you want to print if the input function fails
@return: an int representing the success/failure
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


/*
-------------------------------------------------------------
This function servers as the manager for the thread pool. This
function also handles the synchronization amongst all the threads.
The threads will wait in the thread pool. Once a client_socket
is put onto the queue, an available thread will begin to 
handle the client socket connection.

@param *arg because thread functions must accept and return pointers
@return: void *
*/
void * waitForWork(void *arg)
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
        client_socket = removeData();

        // unlocks or "returns" the mutex to allow another thread to access the lock now that removal has finished
        pthread_mutex_unlock(&mutex);

        // if the client_socket is NULL then there isn't any connections currently available in the
        // queue, else, allow a thread to handle the connection since one was pulled from the queue
        if (client_socket != NULL)
        {
            handleConnection(client_socket);
        }
    }
}

/*
-------------------------------------------------------------
This is the main server function. It handles all of the server
setup including listening and binding. It also all creates the
thread pool and spawns the threads that run the waitForWork() 
in the pool. As connections are accepted by the server, they're
placed onto the queue (insertConnection()) so a thread from the 
thread pool (waitForWork()) can handle the connection (handleConnection())


@param an int representing the port number that the server will run on
@return: void
*/
void serverSocket_SendReceive(int port)
{
    // an array of threads representing the thread pool
    pthread_t thread_pool[THREAD_NUMBER];

    // each created thread will run the waitForWork() which will infinitely loop and check for connections
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        pthread_create(&thread_pool[i], NULL, waitForWork, NULL);
    }

    // typedef the structs to clean up the server code
    typedef struct sockaddr_in SA_IN;
    typedef struct sockaddr SA;

    int entrySocket, connectionSocket, addr_size;
    SA_IN server_addr, client_addr;
    
    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    errorCheck(entrySocket = socket(PF_INET, SOCK_STREAM, 0), "Error creating socket"); // Create the socket

    // Configure settings of the server address struct
    server_addr.sin_family = AF_INET;                               //Address family = Internet
    server_addr.sin_port = htons(port);                             //Set port number, using htons function to use proper byte order
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);                //Sets IP to accept from any IP address

    // bind and listen
    errorCheck(bind(entrySocket, (struct sockaddr *)&server_addr, sizeof(server_addr)), "Error in bind"); //Bind the address struct to the socket
    errorCheck(listen(entrySocket, BACKLOG), "Error listening");

    printf("SERVER: Listening on port %d\n", port);

    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof(SA_IN);
        connectionSocket = accept(entrySocket, (SA *)&client_addr, (socklen_t *)&addr_size);
        printf("SERVER: Connected to client\n");

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
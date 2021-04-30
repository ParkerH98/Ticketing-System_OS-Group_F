#include "header.h"

struct Customer reserveInformationFromUser();
void promptMenu(int *selection);

void clientHandleSelection(int selection, void *client)
{
    int client_socket = *((int *)client);

    while(1)
    {
        //==============================
        //    Make Ticket Reservation
        //==============================
        if (selection == 1)
        {
            struct Customer customer;
            struct Customer *customer_ptr = &customer;

            customer = reserveInformationFromUser();

            printf("Order Preview:\n");
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

            // printf("Order Confirmation:\nAre you sure you want to place this order (Y or N)?\n");

            char answer[2];
            // scanf("%s", answer);
            sprintf(answer, "%s", "y");

            if ((strcmp(answer, "Y") == 0) || (strcmp(answer, "y") == 0))
            {
                send(client_socket, customer_ptr, sizeof(struct Customer), 0);

                printf("Reservation completed. You will now be brought back to the main menu.\n\n\n");

                promptMenu(&selection);
                send(client_socket, &selection, sizeof(selection), 0);
                continue;
            }
            else
            {
                printf("Were sorry you changed your mind. Come back next time.\n");
                exit(0);
            }
        }


        //==============================
        //      Ticket Inquiry
        //==============================
        else if (selection == 2)
        {
            // inquiry();
        }


        //==============================
        //    Ticket Modification
        //==============================
        else if (selection == 3)
        {
            printf("\nPlease enter a ticket number to modify: ");

            // gets ticket number and sends to server
            int ticket_num;
            scanf("%d", &ticket_num);
            send(client_socket, &ticket_num, sizeof(ticket_num), 0);

            // receives server modification message
            // char modification_message[512];
            // recv(client_socket, modification_message, sizeof(modification_message), 0);

            // printf("%s", modification_message);

            // struct Customer modified_cust;
            // struct Customer *modified_cust_ptr = &modified_cust;

            // modified_cust = reserveInformationFromUser();

            // strcpy(modified_cust.name, "ChangedName");
            // modified_cust.dob = 123456;
            // modified_cust.gender = 'F';
            // modified_cust.govt_id = 1234;
            // modified_cust.travel_date = 123456;
            // modified_cust.num_traveler = 1;
            // modified_cust.seats[0] = 1;

            send(client_socket, modified_cust_ptr, sizeof(struct Customer), 0);

            printf("Modification completed. You will now be brought back to the main menu.\n\n\n");

            promptMenu(&selection);
            send(client_socket, &selection, sizeof(selection), 0);
            continue;
        }


        //==============================
        //    Ticket Cancellation
        //==============================
        else if (selection == 4)
        {
            int ticket_num;
            char confirmation_msg[1024];

            printf("\nWhat is your ticket number?\n");
            scanf("%d", &ticket_num);

            // sends the ticket number to the server
            send(client_socket, &ticket_num, sizeof(ticket_num), 0);

            // receives cancellation confirmation message
            recv(client_socket, confirmation_msg, sizeof(confirmation_msg), 0);

            printf("%s", confirmation_msg);

            char answer[2];
            scanf("%s", answer);

            if ((strcmp(answer, "Y") == 0) || (strcmp(answer, "y") == 0))
            {
                send(client_socket, answer, sizeof(answer), 0);
            }

            printf("Cancellation completed. You will now be brought back to the main menu.\n\n\n");

            promptMenu(&selection);
            send(client_socket, &selection, sizeof(selection), 0);
            continue;
        }


        //==============================
        //       Exit The Program
        //==============================
        else if (selection == 5)
        {
            exit(0);
        }
    }
}

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
    int *client_socket_ptr = malloc(sizeof(int));
    *client_socket_ptr = clientSocket;

    printf("CLIENT: Connected at port %d\n", port);

    char menu[256];
    read(clientSocket, menu, sizeof(menu));
    printf("%s\n", menu);

    char selection[2];
    scanf("%s", selection);

    // for automation
    // sprintf(selection, "%d", num);
    // strcpy(selection, "1");

    send(clientSocket, selection, sizeof(selection), 0);

    clientHandleSelection(atoi(selection), client_socket_ptr);

    close(clientSocket);
}

void promptMenu(int *selection)
{
    printf("\n========================\n    Reservation Menu\n========================\n\nPlease choose a selection.\n\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n");

    scanf("%d", selection);
}
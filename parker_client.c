#include "header.h"

void promptMenu(int *selection);

/*
This function is called by clientSocket_SendReceive() and 
handles the client's menu selection. 

@param selection is an int representing the customer's menu selection
@param client_socket is an int containing the client socket connection
@return void
*/
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

            customer = getInformationFromUser();

            printf("\n\n===================Order Preview===================\n");
            printf("Name: %s\n", customer_ptr->name);
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

            printf("Order Confirmation:\nAre you sure you want to place this order (Y or N)?\n");

            char answer[2];
            scanf("%s", answer);
            // sprintf(answer, "%s", "y");

            if ((strcmp(answer, "Y") == 0) || (strcmp(answer, "y") == 0))
            {
                send(client_socket, customer_ptr, sizeof(struct Customer), 0);

                printf("Reservation completed. You will now be brought back to the main menu.\n\n");

                char customer_receipt[4096];

                recv(client_socket, customer_receipt, sizeof(customer_receipt), 0);

                printf("%s", customer_receipt);

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
            printf("\nPlease enter a ticket number for inquiry: ");

            // gets ticket number and sends to server
            int ticket_num;
            scanf("%d", &ticket_num);
            send(client_socket, &ticket_num, sizeof(ticket_num), 0);

            char inquiry_msg[1024];
            recv(client_socket, inquiry_msg, sizeof(inquiry_msg), 0);
            printf("%s", inquiry_msg);

            promptMenu(&selection);
            send(client_socket, &selection, sizeof(selection), 0);
            continue;
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

      

            // automated for testing
            // strcpy(modified_cust.name, "Parker");
            // modified_cust.dob = 19980418;
            // modified_cust.gender = 'M';
            // modified_cust.govt_id = 56441;
            // modified_cust.travel_date = 1;
            // modified_cust.receipt_id = ticket_num;


            send(client_socket, &ticket_num, sizeof(ticket_num), 0);

            // receives server modification message
            char modification_message[512];
            recv(client_socket, modification_message, sizeof(modification_message), 0);
            printf("%s", modification_message);

            struct Customer modified_cust;
            struct Customer *modified_cust_ptr = &modified_cust;

            printf("Please enter your credentials as prompted.\n\n");
            printf("Name: ");
            char Name[50];
            scanf(" %s", Name);
            strcpy(modified_cust.name, Name);
            printf("Date of Birth(YYYYMMDD): ");
            scanf("%d", &modified_cust.dob);
            printf("Gender (M or F): ");
            scanf(" %c", &modified_cust.gender);
            printf("Government ID: ");
            scanf("%d", &modified_cust.govt_id);
            printf("Available dates of travel: 1 or 2.\nSelect One: ");
            scanf("%d", &modified_cust.travel_date);
            printf("Number of Travelers: ");
            scanf("%d", &modified_cust.num_traveler);

            // printf("Number of Travelers: ");
            // scanf("%d", &modified_cust.num_traveler);

            // Sets all the values of the seats[] to be 0. This fixes a bug where unexpected values were present in the array.
            for (int i = 0; i < NUM_SEATS; i++)
            {
                modified_cust.seats[i] = 0;
            }

            printTrain(modified_cust.travel_date);

            printf("Enter your desired seats to reserve:\n");

            // sets the desired customer's seats' indices to be 1
            for (int i = 0; i < modified_cust.num_traveler; i++)
            {
                printf("Choose seat for ticket %d/%d: ", i + 1, modified_cust.num_traveler);
                int temp;
                scanf("%d", &temp);
                modified_cust.seats[temp - 1] = 1;
            }

            printf("\n\n===================Modified Customer===================\n");
            printf("Name: %s\n", modified_cust.name);
            printf("DOB: %d\n", modified_cust.dob);
            printf("Gender: %c\n", modified_cust.gender);
            printf("Government ID: %d\n", modified_cust.govt_id);
            printf("Travel Date: %d\n", modified_cust.travel_date);
            printf("Number of Travelers: %d\n", modified_cust.num_traveler);
            printf("Seats Chosen: \n");
            printf("===================\n");
            for (int i = 0; i < NUM_SEATS; i++)
            {
                printf("%d", modified_cust.seats[i]);
            }
            printf("\n===================");

            printf("\n\n");

            send(client_socket, modified_cust_ptr, sizeof(struct Customer), 0);

            printf("Modification completed. You will now be brought back to the main menu.\n\n");

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

            printf("Cancellation completed. You will now be brought back to the main menu.\n\n");

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

    // gets user's selection and sends to server
    char selection[2];
    scanf("%s", selection);
    send(clientSocket, selection, sizeof(selection), 0);

    clientHandleSelection(atoi(selection), client_socket_ptr);

    close(clientSocket);
}

void promptMenu(int *selection)
{
    printf("\n========================\n    Reservation Menu\n========================\n\nPlease choose a selection.\n\n1: Make a reservation\n2: Inquiry about the ticket\n3: Modify the reservation\n4: Cancel the reservation\n5: Exit the program\n");

    scanf("%d", selection);
}
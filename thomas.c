#include "header.h"

void sendReceiptToCust(struct Customer customer, int client_socket, int *port)
{
    FILE *summary_fp = fopen("summary.txt", "a");

    char customer_receipt[4096];
    char selected_seats[256];

    for (int i = 0; i < NUM_SEATS - 1; i++)
    {
        if (i % 10 == 0)
            strcat(selected_seats, "\n");
        char temp[50];
        sprintf(temp, "%d ", customer.seats[i]);
        strcat(selected_seats, temp);
    }

    sprintf(customer_receipt, "\n\n===================Order Receipt===================\nServer ID: %d\nReceipt ID: %d\nName: %s\nDOB: %d\nGovernment ID: %d\nTravel Day: %d\nNumber of Travelers: %d\nSeats Selected: \n===================%s\n===================\n\n",
            *port, customer.receipt_id, customer.name, customer.dob, customer.govt_id, customer.travel_date, customer.num_traveler, selected_seats);

    fclose(summary_fp);
    send(client_socket, customer_receipt, sizeof(customer_receipt), 0);

    strcpy(selected_seats, "");
}
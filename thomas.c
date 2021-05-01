#include "header.h"

char customer_receipt[1024];

void sendReceiptToCust(struct Customer customer, int client_socket)
{
    printf("Here is your receipt with receipt ID number %d\n", customer.receipt_id);

    printf("{\n\tReceipt Number : %d,\n\
        Customer name: %u,\n\
        Government ID: %u,\n\
        Travel Date: %u,\n\
        Number of Travellers : %u\n\
        Seats selected:%u\n}",
           customer.receipt_id, customer.name, customer.govt_id, customer.travel_date, customer.num_traveler, customer.seats);

    sprintf(customer_receipt, "{\n\tReceipt Number : %d,\n\
           Customer name: %u,\n\
           Government ID: %u,\n\
           Travel Date: %u,\n\
           Number of Travellers : %u\n\
           Seats selected: %u\n}",
            customer.receipt_id, customer.name, customer.govt_id, customer.travel_date, customer.num_traveler, customer.seats);
    sprintf(customer_receipt, "Here is your receipt. Your receipt info is %d", customer.receipt_id);

    send(client_socket, customer_receipt, sizeof(customer_receipt), 0);
}
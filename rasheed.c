#include "header.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void printTrain(int day);

void reserveSeats(struct Customer *customer, int client_socket)
{
    struct Customer a;
    a = *customer;

    // gives lock to writer
    sem_wait(wrt);

    // ==========================
    // BEGINNING CRITICAL SECTION
    // ==========================


    if (!(a.receipt_id >= 2000 && a.receipt_id < 3000))
    {
        a.receipt_id = receipt_num;
        receipt_num++;
    }

    int x = a.receipt_id;

    char str[20];
    sprintf(str, "%d", x);

    char filename[15];
    strcat(str, "_r.txt");
    // printf("%s\n", str);
    strcpy(filename, str);
    // printf("%s\n", filename);

    FILE *fp2 = fopen(filename, "w");

    //print the receipt information in the file

    fprintf(fp2, "%s\n", a.name);
    fprintf(fp2, "%d\n", a.govt_id);
    fprintf(fp2, "%d\n", a.travel_date);

    fprintf(fp2, "%d\n", a.num_traveler);
    for (int i = 0; i < NUM_SEATS; i++)
    {
        fprintf(fp2, "%d", a.seats[i]);
    }
    fprintf(fp2, "\n");



    FILE *fp1;

    char Train[32];
    char temp[10];

    sprintf(temp, "%d", a.travel_date);

    strcpy(Train, "train_day");
    strcat(Train, temp);
    strcat(Train, ".txt");

    fp1 = fopen(Train, "r");

    char seats_now[31];
    fscanf("%s", seats_now);

    fclose(fp1);

    fp1 = fopen(Train, "w");
    for(int i=0; i<30; i++)
    {
        if( a.seats[i] ) seats_now[i] = '1';
    }

    fprintf(fp1, "%s", seats_now);

    fclose(fp1);
    fclose(fp2);

    sem_post(wrt);
}

void inquiry(int ticket) // still working
{
    char filename[32];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(filename, temp);
    strcat(filename, "_r.txt");

    if (fopen(filename, "r"))
    {
        printf("Ticket number %d has been found.\n", ticket);

        FILE *fp1;
        fp1 = fopen(filename, "r");

        char temp[50];
        int temp2, temp3, temp4;
        char temp5[35];
        fscanf(fp1, "%[^\n]%d%d%d%s", temp, &temp2, &temp3, &temp4, temp5);

        printf("Name: %s\n", temp);
        printf("Date of Birth: %d\n", temp2);
        printf("Govt. ID: %d\n", temp3);
        printf("Number of seats: %d\n", temp4);

        for (int i = 0; i < 30; i++)
        {
            if (temp5[i] == '1')
                printf("%d ", i + 1);
        }
        printf("\n");

        fclose(fp1);
    }
    else
    {
        printf("Ticket not found.\n");
    }
}


void modify(int ticket, int client_socket)
{
    // int ticket = a.receipt_id;
    char filename[32];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(filename, temp);
    strcat(filename, "_r.txt");

    printf("%s\n", filename);

    if (fopen(filename, "r"))
    {
        char modification_message[512];

        sprintf(modification_message, "Found ticket [%d] in our database.\nModifying ticket. Please enter the information below.\n", ticket);
        send(client_socket, modification_message, sizeof(modification_message), 0);

        struct Customer modified_cust;
        struct Customer *modified_cust_ptr = &modified_cust;

        // receives modified customer struct from the client
        recv(client_socket, modified_cust_ptr, sizeof(struct Customer), 0);

        ticket = ticket + 1000;
        modified_cust.receipt_id = ticket;

        printf("NUMBER: %d\n", modified_cust_ptr->receipt_id);

        reserveSeats(modified_cust_ptr, client_socket);

        remove(filename);
    }
    else
    {
        printf("Ticket not found.\n");
    }
}

void cancellation(int *ticket_ptr, int client_socket)
{
    int ticket = *ticket_ptr;
    char filename[11];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(filename, temp);
    strcat(filename, "_r.txt");

    printf("%s\n", filename);

    if (fopen(filename, "r"))
    {
        char confirmation_msg[1024];
        sprintf(confirmation_msg, "Ticket [%d] was found.\nAre you sure you want to cancel the reservation (Y or N)?\n", ticket);

        // sends confirmation message to the client
        send(client_socket, confirmation_msg, sizeof(confirmation_msg), 0);

        // receives cancellation confirmation answer from client
        char answer[2];
        recv(client_socket, answer, sizeof(answer), 0);

        if ((strcmp(answer, "Y") == 0) || (strcmp(answer, "y") == 0))
        {
            printf("Reservation for ticket %d is cancelled.\n", ticket);
            remove(filename);
        }
    }
    else
    {
        printf("The ticket doesn't exist.\n");
    }
}

struct Customer reserveInformationFromUser()
{
    struct Customer a;

    // printf("Please enter your credentials as prompted.\n\n");
    printf("Name: ");
    char Name[50];
    scanf(" %s", Name);
    strcpy(a.name , Name);
    printf("Date of Birth(YYYYMMDD): ");
    scanf("%d", &a.dob);
    printf("Gender (M or F): ");
    scanf(" %c", &a.gender);
    printf("Government ID: ");
    scanf("%d", &a.govt_id);
    printf("Available dates of travel: 1 or 2.\nSelect One: ");
    scanf("%d", &a.travel_date);
    printf("Number of Travelers: ");
    scanf("%d", &a.num_traveler);

    // automated for testing
    // strcpy(a.name, "Parker");
    // a.dob = 19980418;
    // a.gender = 'M';
    // a.govt_id = 56441;
    // a.receipt_id = 45259;
    // a.travel_date = 20210419;
    // a.num_traveler = 1;

    // Sets all the values of the seats[] to be 0. This fixes a bug where unexpected values were present in the array.
    for (int i = 0; i < NUM_SEATS; i++)
    {
        a.seats[i] = 0;
    }

    // a.seats[4] = 1;

    printTrain(a.travel_date);

    // printf("Enter your desired seats to reserve:\n");

    // sets the desired customer's seats' indices to be 1
    for (int i = 0; i < a.num_traveler; i++)
    {
        printf("Choose seat for ticket %d/%d: ", i + 1, a.num_traveler);
        int temp;
        scanf("%d", &temp);
        a.seats[temp - 1] = 1;
    }
    printf("\n");

    return a;
}


struct Customer printReceipt(struct Customer a, int choice)
{
    printf("\n\n_____________________________________\n");
    printf("Your Hogwards express ticket is ready\n");
    printf("_____________________________________\n");

    if (choice == 1)
        receipt_num++;
    if (choice < 4)
    {
        // previously no values have been assigned
        a.receipt_id = choice * 1000 + receipt_num; //1000 for reservation, 2000 for modification, 3000 for cancelation
    }

    printf("Your receipt number (store for future use): %d\n", a.receipt_id);
    printf("==============================================\n");
    printf("Customer Name: %s\n", a.name);
    printf("Customer ID: %d\n", a.govt_id);
    printf("Date of Travel (YYYYMMDD): %d\n", a.travel_date);

    printf("Seats Booked: %d\n", a.num_traveler);
    for (int i = 1; i <= 30; i++)
    {
        if (a.seats[i])
            printf("%d ", i);
    }
    printf("\n");
    //printf("Total number of seats = %d\n", cnt);

    printf("Have a great travel to Hogwarts. Dumbeldore awaits\n");
    printf("__________________________________________________\n\n");

    sleep(3);
    return a;
}


void printTrain(int day)
{
    char Train[32];
    char temp[10];

    sprintf(temp, "%d", day);

    strcpy(Train, "train_day");
    strcat(Train, temp);
    strcat(Train, ".txt");

    printf("%s\n", Train);

    FILE *fp1;
    fp1 = fopen(Train, "r");

    printf("Your desired train to Hogwarts seats' are shown below:\n");
    for (int i = 1; i < 31; i++)
    {
        printf("%5d", i);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("\n");
    char train_seats[32];
    fscanf(fp1, "%[^\n]", train_seats);

    printf("Available seats at the moment: \n");
    for (int i = 0; i < 30; i++)
    {
        if (train_seats[i] == '0')
            printf("%3d", i + 1);
    }
    printf("\n");

    fclose(fp1);
}

void createTrainFiles()
{
    FILE *f, *f2;
    f = fopen("train_day1.txt", "w");
    f2 = fopen("train_day2.txt", "w");

    char t[30];
    for (int i = 0; i < 30; i++)
    {
        t[i] = '0';
    }

    fprintf(f, "%s", t);
    fprintf(f2, "%s", t);

    fclose(f);
    fclose(f2);
}
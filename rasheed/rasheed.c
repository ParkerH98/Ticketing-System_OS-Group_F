#include "../header.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int receipt_num = 1; //please call this as global variable

struct Customer
{
    int id;           // receipt id
    char name[50];    // name of the customer
    int dob;          // date of birth
    char gender;      // gender of the customer
    int govt_id;      //government id
    int travel_date;  //date they will travel. Format YYYYMMDD
    int num_traveler; // number of traveler
};

struct Customer initializeCust(struct Customer a)
{
    a.id = 100;
    a.dob = 20000101;
    strcpy(a.name, "void");
    a.gender = 'e';
    a.govt_id = 1234;
    a.travel_date = 20210410;
    a.num_traveler = 1;

    return a;
}

void PrintTrain(int available[]) //pass an available array to print the train and the availability of the train
{
    // First element of the array is the number of seats available
    // Print the train seats first and then the available seat numbers

    printf("Your desired train to Hogwarts seats' are shown below:\n");
    for (int i = 1; i <= 10; i++)
    {
        printf("%5d", i);
    }
    printf("\n");
    for (int i = 11; i <= 20; i++)
    {
        printf("%5d", i);
    }
    printf("\n");
    for (int i = 21; i <= 30; i++)
    {
        printf("%5d", i);
    }
    printf("\n");

    printf("%d available seats at the moment: ", available[0]);
    for (int i = 1; i <= available[0]; i++)
    {
        printf("%3d", available[i]);
    }
    printf("\n");
}

struct Customer printReceipt(int seatchoice[], struct Customer a)
{
    printf("\n\n_____________________________________\n");
    printf("Your Hogwards express ticket is ready\n");
    printf("_____________________________________\n");

    a.id = 1000 + receipt_num; //1000 for reservation, 2000 for modification, 3000 for cancelation.
    receipt_num++;

    printf("Your receipt number (store for future use): %d\n", a.id);
    printf("==============================================\n");
    printf("Customer Name: %s\n", a.name);
    printf("Customer ID: %d\n", a.govt_id);
    printf("Date of Travel (YYYYMMDD): %d\n", a.travel_date);
    printf("Seats Booked: %d\n", a.num_traveler);
    for (int i = 0; i < a.num_traveler; i++)
        printf("%d ", seatchoice[i]);
    printf("\n");

    printf("Have a great travel to Hogwarts. Dumbeldore awaits\n");
    printf("__________________________________________________\n\n");

    sleep(3);
    return a;
}

void reserveSeats(int seats[]) // files demo
{
    printf("\nThe following seat numbers have been reserved:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", seats[i]);
    }
}

int availableFunction(struct Customer a) //files demo
{
    return 10;
}

int *availableFunction2(struct Customer a) //files demo
{
    static int r[] = {10, 3, 6, 8, 9, 10, 16, 17, 18, 22, 23};
    int i;

    return r;
}

int main()
{
    // Connection from the manager

    while (1)
    {
        //Greet the customer until he chooses 5
        printf("\n\nWelcome to the Platform 9 3/4.\n______________________________\n\n");
        printf("To check the availability of the Hogwarts Express, please follow the menu and choose your options.\n");

        printf("1. Make a reservation\n");
        printf("2. Inquire about the ticket\n");
        printf("3. Modify the reservation\n");
        printf("4. Cancel the reservation\n");
        printf("5. Exit the platform\n");

        printf("What is your magic number?: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 5) //exit the program
        {
            printf("Missing all the fun with Hogwarts!! Goodbye\n");
            return 0; //return back to the manager
        }

        if (choice == 1)
        {
            printf("Nice choice. We only have Hogwarts express for 2021-04-11 and 2021-04-12 (YYYY-MM-DD) and 30 seats per train.\nPlease provide us with the following information.\n");

            struct Customer a;
            a = initializeCust(a);
            printf("Please provide name: ");
            char Name[50];
            strcpy(Name, "Harry Potter");
            //fgets(Name, 50, stdin);
            strcpy(a.name, Name);
            printf("Date of Birth(YYYYMMDD): ");
            scanf("%d", &a.dob);
            printf("Your gender: ");
            scanf("%c", &a.gender);
            printf("Government ID: ");
            scanf("%d", &a.govt_id);
            printf("Available date of travel: 20210411 or 20210412.\n Select one: ");
            scanf("%d", &a.travel_date);
            int reminder = availableFunction(a); //connect with files
            while (1)
            {
                printf("Number of travelers: ");
                scanf("%d", &a.num_traveler);
                if (a.num_traveler > reminder)
                {
                    printf("We don't have that many seats left. Try again.\n");
                    sleep(1);
                    continue;
                }
                else
                    break;
            }

            //Confirmation
            printf("Do you want to make the reservation for Hogwarts? (y/n) ");
            char ans;
            //scanf("%c", &ans);
            ans = 'y';
            if (ans == 'n')
            {
                sleep(2);
                continue;
            }

            int *avail;
            avail = availableFunction2(a); //connect to files
            int available[35];
            for (int i = 0; i < 11; i++)
            {
                available[i] = *(avail + i);
            }

            PrintTrain(available);
            printf("Select seat numbers for Hogwarts Express: ");
            int seatchoice[a.num_traveler];
            for (int i = 0; i < a.num_traveler; i++)
            {
                scanf("%d", &seatchoice[i]);
            }

            reserveSeats(seatchoice); //connect to files

            a = printReceipt(seatchoice, a);
        }
        if (choice == 2)
        {
        }
        if (choice == 3)
        {
        }
    }
    return 0;
}
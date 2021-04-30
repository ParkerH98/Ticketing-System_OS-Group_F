#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

void searchticket( int ticket ) // still working
{
    char filename[32];
    char temp[10];
    
    sprintf(temp, "%d", ticket);
    strcpy(filename, temp);
    strcat(filename, "_r.txt");


    if( fopen(filename, "r") )
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
        
        for(int i = 0; i<31; i++)
        {
            if( temp5[i] == '1') printf("%d ", i); 
        }

        fclose(fp1);

    }
    else
    {
        printf("Ticket not found.\n");
    }
}


void PrintTrain( int day ) 
{
    char Train[32];
    char temp[4];

    sprintf(temp, "%d", day);

    strcpy(Train, "train_day");
    strcat(Train, temp);
    strcat(Train, ".txt");


    printf("%s\n", Train);


    FILE *fp1; 
    fp1 = fopen(Train, "r");


    printf("Your desired train to Hogwarts seats' are shown below:\n");
    for(int i = 1; i<31; i++)
    {
        printf("%5d", i);
        if(i%10 == 0) printf("\n");
    }
    char train_seats[32];
    fscanf(fp1, "%[^\n]", train_seats);

    printf("Available seats at the moment: ");
    for(int i = 0; i < 30; i++)
    {
        if( train_seats[i] == '0' ) printf("%3d", i+1);
    }
    printf("\n");

    fclose(fp1);
} 



int main()
{
    FILE *f, *f2;
    f = fopen("train_day1.txt", "w");
    f2 = fopen("train_day2.txt", "w");

    char t[30]; 
    for(int i=0; i<30;i++)
    {
        t[i] = '0';
    }

    fprintf(f, "%s", t); 
    fprintf(f2, "%s", t);

    fclose(f);
    fclose(f2);

}

struct Customer initializeCust()
{
    struct Customer a;
    a.receipt_id = 100;
    a.dob = 20000101;
    strcpy(a.name, "void");
    a.gender = 'e';
    a.govt_id = 1234;
    a.travel_date = 20210413;
    a.num_traveler = 1;
    for (int i = 0; i < 31; i++)
        a.seats[i] = 0;
    return a;
}

// struct Customer initializeCust(struct Customer a)
// {
//     a.receipt_id = 100;
//     a.dob = 20000101;
//     strcpy(a.name, "void");
//     a.gender = 'e';
//     a.govt_id = 1234;
//     a.travel_date = 20210413;
//     a.num_traveler = 1;
//     for (int i = 0; i < 31; i++)
//         a.seats[i] = 0;
//     return a;
// }

// int main()
// {
//     // Connection from the manager

//     // create summary file
//     FILE *fp;
//     fp = fopen("summary.txt", "w");
//     fclose(fp);
//     // close the summary file pointer, to avoid future problems

//     while (1)
//     {
//         //Greet the customer until he chooses 5
//         printf("\n\nWelcome to the Platform 9 3/4.\n______________________________\n\n");
//         printf("To check the availability of the Hogwarts Express, please follow the menu and choose your options.\n");

//         printf("1. Make a reservation\n");
//         printf("2. Inquire about the ticket\n");
//         printf("3. Modify the reservation\n");
//         printf("4. Cancel the reservation\n");
//         printf("5. Exit the platform\n");

//         printf("What is your magic number?: ");
//         int choice;
//         scanf("%d", &choice);

//         if (choice == 5) //exit the program
//         {
//             printf("Missing all the fun with Hogwarts!! Goodbye\n");
//             printf("Exiting...\n");
//             sleep(1);
//             return 0; //return back to the manager
//         }

//         if (choice == 1)
//         {
//             printf("Nice choice. We only have Hogwarts express for 2021-04-14 and 2021-04-15 (YYYY-MM-DD) and 30 seats per train.\nPlease provide us with the following information.\n");

//             struct Customer a;
//             a = initializeCust(a);
//             printf("Please provide name: ");
//             char Name[50];
//             strcpy(Name, "Harry Potter");
//             //fgets(Name, 50, stdin);
//             strcpy(a.name, Name);
//             printf("Date of Birth(YYYYMMDD): ");
//             scanf("%d", &a.dob);
//             printf("Your gender: ");
//             scanf("%c", &a.gender);
//             printf("Government ID: ");
//             scanf("%d", &a.govt_id);
//             printf("Available date of travel: 20210411 or 20210412.\n Select one: ");
//             scanf("%d", &a.travel_date);
//             int reminder = availableFunction(a); //connect with files
//             while (1)
//             {
//                 printf("Number of travelers: ");
//                 scanf("%d", &a.num_traveler);
//                 if (a.num_traveler > reminder)
//                 {
//                     printf("We don't have that many seats left. Try again.\n");
//                     sleep(1);
//                     continue;
//                 }
//                 else
//                     break;
//             }

//             //Confirmation
//             printf("Do you want to make the reservation for Hogwarts? (y/n) ");
//             char ans;
//             //scanf("%c", &ans);
//             ans = 'y';
//             if (ans == 'n')
//             {
//                 sleep(2);
//                 continue;
//             }

//             int *avail;
//             avail = availableFunction2(a); //connect to files
//             int available[35];
//             for (int i = 0; i < 11; i++)
//             {
//                 available[i] = *(avail + i);
//             }

//             PrintTrain(available);
//             printf("Select seat numbers for Hogwarts Express: ");
//             int seatchoice[a.num_traveler];
//             for (int i = 0; i < a.num_traveler; i++)
//             {
//                 scanf("%d", &seatchoice[i]);
//                 a.seats[seatchoice[i]] = 1;
//             }

//             a = printReceipt(a, 1);
//             reserveSeats(a); //connect to files
//         }

//         if (choice == 2) // inquire about the tickets
//         {
//             struct Customer a;
//             printf("Please enter the ticket number: ");
//             int ticket;
//             scanf("%d", &ticket);
//             a = inquireTicket(ticket);
//             a = printReceipt(a, 4);

//             sleep(3);
//             printf("\nReturning back to menu.\n");
//             sleep(1);
//             printf("...\n");
//             sleep(1);
//             printf("...\n");
//             sleep(1);
//             printf("...\n");
//             continue;
//         }
//         if (choice == 3) // modify the ticket
//         {
//             struct Customer a;
//             int ticket;
//             printf("Please provide the ticket number you want to modify: ");
//             scanf("%d", &ticket);
//             a = inquireTicket(ticket);
//             printf("\n\nCurrently the following seats are available:\n");

//             int *avail;
//             avail = availableFunction2(a); //connect to files
//             int available[35];
//             for (int i = 0; i < 11; i++)
//             {
//                 available[i] = *(avail + i);
//             }
//             PrintTrain(available);

//             a.receipt_id = ticket;
//             a = modifyTicket(a);
//             printReceipt(a, 2);
//         }

//         if (choice == 4) // cancel the ticket
//         {
//             struct Customer a;
//             printf("Please enter the ticket number that you want to cancel: ");
//             int ticket;
//             scanf("%d", &ticket);
//             a = cancelTicket(ticket); // connect to files
//             a = printReceipt(a, 3);

//             printf("We are really so to see you go. :(\n");
//             printf("Hogwarts will miss you!!!");

//             sleep(3);
//             printf("\nReturning back to menu.\n");
//             sleep(1);
//             printf("...\n");
//             sleep(1);
//             printf("...\n");
//             sleep(1);
//             printf("...\n");
//             continue;
//         }
//     }
//     return 0;
// }
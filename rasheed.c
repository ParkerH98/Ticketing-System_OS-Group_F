#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

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
    int seats[31];    //selected seats in the train
};

struct Customer initializeCust(struct Customer a)
{
    a.id = 100;
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
        a.id = choice * 1000 + receipt_num; //1000 for reservation, 2000 for modification, 3000 for cancelation
    }

    printf("Your receipt number (store for future use): %d\n", a.id);
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

void reserveSeats(struct Customer a) // files demo
{

    FILE *fp1;
    fp1 = fopen("summary.txt", "w");

    int x = a.id;
    fprintf(fp1, "%d, e\n", x);

    char str[20];
    sprintf(str, "%d", x);

    char filename[15];
    strcat(str, "_r.txt");
    printf("%s\n", str);
    strcpy(filename, str);
    printf("%s\n", filename);

    FILE *fp2 = fopen(filename, "w");

    //print the receipt information in the file
    fprintf(fp2, "%s\n", a.name);
    fprintf(fp2, "%d\n", a.govt_id);
    fprintf(fp2, "%d\n", a.travel_date);

    fprintf(fp2, "%d\n", a.num_traveler);
    for (int i = 1; i <= 30; i++)
    {
        fprintf(fp2, "%d", a.seats[i]);
    }
    fprintf(fp2, "\n");

    fclose(fp2);
    fclose(fp1);
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

struct Customer inquireTicket(int ticket) //file demo
{
    struct Customer a;
    a = initializeCust(a);
    a.id = ticket;
    strcpy(a.name, "Harry Potter");
    // a.name = "Harry Potter";
    a.dob = 19940920;
    a.gender = 'm';
    a.govt_id = 405762;
    a.travel_date = 20210414;
    a.num_traveler = 5;

    a.seats[3] = 1;
    a.seats[8] = 1;
    a.seats[10] = 1;
    a.seats[18] = 1;
    a.seats[23] = 1;

    return a;
}

struct Customer modifyTicket(struct Customer a) // file demo
{
    return a;
};

struct Customer cancelTicket(ticket) //file demo
{
    struct Customer a;
    return a;
};

void cancellation(int ticket)
{
    if(ticket < 2000)
    {
        char filename[11];
        char temp[4];
        
        sprintf(temp, "%d", ticket);
        strcpy(filename, temp);
        strcat(filename, "_r.txt");

        //printf("%s\n", filename);

        if( fopen(filename, "r") )
        {
            printf("Ticket FOUND %d\n", ticket);
            printf("Are you sure you want to cancel the reservation? Y/N\n");
            char ans;
            scanf(" %c", &ans);
            printf("Reservation for ticket %d is cancelled.\n", ticket);
            remove(filename);
        }
        else
        {
            printf("The ticket doesn't exist.\n");
        }
    }
}

int main()
{
    // Connection from the manager

    // create summary file
    FILE *fp;
    fp = fopen("summary.txt", "w");
    fclose(fp);
    // close the summary file pointer, to avoid future problems

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
            printf("Exiting...\n");
            sleep(1);
            return 0; //return back to the manager
        }

        if (choice == 1)
        {
            printf("Nice choice. We only have Hogwarts express for 2021-04-14 and 2021-04-15 (YYYY-MM-DD) and 30 seats per train.\nPlease provide us with the following information.\n");

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
                a.seats[seatchoice[i]] = 1;
            }

            a = printReceipt(a, 1);
            reserveSeats(a); //connect to files
        }

        if (choice == 2) // inquire about the tickets
        {
            struct Customer a;
            printf("Please enter the ticket number: ");
            int ticket;
            scanf("%d", &ticket);
            a = inquireTicket(ticket);
            a = printReceipt(a, 4);

            sleep(3);
            printf("\nReturning back to menu.\n");
            sleep(1);
            printf("...\n");
            sleep(1);
            printf("...\n");
            sleep(1);
            printf("...\n");
            continue;
        }
        if (choice == 3) // modify the ticket
        {
            struct Customer a;
            int ticket;
            printf("Please provide the ticket number you want to modify: ");
            scanf("%d", &ticket);
            a = inquireTicket(ticket);
            printf("\n\nCurrently the following seats are available:\n");

            int *avail;
            avail = availableFunction2(a); //connect to files
            int available[35];
            for (int i = 0; i < 11; i++)
            {
                available[i] = *(avail + i);
            }
            PrintTrain(available);

            a.id = ticket;
            a = modifyTicket(a);
            printReceipt(a, 2);
        }

        if (choice == 4) // cancel the ticket
        {
            struct Customer a;
            printf("Please enter the ticket number that you want to cancel: ");
            int ticket;
            scanf("%d", &ticket);
            a = cancelTicket(ticket); // connect to files
            a = printReceipt(a, 3);

            printf("We are really so to see you go. :(\n");
            printf("Hogwarts will miss you!!!");

            sleep(3);
            printf("\nReturning back to menu.\n");
            sleep(1);
            printf("...\n");
            sleep(1);
            printf("...\n");
            sleep(1);
            printf("...\n");
            continue;
        }
    }
    return 0;
}
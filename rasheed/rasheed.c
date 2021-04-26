#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


struct Customer
{
    int id;         // receipt id
    char name[50];  // name of the customer
    int dob;        // date of birth
    char gender;    // gender of the customer
    int govt_id;    //government id
    int travel_date; //date they will travel. Format YYYYMMDD
    int num_traveler; // number of traveler
    int seats[31]; //selected seats in the train
};

struct Customer initializeCust(struct Customer a)
{

    a.dob = 19940920;
    strcpy(a.name, "Harry");
    a.gender = 'm';
    a.govt_id = 74075;
    a.travel_date = 20210413;
    a.num_traveler = 5;
    for(int i=0; i<=31; i++)
        a.seats[i] = 0;
    
    return a;
}

void reserveSeats( struct Customer a ) // files demo
{
    FILE *fp1; 
    fp1 = fopen("summary.txt", "a");

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
    for(int i=0; i < 30; i++)
    {
        fprintf(fp2, "%d", a.seats[i]);
    }
    fprintf(fp2, "\n");


    fclose(fp2);
    fclose(fp1);
}

struct Customer reserveInformationFromUser( struct Customer a)
{
    printf("Please provide name: ");
    char Name[50];
    //strcpy(Name, "Harry Potter");
    scanf(" %s", Name);
    strcpy(a.name, Name);
    printf("Date of Birth(YYYYMMDD): ");
    scanf("%d", &a.dob);
    printf("Your gender: ");
    scanf(" %c", &a.gender);
    printf("Government ID: ");
    scanf("%d", &a.govt_id);
    printf("Available date of travel: 20210411 or 20210412.\n Select one: ");
    scanf("%d", &a.travel_date);
    printf("Number of travelers: ");
    scanf("%d", &a.num_traveler);

    for(int i = 0; i<a.num_traveler; i++)
    {
        int temp;
        scanf("%d", &temp);
        a.seats[temp-1] = 1;
    }


    return a;
}

int searchticket( int a )
{
    FILE *f;
    f = fopen("summary.txt", "r");
    rewind(f);

    int stat = 0; // 0 means didn't find // 1 means found and existing // 2 means modified
    int num;
    char x;
    while(!EOF)  
    { 
        fscanf(f, "%d, %c", &num, &x);
        printf("%d %c\n",num, x);
        if(num == a && x == 'e')
            return stat = 1;
        
        if(num == a && x == 'm')
            return stat = 2;
    }

    fclose(f);
    return stat = 0;
}

int main()
{

    FILE *fpnew; 
    fpnew = fopen("summary.txt", "w");
    fclose(fpnew);

    struct Customer a;
    a = initializeCust(a);
    
    /*
    a = reserveInformationFromUser( a );
    a.id = 1004;
    reserveSeats( a ); //first reservation


    a = initializeCust( a );
    a = reserveInformationFromUser( a );
    a.id = 1005;
    reserveSeats( a ); //second reservation
    */

    // read the reservation 
    int cnt = 5;
    while(cnt--)
    {
        int ticket_num;
        scanf("%d", &ticket_num);
        int status = searchticket( ticket_num );
        
        if(status == 1) // found the original ticket
        {
            printf("Found the original ticket\n");
        }
        else if(status == 2) // ticket was modified
        {
            printf("Found the modified version of the ticket\n");
        }
        else // ticket was not found
        {
            printf("ticket was not found\n");

        }
    }
    

    return 0;
}
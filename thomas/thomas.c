#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
    a.id = 100;
    a.dob = 20000101;
    strcpy(a.name, "void");
    a.gender = 'e';
    a.govt_id = 1234;
    a.travel_date = 20210413;
    a.num_traveler = 1;
    for(int i=0; i<31; i++)
        a.seats[i] = 0;
    return a;
}

void reserveSeats( struct Customer a ) // files demo
{
    printf("\nThe following seat numbers have been reserved:\n");
    for(int i = 1; i <= 30; i++)
    {
        if(a.seats[i]) printf("%d ", i);
    }
}

int availableFunction(struct Customer a) //files demo
{
    return 10;
}

int * availableFunction2(struct Customer a) //files demo
{
    static int  r[] = {10, 3, 6, 8, 9, 10, 16, 17, 18, 22, 23} ;
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
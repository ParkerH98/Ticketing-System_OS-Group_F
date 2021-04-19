#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct Customer
{
    int id;           // receipt id
    char name[50];    // name of the customer
    int dob;          // date of birth
    char gender;      // gender of the customer
    int govt_id;      //government id
    int travel_date;  //date they will travel. Format YYYYMMDD
    int num_traveler; // number of traveller
   // bool seats[7];   //how many seat the customer wants to reserve
};

struct returnCustomer {
    int receipt;
    char *output;
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
//    a.seats[7]= {0,0,1,0,0,1,1};
   // strcpy (a.seats,{0,0,1,0,0,1,1});

    return a;
}

//function for reserving seats
void reserveSeat(struct Customer cust){
    FILE *fpt;
    char buffer[1024];
    fpt = fopen("ReserveSeats.csv","a+");

    //creates an excel sheet for reserving seats
    if(fpt==NULL){
        printf("I have another guy\n");
        fpt = fopen("ReserveSeats.csv","w+");
        //for some reason, this is not writing to the excel sheet. i don't know why
        printf(fpt,"id, name, dob, gender, gov_id, travel_date, num_traveler, seats\n");
        exit(EXIT_FAILURE);
    }
    printf("Customer's id is %d \n", cust.id);

    //added the information from customer to be stored in the file
    while (fgets(buffer, 1024, fpt)){
        //this is also not writing to the sheet
        printf(fpt,"%d, %[^,], %d, %s, %d, %d, %d, %d\n",cust.id,cust.name,cust.dob,cust.gender,cust.govt_id,cust.travel_date,cust.num_traveler);
        printf("seats reserved successfully!");
    }
    fclose(fpt);
}

char *inquirySeat(int receipt_no){
    struct returnCustomer rt;

}

int main()
{
    struct Customer cust;
    int seats_taken;
    cust = initializeCust(cust);

    reserveSeat(cust);

    //bool arr[7] = a.seats;
    for(int i=0; i<7; i++){
    //    printf("%u\n",arr[i]);
    }

    return 0;
}


/*
//this was the first one that i did, that i ran into an issue with the seat reservation.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int vacant[7];
bool available_seats[7];
int num_seats = 7;

int getNumberOfSeats(){
    int count = 0;
    for(int i=0; i< num_seats; i++){
        if(available_seats[i]==0){
            count++;
        }
    }
    return count;
}

int *getAvailableSeats(){
    for(int i=0; i<num_seats; i++){
        if(available_seats[i]==0){
            vacant[i]= i+1;
        }
    }
    for(int i=0; i<7;i++){
        printf("%u\n",vacant[i]);
    }
    return vacant;
}

void reserveSeat(bool seats[],int seat_size){
    for(int i=0; i<seat_size; i++){
        if(available_seats[i]==0 && seats[i]==1){
            available_seats[i] =1;
        }
    }
    getAvailableSeats();
    for(int i=0; i<7; i++){
        printf("\n%u\n",availa)
    }
}

int *vailableSeats(bool seats[],int seat_size){
    for(int i=0; i< seat_size;i++){
        if(seats[i]==0){
            vacant[i] = i+1;
        }
        else {
            printf("Sorry seat %d is taken\n", i);
        }
    }
    int length= sizeof(vacant) / sizeof *vacant;
    for(int i=0; i<length; i++){
        printf("%u\n",vacant[i]);
    }
    return vacant;
}

int main()
{
    struct Customer cust;
    cust = initializeCust(cust);

    reserveSeat(cust);

    //bool arr[7] = a.seats;
    for(int i=0; i<7; i++){
    //    printf("%u\n",arr[i]);
    }


  //  bool seats[] = {0,1,1,0,1};
    //int seat_size = sizeof(seats) / sizeof(seats[0]);
   // printf("The number of available seats are %d\n\n",getNumberOfSeats());
   // getAvailableSeats();
   // reserveSeat(seats,seat_size);
  //  int *val =getAvailableSeats();
    //printf("\n%u\n",val);
   // bool seats2[] = {1,1,1,0,0};
    return 0;
}

*/
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

//function for returning seat
void reserveSeat(struct Customer cust){
    FILE *fpt;
    char buffer[1024];
    fpt = fopen("ReserveSeats.csv","a+");

    if(fpt==NULL){
        printf("I have another guy\n");
        fpt = fopen("ReserveSeats.csv","w+");
        printf(fpt,"id, name, dob, gender, gov_id, travel_date, num_traveler, seats\n");
        exit(EXIT_FAILURE);
    }
    printf("Customer's id is %d \n", cust.id);
    while (fgets(buffer, 1024, fpt)){
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

struct DataItem {
   bool selected_seats[5];   
   int custId;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;
bool available_seats[7] ={0,0,0,0,0,0,0};
int vacant[7];

int hashCode(int custId) {
   return custId % SIZE;
}

int getNumberOfSeats(){
    int count = 0;
    for(int i=0; i< SIZE; i++){
        if(available_seats[i]==0){
            count++;
        }
    }
    return count;
}

struct DataItem *inquireTicket(int custId) {
   //get the hash 
   int hashIndex = hashCode(custId);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->custId == custId){
         printf("Customer reserved seat: %u\n",hashArray[hashIndex]);
         return hashArray[hashIndex]; 
      }
      else{
          printf("Customer %d have not reserve any seat\n",custId);
          return NULL;
      }
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	//returns the index customer and it's array
   return hashArray[hashIndex]->selected_seats;        
}

void reserveSeat(int custId,bool selected_seats[]) {
    int seat_size = 5;
    for(int i=0; i< seat_size;i++){
        if(selected_seats[i]==0){
            vacant[i] = i+1;
        }
    }


   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->selected_seats[SIZE] = selected_seats[SIZE];  
   item->custId = custId;

   //get the hash 
   int hashIndex = hashCode(custId);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->custId != -1) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

//This is optional.. we don't need it for our main code
void display() {
   int i = 0;
   int count =0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" customer %d got seat %u\n",hashArray[i]->custId,hashArray[i]->selected_seats);
      else
         printf(" ~~ \n");
   }
	
   printf("====================================================\n");
}

int main() {
   //dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   //dummyItem->selected_seats[SIZE] = -1;  
   //dummyItem->custId = -1; 

    bool  seats[5]= {1,0,0,1,1};
    bool  seats2[5]= {0,1,0,0,0};
    bool seat3[5] = {0,0,1,0,0};

   reserveSeat(1, seats);
   reserveSeat(2, seats2);
   printf("The number of available seats is %d\n\n",getNumberOfSeats());
   reserveSeat(3, seat3);
   printf("The number of available seats is %d\n\n",getNumberOfSeats());
   display();

   inquireTicket(37);
   item = inquireTicket(1);
   bool *array = item->selected_seats;

    int len = sizeof(array) / sizeof(*array);
    printf("length of the seats is %d\n ",len);
    for (int i=0; i< len; i++){
        if (array[i]==1)
        {
            printf("The reserved seats are %u\n",array[i]);
        }
        
        
    }
}
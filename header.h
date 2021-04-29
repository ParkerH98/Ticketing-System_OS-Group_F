#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h> // needed for file operations
#include <stdio.h> // Baisc standard I/O like printf
#include <string.h> // required for strlen
#include <unistd.h> // defines standard symbolic constants and types
#include <sys/types.h> // basic derived types like pid_t
#include <sys/stat.h> //required for mkfifo (i.e. defines data returned by the stat() function: get file status)
#include <fcntl.h> //required for open (i.e. file control options)
#include <sys/wait.h> // used for wait function 
#include <netinet/in.h> // needed for socket connections
#include <sys/socket.h> // needed for socket connections
#include <arpa/inet.h> // needed for socket connections
#include <pthread.h> // threads
#include <time.h> // time for random seed
#include <semaphore.h> // semaphores

// SERVER CONSTANTS
#define PORT 9087
#define NUM_SERVERS 2
#define BACKLOG 50
#define THREAD_NUMBER 2

#define QUEUE_SIZE 6


// STRUCT CONSTANTS
#define CUST_NAME_LEN 50
#define NUM_SEATS 31 // +1 of desired seats because index 0 is unused

struct Customer
{
    int id;         // receipt id
    char name[CUST_NAME_LEN];  // name of the customer
    int dob;        // date of birth
    char gender;    // gender of the customer
    int govt_id;    //government id
    int travel_date; //date they will travel. Format YYYYMMDD
    int num_traveler; // number of traveler
    int seats[NUM_SEATS]; //selected seats in the train
};

sem_t *wrt;
pthread_mutex_t mutex;
static int read_count = 0;

#endif


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

#define PORT 9008

#define CUSTNAME_LEN 64
#define DOB_LEN 16
#define GENDER_LEN 2
#define TRAVELDATE_LEN 16

struct Reservation{
    char customerName[CUSTNAME_LEN];
    char dateOfBirth[DOB_LEN];
    char gender[GENDER_LEN];
    int govIDNumber;
    char travelDate[TRAVELDATE_LEN];
    int numberTravelers;
};

#endif
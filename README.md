
 # OS-Group_F Train Ticketing System

Operating Systems Spring 2021 Group F Repository for Assignment03

## Table of Contents
- [OS-Group\_F Train Ticketing System](#os-group_f-train-ticketing-system)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Installation](#installation)
  - [Usage](#usage)
    - [Server](#server)
    - [Client](#client)
  - [Important Notes](#important-notes)
  - [Repository Contents](#repository-contents)
    - [Program Files](#program-files)
  - [Contributors](#contributors)

## About
This repository contains a client-server program for a train ticket reservation system developed for our Operating Systems course in Spring 2023 (Group B). The program uses socket connections for client/server interactions, multi-threading, thread pool, semaphores, mutex locks, and priority scheduling to handle client requests in a train ticket reservation system.

## Installation
To compile and run the program, you will need a C compiler like GCC. 

## Usage

### Server

1. Compile the server driver file with `make s`.
2. Run the server with `./s`.

### Client

1. Compile the client driver file with `make c`.
2. Run the client with `./c`.

## Important Notes

* The program handles ticket reservation, inquiry, modification, cancellation, and program exit.
* Both the client and server require 'Control + C' to stop the program execution.
* The client initiates a clientSocket send/receive operation with the server on a random port number within a certain range.
* The server creates training files, prepares a summary file, initializes a mutex for thread pool operation, and spawns a certain number of server processes using fork.

## Repository Contents

### Program Files

* `driver_client.c` - main() for client
* `driver_server.c` - main() for server
* `parker_client.c` - client-side logic file. Handles client's menu selection and performs different operations based on the selection. Establishes TCP connection with the server.
* `parker_server.c` - server-side logic file. Handles request processing. Implements the thread pool, priority scheduling, server/client socket connection, and multi-threaded mutual exclusion.
* `parker_utility.c` - utility file providing common functionalities used by both client and server.
* `rasheed.c` - Contains functions and routines for creating, modifying, and cancelling a reservation for a train ticket.
* `thomas.c` - Responsible for generating a receipt for the customer's order. The `sendReceiptToCust` function creates a receipt including customer's name, DOB, government ID, travel date, number of travelers, and selected seats, and sends this receipt to the client socket.
* `header.h` - includes, global function, and struct definitions
* `Makefile` - file for managing build automation.

## Contributors

1. Parker Hague
2. Rasheed Abid
3. Thomas


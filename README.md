# OS-Group_F: Train Ticketing System

Course: Operating Systems, Spring 2021  
Assignment: Group Project F - Multi-threaded Train Ticketing System

## Table of Contents
- [OS-Group\_F: Train Ticketing System](#os-group_f-train-ticketing-system)
  - [Table of Contents](#table-of-contents)
  - [About The Project](#about-the-project)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
    - [Server](#server)
    - [Client](#client)
  - [Notes](#notes)
  - [Repository Structure](#repository-structure)
    - [Program Files](#program-files)
  - [Contributors](#contributors)

## About The Project
The repository contains a train ticket reservation system implemented in C for the Operating Systems course, Spring 2023. The project is based on a client-server model, using socket connections for communication. The server utilizes multi-threading, a thread pool, semaphores, mutex locks, and priority scheduling to handle client requests effectively.

## Getting Started

### Prerequisites
- GCC compiler

### Installation
1. Clone the repository.
2. Navigate to the directory containing the source code.
3. Use the `Makefile` for easy compilation of the program files.

## Usage

### Server

1. Compile the server driver file using the command: `make s`.
2. Run the server with: `./s`.

### Client

1. Compile the client driver file using the command: `make c`.
2. Run the client with: `./c`.

## Notes
- The program functionalities include ticket reservation, inquiry, modification, cancellation, and program exit.
- The server prepares a summary file, initializes a mutex for thread pool operation, and spawns a certain number of server processes using fork.
- 'Control + C' is required to stop the execution on both client and server ends.

## Repository Structure

### Program Files

- `driver_client.c` - Entry point for client.
- `driver_server.c` - Entry point for server.
- `parker_client.c` - Handles client's menu selection and TCP connection with the server.
- `parker_server.c` - Manages server-side request processing. Includes implementation of the thread pool, priority scheduling, and multi-threaded mutual exclusion.
- `parker_utility.c` - Contains utility functions used by both client and server.
- `rasheed.c` - Features routines for creating, modifying, and cancelling a train ticket reservation.
- `thomas.c` - Creates and sends a receipt for the customer's order to the client socket.
- `header.h` - Contains global function definitions and structure definitions.
- `Makefile` - Used for build automation.

## Contributors

1. Parker Hague: Main client and server-side logic, implementation of multi-threading, thread pool, priority scheduling, and socket connection.
2. Rasheed Abid: Logic for creating, modifying, and cancelling a reservation for a train ticket.
3. Thomas: Contribution to generating a receipt for the customer's order.

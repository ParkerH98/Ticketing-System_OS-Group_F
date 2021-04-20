
#include "rasheedPR.c"
#include "parkerPR.c"

int main()
{
    // ================================================
    //                  Parker's Code
    // ================================================

    printf("BEGINNING OF PARKER'S TEST CODE\n");
    pid_t pid;
    pid = fork(); // creates a child process

    if (pid == 0) // child process
    {
        serverSocket_SendReceive(PORT); // starts server and begins listening

        exit(0);
    }
    else if (pid > 0) // parent process
    {
        sleep(1);
        clientSocket_SendReceive(PORT);
    }
    printf("END OF PARKER'S TEST CODE\n");

    sleep(2); // to allow time between mine and rasheed's code to execute

    // }
    // ================================================
    //                  Parker's Code
    // ================================================

    // ================================================
    //                  Rasheed's Code
    // ================================================
    printf("BEGINNING OF RASHEED'S TEST CODE\n");

    server();

    printf("END OF RASHEED'S TEST CODE\n");

    // ================================================
    //                  Rasheed's Code
    // ================================================
}

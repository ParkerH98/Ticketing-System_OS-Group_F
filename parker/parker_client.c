
#include "../header.h"

/*
---------------------------------------------------------
This function handles all of the client socket connections.
This function connects to the server and sends a query. The 
function then waits and receives a result back from the server.

Params: char pointers of query fields: employee name, job title, and status
Return: an Employee structure instance containing the resulted employee
*/
struct EmployeeStructure clientSocket_SendReceive(char *employeeName, char *jobTitle, char *status)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // sets values: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr(IP);                    //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, employeeName);
    strcpy(queryPtr->jobTitle, jobTitle);
    strcpy(queryPtr->status, status);

    send(clientSocket, queryPtr, sizeof(struct Query), 0);
    printf("CLIENT: Query sent to server.\n\n");

    struct EmployeeStructure employee;
    struct EmployeeStructure *employeePtr = &employee;

    read(clientSocket, employeePtr, sizeof(struct EmployeeStructure));

    printf("CLIENT: Result received from server.\n");
    printf("Id: %d\n", employee.id);
    printf("Employee Name: %s\n", employee.employeeName);
    printf("Job Title: %s\n", employee.jobTitle);
    printf("Base Pay: %f\n", employee.basePay);
    printf("Overtime Pay: %f\n", employee.overtimePay);
    printf("Benefit: %f\n", employee.benefit);
    printf("Status: %s\n", employee.status);
    printf("Satisfaction Level: %f\n", employee.satisfactionLevel);
    printf("Number of Projects: %d\n", employee.numberProject);
    printf("Average Monthly Hours: %d\n", employee.averageMonthlyHours);
    printf("Company Time (Years): %d\n", employee.yearsInCompany);
    printf("Work Accident: %d\n", employee.workAccident);
    printf("Promotion in Last 5 Years: %d\n", employee.promotionsLast5Years);

    close(clientSocket);
    return employee;
}
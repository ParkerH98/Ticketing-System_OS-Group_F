#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>



void searchticket( int ticket ) // still working
{
    char filename[32];
    char temp[10];
    
    sprintf(temp, "%d", ticket);
    strcpy(filename, temp);
    strcat(filename, "_r.txt");


    if( fopen(filename, "r") )
    {
        printf("Ticket FOUND %d\n", ticket);

        FILE *fp1;
        fp1 = fopen(filename, "r");

        char temp[50];
        fscanf(fp1, "%[^\n]", temp);
        printf("%s\n", temp);
        
        char temp[50];
        fscanf(fp1, "%[^\n]", temp);
        printf("%s\n", temp);

        char temp[50];
        fscanf(fp1, "%[^\n]", temp);
        printf("%s\n", temp);

        char temp[50];
        fscanf(fp1, "%[^\n]", temp);
        printf("%s\n", temp);

        printf("===========");

        fclose(fp1);

    }
    else
    {
        printf("Ticket not found.\n");
    }
}


void PrintTrain( int day ) 
{
    char Train[32];
    char temp[4];

    sprintf(temp, "%d", day);

    strcpy(Train, "train_day");
    strcat(Train, temp);
    strcat(Train, ".txt");


    printf("%s\n", Train);


    FILE *fp1; 
    fp1 = fopen(Train, "r");


    printf("Your desired train to Hogwarts seats' are shown below:\n");
    for(int i = 1; i<31; i++)
    {
        printf("%5d", i);
        if(i%10 == 0) printf("\n");
    }
    char train_seats[32];
    fscanf(fp1, "%[^\n]", train_seats);

    printf("Available seats at the moment: ");
    for(int i = 0; i < 30; i++)
    {
        if( train_seats[i] == '0' ) printf("%3d", i+1);
    }
    printf("\n");

    fclose(fp1);
} 



int main()
{
    FILE *f, *f2;
    f = fopen("train_day1.txt", "w");
    f2 = fopen("train_day2.txt", "w");

    char t[30]; 
    for(int i=0; i<30;i++)
    {
        t[i] = '0';
    }

    fprintf(f, "%s", t); 
    fprintf(f2, "%s", t);

    fclose(f);
    fclose(f2);

}
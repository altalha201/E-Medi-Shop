#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "Types.h"
#include "Sub.h"
#include "Utility.h"
#include "Work.h"

#define MAX_SIZE 10000

void systemOperation()
{
    system("COLOR C");
    int choise;
    int selection;

    while(1)
    {
        readFromFile();
        printf("\n\n\t\t\t\t---------------------------------------\n");
        printf("\t\t\t\t|          Setup Your System          |\n");
        printf("\t\t\t\t---------------------------------------\n\n\n");
        printf("\t\t\t\t\t 1. Check All Medicines\n");
        printf("\t\t\t\t\t 2. Add Medicine\n");
        printf("\t\t\t\t\t 3. Remove Medicine\n");
        printf("\t\t\t\t\t 4. Update Medicine's Price\n");
        printf("\t\t\t\t\t 5. Last Order\n");
        printf("\t\t\t\t\t 6. History\n");
        printf("\t\t\t\t\t 7. Exit\n");

        printf("\nEnter your option:- ");
        scanf("%d", &choise);
        getchar();

        switch(choise)
        {
        case 1:
            printAll();
            clear();
            break;
        case 2:
            addMedicine();
            break;
        case 3:
            printf("\nEnter Code to remove:- ");
            scanf("%d", &selection);
            removeMedicine(selection);
            break;
        case 4:
            printf("\nEnter Code to update:- ");
            scanf("%d", &selection);
            updatePrice(selection);
            break;
        case 5:
            printLastOrder();
            break;
        case 6:
            history();
            break;
        case 7:
            saveToFileMedi();
            clear();
            system("COLOR 70");
            return;
        default:
            printf("Invalid Option\nReenter Your Option.\n");
        }
    }

    return;
}

void customerEnd()
{
    system("color 3f");
    int option;

    while(1)
    {
        printf("\n\n\t\t\t\t--------------------------------------\n");
        printf("\t\t\t\t|       Welcome to E-Medi Shop       |\n");
        printf("\t\t\t\t--------------------------------------\n\n");
        printf("\t\t\t\tWish You A Good Day!!\n");
        printf("\t\t\t\t\t 1. Order\n");
        printf("\t\t\t\t\t 2. Receive\n");
        printf("\t\t\t\t\t 3. Exit\n");

        printf("\nEnter Your Option:- ");
        scanf("%d",&option);
        getchar();


        switch(option)
        {
        case 1:
            readFromFile();
            get_order();
            break;
        case 2:
            deliver();
            break;
        case 3:
            clear();
            system("COLOR 70");
            return;
        default:
            printf("Invalid Option\nReenter Your Option.\n");
        }
    }
}

void end_tag()
{
    system("cls");
    system ("COLOR A");
    FILE *fp;
    char note[MAX_SIZE];

    fp = fopen("Development Note.txt", "r");
    if(fp == NULL) {
        puts("Error Opening File");
        return;
    }
    while(fgets(note, MAX_SIZE, fp) != NULL) {
        printf("%s", note);
    }
    fclose(fp);

    puts("\n\nEnter any key to Continue....");
    getch();
}


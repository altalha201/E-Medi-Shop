#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Types.h"
#include "Sub.h"
#include "Utility.h"
#include "Work.h"

int main()
{
    system("COLOR 70");
    while(1)
    {
        int option;
        char givePassword[10];
        char mainPassword[] = "123456";

        printf("\n\n\t\t\t\t--------------------------------------\n");
        printf("\t\t\t\t|       Welcome to E-Medi Shop       |\n");
        printf("\t\t\t\t--------------------------------------\n\n\n");
        printf("\t\t\t\t\t 1. System Operation\n");
        printf("\t\t\t\t\t 2. Customer End\n");
        printf("\t\t\t\t\t 3. Finish\n");
        printf("Your Option:- ");
        scanf("%d",&option);
        getchar();


        switch(option)
        {
        case 1:
            printf("\nGive your Password: ");
            gets(givePassword);
            if(strcmp(givePassword, mainPassword) == 0) {
                system("cls");
                systemOperation();
            }
            else {
                printf("Invalid Password! Try Again or Try Customer End.....\n");
                clear();
            }
            break;
        case 2:
            system("cls");
            customerEnd();
            break;
        case 3:
            end_tag();
            break;
        default:
            printf("Invalid Option\nReenter Your Option.\n");
            clear();
        }
        if(option == 3)
            break;
    }
}

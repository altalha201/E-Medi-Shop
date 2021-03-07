#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "Types.h"
#include "Utility.h"
#include "Work.h"

#define MAX_SIZE 10000

/** Global Declaration */
int order_count = 0, delivered = 0, wait_to_deliver = 0;
int currentSize = 0;
long int totalCollection = 0;

medicines product[MAX_SIZE];

void printAMedicien(int index)
{
    if(index < 0 || index > currentSize) {
        puts("No Medicine Found!");
        return;
    }
    medicines m = product[index];

    printf("\t\tProduct Code     : %04d\t\t", m.mediCode);
    printf("Brand Name       : %s\n", m.brandName);
    printf("\t\tType             : %s\t", m.mediType);
    printf("Pieces / Packet  : %d\t", m.pieces);
    printf("Price / Packet   : %d/=\n", m.price);
}

void printAll()
{
    if(currentSize == 0) {
        puts("\n\nNo Medicine have been listed!");
        return;
    }

    printf("\n\t |.................................MADICIENS...................................|\n\n");
    for(int i = 0; i < currentSize; i++) {
        printAMedicien(i);
        puts("");
    }
}

void readFromFile()
{
    FILE *fp;
    if((fp = fopen("Medicine.db", "rb")) == NULL) {
        puts("\nError: Can't load the database file");
        return;
    }

    if(fread(&currentSize, sizeof(currentSize), 1, fp) != 1) {
        puts("\nError: Can't read data!");
        return;
    }
    if(fread(product, sizeof(product), 1, fp) != 1) {
        puts("\nError: Can't read data!");
        return;
    }
}

void saveToFileMedi()
{
    FILE *fp;

    if( (fp = fopen("Medicine.db", "wb")) == NULL) {
        puts("\nError: can't create a database file!");
        return;
    }

    if(fwrite(&currentSize, sizeof(currentSize), 1, fp) != 1) {
        puts("\nError: can't save data!");
        return;
    }

    if(fwrite(product, sizeof(product), 1, fp) != 1) {
        puts("Error: can't save data!");
        return;
    }

    puts("\nDatabase Updated!");
}

void addMedicine()
{
    if(currentSize == MAX_SIZE) {
        puts("Medicine List is Full!");
        clear();
        return;
    }

    int i;
    medicines m;
    m.mediCode = currentSize;
    printf("Enter Brand Name:- ");
    gets(m.brandName);
    printf(" 1. Tablet\n");
    printf(" 2. Syrup\n");
    printf(" 3. Suspension\n");
    printf(" 4. Others\n");
    printf("Medicine Type:- ");
Here:
    scanf("%d", &i);

    switch(i)
    {
    case 1:
        strcpy(m.mediType, "Tablet");
        break;
    case 2:
        strcpy(m.mediType, "Syrup");
        break;
    case 3:
        strcpy(m.mediType, "Suspension");
        break;
    case 4:
        printf("Enter Type:- ");
        gets(m.mediType);
        break;
    default:
        puts("Invalid!!");
        goto Here;
    }

    printf("Pieces in a packet:- ");
    scanf("%d", &m.pieces);
    printf("Price Per Packet:- ");
    scanf("%d", &m.price);

    product[currentSize] = m;
    ++currentSize;

    saveToFileMedi();
    puts("Item Added!");
    clear();
}

void removeMedicine(int number)
{
    if(number > currentSize || number < 0) {
        puts("Invalid Code Try again...");
        clear();
        return;
    }

    int i, j;
    for(i = 0; i < currentSize; i++) {
        if(product[i].mediCode == number) {
            for(j = i; j < currentSize - 1; j++) {
                product[j] = product[j+1];
                product[j].mediCode--;
            }
            product[j].mediCode = 0;
            product[j].pieces = 0;
            product[j].price = 0;
            strcpy(product[j].brandName, "");
            strcpy(product[j].mediType, "");

            currentSize -= 1;
        }
    }

    saveToFileMedi();
    puts("\nItem Deleted...");
    clear();
}

void updatePrice(int code)
{
    if(code > currentSize || code < 0) {
        puts("Invalid Code Try again...");
        clear();
        return;
    }
    int i;
    for(i = 0; i < currentSize; i++) {
        if(product[i].mediCode == code) {
            printf("Enter New Price:- ");
            scanf("%d", &product[i].price);
	    saveToFileMedi();
            puts("\nPrice Updated Successfully...");
            break;
        }
    }
    clear();
}

void history()
{
    system("cls");
    system("color 4f");
    char ch;
    printf("\n\n\t Total collection till the system Start:- %ld/=\n", totalCollection);
    printf("\n\t Number of Order Taken: %d\n", (count()));
    printf("\t Total Delivered: %d\n", delivered);
    printf("\t Waiting for delivery: %d\n\n", (count()-delivered));
    printf("Want to See Customer History?(Y/N) ");
    scanf("%c", &ch);
    getchar();
    if(ch == 'Y' || ch == 'y')
        print_history();

    clear();
    system("COLOR C");
}

void print_history()
{
    struct order* p = head;
    printf("\n");
    while(p != NULL)
    {
        printf("Customer Name               :\t %s\n", p->name);
        printf("Number of medicine ordered  :\t %d\n", p->number_of_medicine);
        printf("Total Bill                  :\t %d/=\n\n", p->bill);
        p = p->next;
    }
}

void printLastOrder()
{
    FILE *fp;
    char list[MAX_SIZE];

    fp = fopen("order.txt", "r");
    if(fp == NULL) {
        puts("Error Opening File");
        return;
    }
    while(fgets(list, MAX_SIZE, fp) != NULL) {
        printf("%s", list);
    }
    fclose(fp);
    clear();
}

void get_order()
{
    system("cls");
    system("color 3f");

    deletePrivioslist();

    if(currentSize == 0) {
        puts("\nEnvironment Not been Setup Earlier");
        clear();
        return;
    }

    int n, k, p, t;
    struct order* temp;
    temp = (struct order*)malloc(sizeof(struct order));
    printf("\n\nEnter Your Name:- ");
    gets(temp->name);
    temp->order_number = 10000 + order_count;
    printAll();
    temp->number_of_medicine = 0;
    temp->bill = 0;

Level:
    printf("Number of Medicines You Need:- ");
    scanf("%d", &n);
    getchar();

    while(n--)
    {
        printf("Enter Medicine Code: ");
        scanf("%d", &k);

        if(check(k) == 1) {
            printf("Number of Packet(s): ");
            scanf("%d", &p);
            getchar();
            t = price(k);
            addToLastOrder(k, p);

            temp->number_of_medicine += p;
            temp->bill += (t * p);
        }
        else {
            puts("Invalid Code! Reenter Code");
            n++;
        }

    }
    char wm;
    printf("\nWant more to Buy?(Y/N) ");
    scanf("%c", &wm);
    if(wm == 'Y' || wm == 'y')
        goto Level;

    totalCollection += temp->bill;

    printf("\n\nYou ordered %d Product(s).\n", temp->number_of_medicine);
    printf("Your Bill is:- %d/=\n", temp->bill);
    printf("Thank You %s for using the system to buy your needs.\n", temp->name);
    printf("Your order will delivered to you soon.\n\n");

    temp->next = head;
    head = temp;

    clear();
    system("color 3f");
}

void addToLastOrder(int c, int q)
{
    struct oMedi* temp = (struct oMedi*)malloc(sizeof(struct oMedi));
    temp->code = c;
    temp->quantity = q;
    temp->next = head2;
    head2 = temp;

    saveToFileOrder();
}

void saveToFileOrder()
{
    FILE *fp;


    fp = fopen("order.txt", "w");

    if(fp == NULL) {
        puts("Error!");
    }
    else {
        struct oMedi* p = head2;
        while (p != NULL) {
            fprintf(fp, "Code: %04d\tQuantity: %d\n", p->code, p->quantity);
            p = p->next;
        }
    }
    fclose(fp);
}


void deliver()
{
    if(count() - delivered == 0)
    {
        printf("\n\n\tNo Request is pending....\n\n");
        clear();
    }
    else if(count() >= delivered)
    {
        delivered++;
        printf("\n\n\tLast Order Delivered....\n\n");
        clear();
    }
    else
    {
        printf("\n\n\tAll Order Delivered....\n\n");
        clear();
    }
}

void deletePrivioslist()
{
    struct oMedi* current = (struct oMedi*)malloc(sizeof(struct oMedi));
    struct oMedi* next = (struct oMedi*)malloc(sizeof(struct oMedi));

    current = head2;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head2 = NULL;
    saveToFileOrder();
}

int check(int code)
{
    int d = 0;
    medicines m;
    for(int i = 0; i < currentSize; i++) {
        m = product[i];
        if(m.mediCode == code) {
            d = 1;
            break;
        }
    }
    return d;
}

int count()
{
    int c = 0;
    struct order* p = head;
    while(p != NULL)
    {
        c++;
        p = p->next;
    }
    return c;
}

int price(int code)
{
    int d;
    medicines m;
    for(int i = 0; i < currentSize; i++) {
        m = product[i];
        if(m.mediCode == code) {
            d = m.price;
            break;
        }
    }
    return d;
}

#ifndef WORK_H
#define WORK_H

/** Common Function */
void printAMedicien(int index);
void readFromFile();
void printAll();
void deletePrivioslist();

/** System Operator Function */
void addMedicine();
void removeMedicine(int number);
void updatePrice(int code);
void history();
void print_history();
void printLastOrder();
void saveToFileMedi();

/** Customer Functions */
void get_order();
void deliver();
void addToLastOrder(int c, int q);
void saveToFileOrder();

int check(int code);
int count();
int price(int code);

#endif // WORK_H

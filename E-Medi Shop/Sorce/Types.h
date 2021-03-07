#ifndef TYPES_H
#define TYPE_H

/** Types */
struct order {
    char name[50];
    int order_number;
    int number_of_medicine;
    int bill;
    struct order *next;
} *head;

typedef struct {
    int mediCode; // 4 Digits
    char brandName[50];
    char mediType[50];
    int pieces; // Pieces/Packet
    int price; // Per Packet Price
} medicines;

struct oMedi {
    int code;
    int quantity;
    struct oMedi *next;
} *head2;

#endif // TYPES_H

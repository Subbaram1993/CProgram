#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct Passenger {
    char name[25];
    char sex[5];
    int age;
    char preference[7];
    char assigned_berth[15];
    struct Passenger *next;
} Passenger;

typedef struct Coach {
    char type[4];
} Coach;

void display_passenger(Passenger *p);
void assign_berth(Passenger *p, int coach_type);
void save_passen_details(Passenger *p);

#endif

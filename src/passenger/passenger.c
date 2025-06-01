#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "passenger.h"

#define FILENAME "pass_details.txt"

static char *pos_seats[5] = {"L", "M", "U", "SL", "SU"};
static char *berths[5] = {"Lower", "Middle", "Upper", "Side Lower", "Side Upper"};
static char *coach_ids[] = {"S1", "A1", "A2", "B1"};

static int lower_seats[] = {1, 4, 9, 12, 17, 20, 25, 28, 33, 36, 41, 44, 49, 52, 57, 60, 65, 68};
static int middle_seats[] = {2, 5, 10, 13, 18, 21, 26, 29, 34, 37, 42, 45, 50, 53, 58, 61, 66, 69};
static int upper_seats[] = {3, 6, 11, 14, 19, 22, 27, 30, 35, 38, 43, 46, 51, 54, 59, 62, 67, 70};
static int side_lower_seats[] = {7, 15, 23, 31, 39, 47, 55, 63, 71};
static int side_upper_seats[] = {8, 16, 24, 32, 40, 48, 56, 64, 72};

static int seat_index[5] = {0};

void display_passenger(Passenger *p)
{
    if (p == NULL) {
        return;
    }
    printf("\nEntered Passenger Details are:\n");
    printf("Name: %s\nAge: %d\nSex: %s\nPreferred Berth: %s\nAssigned Berth: %s\n",
           p->name, p->age, p->sex, p->preference, p->assigned_berth);
}

void assign_berth(Passenger *p, int coach_type)
{
    int *seat_list[] = {lower_seats, middle_seats, upper_seats, side_lower_seats, side_upper_seats};
    int seat_counts[] = {18, 18, 18, 9, 9};
    int pref_index = -1;

    for (int i = 0; i < 5; i++) {
        if (strcmp(p->preference, pos_seats[i]) == 0) {
            pref_index = i;
            break;
        }
    }

    int assigned = 0;
    for (int i = 0; i < 5; i++) {
        int index = (pref_index + i) % 5;
        if (seat_index[index] < seat_counts[index]) {
            int seat_num = seat_list[index][seat_index[index]];
            seat_index[index]++;
            sprintf(p->assigned_berth, "CNF/%s/%d", coach_ids[coach_type], seat_num);
            assigned = 1;
            break;
        }
    }

    if (!assigned) {
        strcpy(p->assigned_berth, "WL/NA/NA");
    }
}

void save_passen_details(Passenger *p)
{
    FILE *fp1 = fopen(FILENAME, "a");
    if (fp1 == NULL) {
        printf("\nUnable to open the file to save Passenger Details.\n");
        return;
    }
    fprintf(fp1, "%s,%s,%d,%s,%s\n", p->name, p->sex, p->age, p->preference, p->assigned_berth);
    fclose(fp1);
    printf("\nPassenger details saved successfully.\n");
}

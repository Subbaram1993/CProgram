#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passenger.h"

Passenger *pass_head = NULL;

int main()
{
    int coa_ty, s_pref;
    char *selec_coach, *seat_pref;
    Passenger *first = NULL;
    Coach coach[4] = {{"SLR"}, {"1AC"}, {"2AC"}, {"3AC"}};

    printf("\nSelect the Coach(1.SLR,2.1AC,3. 2AC, 4. 3AC) :");
    scanf("%d", &coa_ty);

    switch (coa_ty) {
    case 1:
        selec_coach = "SLR";
        break;
    case 2:
        selec_coach = "1AC";
        break;
    case 3:
        selec_coach = "2AC";
        break;
    case 4:
        selec_coach = "3AC";
        break;
    default:
        printf("\nCoach Not selected.\n");
        return 1;
    }

    first = (Passenger *)malloc(sizeof(Passenger));
    if (first == NULL) {
        printf("\nInsufficient Resources.\n");
        return -1;
    }

    printf("\nEnter the Details of the Passenger:\n");
    printf("\nName of the Passenger: ");
    scanf(" %[^\n]", first->name);
    printf("\nSex (M/F)?: ");
    scanf(" %s", first->sex);
    printf("\nAge of the Passenger: ");
    scanf("%d", &first->age);
    printf("\nSeat Preference (1.L/2.M/3.U/4.SL/5.SU)?: ");
    scanf(" %d", &s_pref);

    switch (s_pref) {
    case 1:
        seat_pref = "L";
        break;
    case 2:
        seat_pref = "M";
        break;
    case 3:
        seat_pref = "U";
        break;
    case 4:
        seat_pref = "SL";
        break;
    case 5:
        seat_pref = "SU";
        break;
    default:
        seat_pref = "M";
    }

    strcpy(first->preference, seat_pref);
    first->next = NULL;

    if (pass_head == NULL) {
        pass_head = first;
    } else {
        Passenger *temp = pass_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = first;
    }

    assign_berth(first, coa_ty - 1);
    display_passenger(first);
    save_passen_details(first);

    return 0;
}

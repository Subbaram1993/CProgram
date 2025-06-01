#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "train_details.h"

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int main() {
    int halt_len, i, j, k, src_index, dest_index;
    char src_stn[25], dest_stn[25];
    int match_trains[NUM_TRAINS], match_count = 0;

    printf("\nEnter Source Station (e.g., Gudur): ");
    scanf("%24s", src_stn);
    to_lowercase(src_stn);

    printf("Enter Destination Station (e.g., VijayawadaJn): ");
    scanf("%24s", dest_stn);
    to_lowercase(dest_stn);

    halt_len = sizeof(halts[0]) / sizeof(halts[0][0]);

    // Find all trains where source and destination appear in order
    for (i = 0; i < NUM_TRAINS; i++) {
        src_index = -1;
        dest_index = -1;

        for (j = 0; j < halt_len; j++) {
            if (strlen(halts[i][j].station) == 0) break;

            char temp_station[25];
            strncpy(temp_station, halts[i][j].station, sizeof(temp_station));
            temp_station[sizeof(temp_station) - 1] = '\0';
            to_lowercase(temp_station);

            if (strstr(temp_station, src_stn) != NULL && src_index == -1) {
                src_index = j;
            }
            if (strstr(temp_station, dest_stn) != NULL && dest_index == -1) {
                dest_index = j;
            }
        }

        if (src_index != -1 && dest_index != -1 && src_index < dest_index) {
            match_trains[match_count++] = i;
        }
    }

    if (match_count == 0) {
        printf("\nNo matching trains found for the given route.\n");
    } else {
        for (k = 0; k < match_count; k++) {
            i = match_trains[k];
            printf("\n==========================================================\n");
            printf("%s (%d) | Route: %s\n", train[i].name, train[i].number, train[i].route);
            printf("----------------------------------------------------------\n");

            src_index = -1;
            dest_index = -1;
            for (j = 0; j < halt_len; j++) {
                if (strlen(halts[i][j].station) == 0) break;

                char temp_station[25];
                strncpy(temp_station, halts[i][j].station, sizeof(temp_station));
                temp_station[sizeof(temp_station) - 1] = '\0';
                to_lowercase(temp_station);

                if (strstr(temp_station, src_stn) != NULL && src_index == -1) {
                    src_index = j;
                }
                if (strstr(temp_station, dest_stn) != NULL && dest_index == -1) {
                    dest_index = j;
                }
            }

            printf("From: %-25s    To: %-25s\n", halts[i][src_index].station, halts[i][dest_index].station);
            printf("Departs: %-20s    Arrives: %-20s\n", halts[i][src_index].departure, halts[i][dest_index].arrival);

            printf("----------------------------------------------------------\n");
            printf("%-25s %-10s %-15s %-10s\n", "Station Name", "Arrival", "Departure", "Day");
            printf("----------------------------------------------------------\n");
            for (j = src_index; j <= dest_index; j++) {
                printf("%-25s %-10s %-15s %-10s\n",
                       halts[i][j].station,
                       halts[i][j].arrival,
                       halts[i][j].departure,
                       halts[i][j].day);
            }
        }
    }

    printf("==========================================================\n");
    return 0;
}

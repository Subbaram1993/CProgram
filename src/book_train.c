#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "train_details.h"

#define GRAY   "\033[1;90m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

// Train search result struct
typedef struct {
	int train_index;
	int src_index;
	int dest_index;
} TrainMatch;

// Passenger struct and booking logic
typedef struct Passenger {
	char name[50];
	char sex[2];
	int age;
	char preference[3];
	char berth_assigned[20];
	struct Passenger *next;
} Passenger;
Passenger *pass_head = NULL;

// Global arrays for berth seat numbers
int lower_seats[]       = {1, 4, 9, 12, 17, 20, 25, 28, 33, 36, 41, 44, 49, 52, 57, 60, 65, 68};
int middle_seats[]      = {2, 5, 10, 13, 18, 21, 26, 29, 34, 37, 42, 45, 50, 53, 58, 61, 66, 69};
int upper_seats[]       = {3, 6, 11, 14, 19, 22, 27, 30, 35, 38, 43, 46, 51, 54, 59, 62, 67, 70};
int side_lower_seats[]  = {7, 15, 23, 31, 39, 47, 55, 63, 71};
int side_upper_seats[]  = {8, 16, 24, 32, 40, 48, 56, 64, 72};

int seat_counts[] = {18, 18, 18, 9, 9};       // Total seats available per berth type
int seat_index[]  = {0, 0, 0, 0, 0};          // Tracks next available seat index per type

// Berth and coach ID labels
char *pos_seats[5] = {"L", "M", "U", "SL", "SU"};     // Preferences
char *coach_ids[]  = {"SLR", "1AC", "2AC", "3AC"};    // Coach types


void to_lowercase(char *str) {
	while (*str) {
		*str = tolower((unsigned char)*str);
		str++;
	}
}

void extract_station_code(char *dest, const char *src) {
	const char *dash = strchr(src, '-');
	if (dash) {
		strncpy(dest, dash + 1, 24);
		dest[24] = '\0';
	} else {
		dest[0] = '\0';
	}
}

int station_match(const char *input, const char *data_station) {
	char input_lower[25], data_name[25], data_code[25];
	
	strncpy(input_lower, input, 24);
	input_lower[24] = '\0';
	to_lowercase(input_lower);
	
	extract_station_code(data_name, data_station);
	extract_station_code(data_code, data_station);
	to_lowercase(data_name);
	to_lowercase(data_code);
	
	return (strcmp(input_lower, data_name) == 0 || strcmp(input_lower, data_code) == 0);
}

int is_na(const char* time) {
	return strcmp(time, "NA") == 0 || strcmp(time, "N.A") == 0;
}

int search_trains(const char *src, const char *dest, TrainMatch matches[], int max_matches) {
	int halt_len = MAX_HALTS, match_count = 0, src_index, dest_index, i,j;
	
	for (i = 0; i < NUM_TRAINS && match_count < max_matches; i++) {
		src_index = -1;
		dest_index = -1;
		for (j = 0; j < halt_len; j++) {
			if (strlen(halts[i][j].station) == 0) break;
			
			if (station_match(src, halts[i][j].station) && src_index == -1) {
				src_index = j;
			}
			if (station_match(dest, halts[i][j].station) && dest_index == -1) {
				dest_index = j;
			}
		}
		if (src_index != -1 && dest_index != -1 && src_index < dest_index) {
			matches[match_count].train_index = i;
			matches[match_count].src_index = src_index;
			matches[match_count].dest_index = dest_index;
			match_count++;
		}
	}
	return match_count;
}

// Print detailed info for the train route between src and dest indices
void print_train_details(int train_i, int src_index, int dest_index) {

	printf("\n==========================================================\n");
	printf("\033[1;32m%s\033[0m (\033[0;31m%d\033[0m) | Route: %s\n", train[train_i].name, train[train_i].number, train[train_i].route);
	printf("----------------------------------------------------------\n");
	printf("From: %-25s    To: %-25s\n", halts[train_i][src_index].station, halts[train_i][dest_index].station);
	printf("Departs: %-25s Arrives: %-20s\n", halts[train_i][src_index].departure, halts[train_i][dest_index].arrival);
	printf("----------------------------------------------------------\n");
	printf("%-25s %-10s %-15s %-10s\n", "Station Name", "Arrival", "Departure", "Day");
	printf("----------------------------------------------------------\n");
	for (int j = src_index; j <= dest_index; j++) {
		const char* arrival = halts[train_i][j].arrival;
		const char* departure = halts[train_i][j].departure;

		const char* arrival_display = is_na(arrival) ? GRAY : YELLOW;
	        const char* departure_display = is_na(departure) ? GRAY : YELLOW;

		const char* arrival_reset = (strcmp(arrival, "NA") == 0) ? RESET : RESET;
	        const char* departure_reset = (strcmp(departure, "NA") == 0) ? RESET : RESET;
		printf("%-25s %s%-10s%s %s%-15s%s %-10s\n",
				halts[train_i][j].station,
				arrival_display,arrival,arrival_reset,
				departure_display, departure,departure_reset,
				halts[train_i][j].day);
	}
	printf("==========================================================\n");
}


//Assigning the Berth in a realistic way
void assign_berth(Passenger *p, int coach_type) {
	int pref_index, i, idx, seat_no, coach_number;
    // Seating coaches start from coach_type = 4 or higher
    // We'll assume: 0=SLR, 1=1AC, 2=2AC, 3=3AC are Sleeper types
    // 4=CC (Chair Car), 5=2S (Second Sitting), etc.

        if (coach_type <= 3) {
		int *seat_list[5] = {
			lower_seats,
			middle_seats,
			upper_seats,
			side_lower_seats,
			side_upper_seats
		};
		pref_index = -1;
		// Find preferred seat type
                for (i = 0; i < 5; i++) {
			if (strcmp(p->preference, pos_seats[i]) == 0) {
				pref_index = i;
				break;
			}
		}
		
		if (pref_index == -1) pref_index = 1; // Default to middle
		for (i = 0; i < 5; i++) {
			idx = (pref_index + i) % 5;
			if (seat_index[idx] < seat_counts[idx]) {
				seat_no = seat_list[idx][seat_index[idx]];
				seat_index[idx]++;
				coach_number = coach_type + 1;
				sprintf(p->berth_assigned, "CNF/S%d/%d/%s", coach_number, seat_no, pos_seats[idx]);
				return;
			}
		}
		
		// If no berth available
        	strcpy(p->berth_assigned, "WL/NA/NA");
	} else {
		// Seating coach seat assignment (no berth type)
        	static int cc_seat_no = 1;
        	static int ts_seat_no = 1;
       		char *coach_code;
        	int seat_no;
        	char seat_type_char = '-';
		
		switch (coach_type) {
			case 4: coach_code = "CC"; seat_no = cc_seat_no++; break;
			case 5: coach_code = "2S"; seat_no = ts_seat_no++; break;
			default: coach_code = "GEN"; seat_no = 0; break;
		}
		// Use preference for seating
		if (strcmp(p->preference, "W") == 0) seat_type_char = 'W';
		else if (strcmp(p->preference, "M") == 0) seat_type_char = 'M';
		else if (strcmp(p->preference, "A") == 0) seat_type_char = 'A';
		
		if (seat_type_char != '-') {
			sprintf(p->berth_assigned, "CNF/%s/%d/%c", coach_code, seat_no, seat_type_char);
		}else {
			sprintf(p->berth_assigned, "CNF/%s/%d", coach_code, seat_no);
		}
	}
}

void display_passenger(Passenger *p) {
	printf("\nEntered Passenger Details are:\n");
	printf("Name: %s\nAge: %d\nSex: %s\nPreferred Berth: %s\nAssigned Berth: %s\n",
			p->name, p->age, p->sex, p->preference, p->berth_assigned);
}

void save_passenger(Passenger *p) {
	// Save to file (append)
  	FILE *fp = fopen("passengers.txt", "a");
	if (fp) {
		fprintf(fp, "%s,%s,%d,%s,%s\n", p->name, p->sex, p->age, p->preference, p->berth_assigned);
		fclose(fp);
		printf("\nPassenger details saved successfully.\n");
	} else {
		printf("Error saving passenger data.\n");
	}
}

int main() {
	char source[25], destination[25], category[10];
    	TrainMatch matches[NUM_TRAINS];
    	int choice, found_count, assign_coach_type,coach_type, seat_pref_i;
	char *coach_str, *pref_str;

    	printf("Enter Source Station :");
    	scanf(" %24[^\n]", source);
    	printf("Enter Destination Station : ");
    	scanf(" %24[^\n]", destination);

    	found_count = search_trains(source, destination, matches, NUM_TRAINS);

    	if (found_count == 0) {
		printf("No trains found for the given route.\n");
		return 0;
	}
	
	printf("\nFound %d trains:\n", found_count);
	for (int i = 0; i < found_count; i++) {
	       	printf("[%d]", i + 1);
		print_train_details(matches[i].train_index, matches[i].src_index, matches[i].dest_index);
	}
	
	printf("Select train to book (1-%d): ", found_count);
	scanf("%d", &choice);
	if (choice < 1 || choice > found_count) {
		printf("Invalid choice.\n");
		return 1;
	}
	
	TrainMatch sel = matches[choice - 1];
	printf("\nBooking on train:\033[1;32m%s\033[0m (\033[0;31m%d\033[0m) \n", train[sel.train_index].name, train[sel.train_index].number);
	
	Passenger *p = malloc(sizeof(Passenger));
	if (!p) {
		printf("Memory allocation failed.\n");
		return 1;
	}
	strcpy(category, train[sel.train_index].category);
	
	if (strcmp(category, "Sleeper") == 0) {
		printf("Select Coach (1.SLR, 2.1AC, 3.2AC, 4.3AC): ");
		scanf("%d", &coach_type);
		switch(coach_type) {
			case 1: coach_str = "SLR"; break;
            		case 2: coach_str = "1AC"; break;
            		case 3: coach_str = "2AC"; break;
            		case 4: coach_str = "3AC"; break;
            		default:
				printf("Invalid coach.\n");
				free(p);
				return 1;
		}
	} else {
		printf("Select Coach (1.CC - Chair Car, 2.2S - Second Seating): ");
		scanf("%d", &coach_type);
        	switch(coach_type) {
			case 1: coach_str = "CC"; break;
            		case 2: coach_str = "2S"; break;
            		default:
				printf("Invalid coach.\n");
				free(p);
				return 1;
		}
	}
	
	printf("Enter Passenger Name: ");
    	scanf(" %49[^\n]", p->name);
    	printf("Enter Sex (M/F): ");
    	scanf(" %1s", p->sex);
    	printf("Enter Age: ");
    	scanf("%d", &p->age);
	
	if (strcmp(category, "Sleeper") == 0) {
		printf("Seat Preference (1.L/2.M/3.U/4.SL/5.SU): ");
		scanf("%d", &seat_pref_i);
		switch(seat_pref_i) {
			case 1: pref_str = "L"; break;
            		case 2: pref_str = "M"; break;
            		case 3: pref_str = "U"; break;
            		case 4: pref_str = "SL"; break;
            		case 5: pref_str = "SU"; break;
            		default: pref_str = "M";
		}
		strcpy(p->preference, pref_str);
		assign_coach_type = coach_type - 1;  // Sleeper coaches index 0..3
	} else {
		printf("Seat Preference (1.W/2.M/3.A/4.N for None): ");
        	scanf("%d", &seat_pref_i);
        	switch(seat_pref_i) {
			case 1: pref_str = "W"; break;
            		case 2: pref_str = "M"; break;
            		case 3: pref_str = "A"; break;
            		case 4: pref_str = "-"; break;
            		default: pref_str = "-";
		}
		strcpy(p->preference, pref_str);
		assign_coach_type = coach_type + 3;  // Seating coaches index 4..5
	 }
	
	p->next = NULL;
	
	assign_berth(p, assign_coach_type);
	
	display_passenger(p);
	save_passenger(p);
	
	// Add passenger to linked list (optional for extended use)
	if (!pass_head)
		pass_head = p;
	else {
		Passenger *temp = pass_head;
		while(temp->next)
			temp = temp->next;
		temp->next = p;
	}
	return 0;
}


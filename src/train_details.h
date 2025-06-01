#ifndef TRAIN_DATA_H
#define TRAIN_DATA_H

#define NUM_TRAINS 6
#define MAX_HALTS  18

typedef struct {
    int number;
    char name[25];
    char route[10];
    char category[10];
} Train_name;

typedef struct {
    char station[25];
    char arrival[10];
    char departure[10];
    char day[10];
} Train_route_details;

extern Train_name train[NUM_TRAINS];
extern Train_route_details halts[NUM_TRAINS][MAX_HALTS];

#endif

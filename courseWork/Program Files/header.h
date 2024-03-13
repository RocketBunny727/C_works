#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void border(int choose);
int max(int a, int b);
int stateWeight(long state, int weights[], int n);
int statePrice(long state, int prices[], int n);
double naiveBackpack(int maxWeight, int *weights, int *prices, int n);
double meetInTheMiddle(int maxWeight, int *weights, int *prices, int n);
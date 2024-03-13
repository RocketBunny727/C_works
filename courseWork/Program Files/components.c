#include "header.h"

void border(int choose)
{
    switch (choose)
    {
    case 0:
        printf("============================================================\n");
        break;
    
    case 1:
        printf("======================ВВДЕННЫЕ-ДАННЫЕ=======================\n");
        break;

    case 2:
        printf("============================МЕНЮ============================\n");
        break;

    case 3:
        printf("=======================НАИВНЫЙ-РЮКЗАК=======================\n");
        break;

    case 4:
        printf("=====================MEET-IN-THE-MIDDLE=====================\n");
        break;

    case 5:
        printf("===========================ВРЕМЯ============================\n");

    default:
        break;
    }
}

int stateWeight(long state, int weights[], int n)
{
    long powerOfTwo = 1;
    int weight = 0;
    for (int i = 0; i < n; i++)
    {
        if ((powerOfTwo & state) != 0)
        {
            weight += weights[i];
        }
        powerOfTwo <<= 1;
    }
    return weight;
}

int statePrice(long state, int prices[], int n)
{
    long powerOfTwo = 1;
    int price = 0;
    for (int i = 0; i < n; i++) {
        if ((powerOfTwo & state) != 0)
        {
            price += prices[i];
        }
        powerOfTwo <<= 1;
    }
    return price;
}

double naiveBackpack(int maxWeight, int *weights, int *prices, int n) 
{
    int numOfItems = 0; // счетчик для колличества взятых вещей
    double time = 0.0; // переменная показывающая время работы программы
    clock_t begin = clock(); // начало отсчета
    clock_t end; // конец отсчета
    long count = pow(2, n); // колличество возможный наборов вещей (2 в степени n)
    int maxPrice = 0; // максимальная цена
    long maxState = 0; // переменная хранящая в себе взятый набор вещей
    int bestWeight = 0; // вес взятого набора вещей
    int numbers[n]; // массив хранящий в себе номера взятых в оптимальный набор вещей

    for (long state = 0; state < count; state++)
    {
        int price = statePrice(state, prices, n);
        int weight = stateWeight(state, weights, n);
        if (weight <= maxWeight)
        {
            if (maxPrice < price)
            {
                maxPrice = price;
                maxState = state;
                bestWeight = weight;
            }
        }
    }

    long powerOfTwo = 1;
    for (int i = 0; i < n; i++)
    {
        if ((powerOfTwo & maxState) > 0)
        {
            numbers[numOfItems] = i + 1;
            numOfItems++;
        }
        powerOfTwo <<= 1;
    }

    end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Оптимальное содержимое рюкзака: ");
    for(int i = 0; i < numOfItems; i++)
    {
        printf("Вещь#%d ", numbers[i]);
    }
    printf("\nОптимальный вес = %d; Оптимальная цена = %d;\n", bestWeight, maxPrice);

    return time;
}

int findMaxValue(int maxWeight, int mid, int B[][2])
{
    int maxPrice = 0;
    for (int i = 0; i < (1 << mid); i++)
    {
        int weight = B[i][0];
        int price = B[i][1];
        if (weight <= maxWeight && price > maxPrice)
        {
            maxPrice = price;
        }
    }
    return maxPrice;
}

void DivideAndConquer(int n, int mid, int A[][2], int B[][2], int *weights, int *prices)
{
    for (int i = 0; i < (1 << (n - mid)); i++)
    {
        int weight = 0, value = 0;
        for (int j = 0; j < (n - mid); j++)
        {
            if (i & (1 << j))
            {
                weight += weights[j];
                value += prices[j];
            }
        }
        A[i][0] = weight;
        A[i][1] = value;
    }
    for (int i = 0; i < (1 << mid); i++)
    {
        int weight = 0, value = 0;
        for (int j = 0; j < mid; j++)
        {
            if (i & (1 << j))
            {
                weight += weights[mid + j];
                value += prices[mid + j];
            }
        }
        B[i][0] = weight;
        B[i][1] = value;
    }
}

double meetInTheMiddle(int maxWeight, int *weights, int *prices, int n)
{
    double time = 0.0; //затраченное время
    clock_t begin = clock(); //начало отсчета
    int maxPrice = 0; //максимальная стоимость набора
    int mid = n / 2; //середина последовательности
    int A[1 << (n - mid)][2]; //первая половина последовательности
    int B[1 << mid][2]; //вторая половина последовательности
    if(n == 1 && weights[0] <= maxWeight)
    {
        maxPrice = prices[0];
        clock_t end = clock();
        time += (double)(end - begin) / CLOCKS_PER_SEC;
    }
    else
    {
    DivideAndConquer(n, mid, A, B, weights, prices);

    for (int i = 0; i < (1 << mid); i++)
    {
        int weight = A[i][0];
        int price = A[i][1];
        int j = (1 << mid) - 1;
        while (j >= 0 && B[j][0] + weight > maxWeight)
        {
            j--;
        }
        if (j >= 0)
        {
            price += findMaxValue(maxWeight - weight, mid, B);
            if (price > maxPrice)
            {
                maxPrice = price;
            }
        }
    }
    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    }
    printf("Оптимальная цена набора = %d;\n", maxPrice);
    return time;
}
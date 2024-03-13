#include "Program Files/header.h"

int main(int argc, char **argv)
{
    system("clear");
    if(argc < 4 || (argc - 2) % 2 != 0)
    {
        printf("Ошибка ввода данных\nФормат ввода аргументов консоли: <максимальная нагрузка рюкзака> <вес вещи#1> <цена вещи#1> ... <вес вещи#n> <цена вещи #n>; подробнее описано в файле README.txt\n");
        return 1;
    }

    if(atoi(argv[1]) == 0)
    {
        printf("Вы ввели недопустимый символ\n");
        return 1;
    }
    double time1 = 0.0, time2 = 0.0; //время работы алгоритмов
    int menu; //переменная для выбора пункта меню
    int n = (argc - 2) / 2; //колличество вещей
    int maxWeight = atoi(argv[1]); //максимальная загрузка
    int* weights = (int*) malloc(n * sizeof(int)); //массив весов
    int* prices = (int*) malloc(n * sizeof(int)); //массив цен
    
    n = 0;

    for(int i = 2; i < argc; i++)
    {
        if(i%2 == 0)
        {
            if(atoi(argv[i]) != 0)
            {
                weights[n] = atoi(argv[i]); 
            }
            else
            {
                printf("Вы ввели недопустимый символ\n");
                return 1;
            }
        }
        if(i%2 == 1)
        {
            if(atoi(argv[i]) != 0)
            {
                prices[n] = atoi(argv[i]);
                n++;
            }
            else
            {
                printf("Вы ввели недопустимый символ\n");
                return 1;
            }
        }
    }

    border(1);
    printf("Максимальная загрузка рюкзака: %d\n", maxWeight);
    for(int i = 0; i < n; i++)
    {
        printf("Вещь#%d: вес - %d цена - %d\n", i+1, weights[i], prices[i]);
    }
    border(2);

    printf("Выберите алгоритм работы программы:\n1. Наивный рюкзак\n2. Алгоритм Meet-in-the-middle\n3. Оба алгоритма\nЧтобы продолжить нажмите соответствующую клавишу\nВаш выбор: ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        border(3);
        time1 = naiveBackpack(maxWeight, weights, prices, n);
        border(5);
        printf("Время работы алгоритма 'Наивный рюкзак': %lf секунд\n", time1);
        border(0);
        break;
    case 2:
        border(4);
        time2 = meetInTheMiddle(maxWeight, weights, prices, n);
        border(5);
        printf("Время работы алгоритма Meet-in-the-middle: %lf секунд\n", time2);
        border(0);
        break;
    case 3:
        border(3);
        time1 = naiveBackpack(maxWeight, weights, prices, n);;
        border(4);
        time2 = meetInTheMiddle(maxWeight, weights, prices, n);
        border(5);
        printf("Время работы алгоритма 'Наивный рюкзак': %lf секунд\n", time1);
        printf("Время работы алгоритма Meet-in-the-middle: %lf секунд\n", time2);
        border(0);
        break;
    default:
        printf("Допустимые значения для ввода: 1, 2 и 3; подробнее в файле README.txt\n");
        break;
    }
    free(weights);
    free(prices);
    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPSILON 0.000001

double func(double x)
{
    return x * x - 3;
}

double mpd_method(double a, double b)
{
    int steps = 0;
    double c;
    while (((b - a) / 2) > EPSILON)
    {
        c = (a + b) / 2;
        steps += 1;
        if (func(c) == 0.0)
        {
            break;
        }
        else if (func(c) * func(a) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    printf("Колличество шагов: %d\n", steps);
    return c;
}

double hord_method(double a, double b)
{
    int steps = 0;
    double c , prev;
    do
    {
        prev = c;
        c = (a * func(b) - b * func(a)) / (func(b) - func(a));
        steps += 1;
        if (func(c) == 0.0)
        {
            break;
        }
        else if (func(c) * func(a) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        // printf("Шаг#%d: a = %lf; b = %lf\n", steps, a, b);
    }
    while(fabs(c - prev) > EPSILON);
    printf("Колличество шагов: %d\n", steps);
    return c;
}

double newton_method(double x)
{
    int steps = 0;
    double prev;
    while(fabs(x - prev) > EPSILON)
    {
        prev = x;
        x = x - (func(x) / (2 * x));

        steps += 1;
        // printf("Шаг#%d: x = %lf\nf(x) = %lf/n", steps, x, func(x));
    }
    printf("Колличество шагов: %d\n", steps);
    return x;
}

int main()
{
    double a, b;
    printf("Введите начальное значение a и b (через пробел): ");
    scanf("%lf %lf", &a, &b);

    if (func(a) * func(b) >= 0)
    {
        printf("Необходимо выбрать другие значения a и b, чтобы функция имела разные знаки на концах интервала.\n");
        return 1;
    }

    printf("=================Метод половинного деления=================\n");
    double root = mpd_method(a, b);
    printf("Приближенный корень уравнения: %lf\n", root);
    printf("========================Метод Хорд=========================\n");
    root = hord_method(a, b);
    printf("Приближенный корень уравнения: %lf\n", root);
    printf("======================Метод  Ньютона=======================\n");
    root = newton_method(b);
    printf("Приближенный корень уравнения: %lf\n", root);
    printf("===========================================================\n");
    return 0;
}
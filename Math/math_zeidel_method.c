#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.0001
#define MAX_SIZE 20

void multiply_by_main_diagonal(int n, double matrix[MAX_SIZE][MAX_SIZE], double constants[MAX_SIZE])
{
    double pivot;
    for(int i = 0; i < n; i++)
    {
        pivot = matrix[i][i];
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] /= pivot;
        }
        constants[i] /= pivot;
    }
}

void iteration_step(int n,double C[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE],double P[MAX_SIZE]) 
{
    double CP[MAX_SIZE] = {0};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // printf("(%.3lf * %.3lf) + ", P[j], C[i][j]);
            CP[i] += (P[j] * C[i][j]);
        }
        //printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        P[i] = B[i] - CP[i];
        printf("X%d = %.3lf", i + 1, P[i]);
    }
    printf("\n");
}

void zeidel_step(int n,double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE], double P[MAX_SIZE])
{
    for(int i = 0; i < n; i++) { 
        P[i] = B[i]; 
        for(int j = 0; j < n; j++) { 
            if (j != i) { 
                P[i] -= A[i][j] * P[j];
                printf("X%d = %.3lf", i + 1, P[i]);
            } 
        } 
    }
    printf("\n");
}

void print_matrix(int n, double matrix[MAX_SIZE][MAX_SIZE], double constants[MAX_SIZE])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.3lf ", matrix[i][j]);
        }
        printf("| %8.3lf\n", constants[i]);
    }
    printf("\n");
}

int exit_condition(int n, double C[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE])
{
    int exit;
    double max = 0;
    double C_max = -1000;
    double B_max = -1000;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            max += fabs(C[i][j]);
        }
        if(max > C_max)
        {
            C_max = max;
        }
        max = 0;
    }

    for(int i = 0; i < n; i++)
    {
        if(fabs(B[i]) > B_max)
        {
            B_max = fabs(B[i]);
        }
    }

    printf("C_max = %.3lf; B_max = %.3lf\n", C_max, B_max);

    exit = ((log((EPSILON * (1 - C_max) / B_max))) / log(C_max)) + 1;

    printf("N = %d\n", exit);

    return exit;
}

void buff_to_matrix(int n, double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE], double A_buff[MAX_SIZE][MAX_SIZE], double B_buff[MAX_SIZE])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A_buff[i][j] = A[i][j];
        }
        B_buff[i] = B[i];
    }
}

void simple_iteration_method(int n, double matrix[MAX_SIZE][MAX_SIZE], double constants[MAX_SIZE], int exit, double zeroable[MAX_SIZE][MAX_SIZE])
{
    double equal[MAX_SIZE];
    double equal_buff[MAX_SIZE];

    multiply_by_main_diagonal(n, matrix, constants);

    printf("Матрица A:\n");
    print_matrix(n, matrix, constants);
    printf("Матрица C:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%8.3lf ", zeroable[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < exit; i++)
    {
        printf("================step#%d================\n", i + 1);
        iteration_step(n, zeroable, constants, equal);
        printf("=======================================\n");
    }

    for(int i = 0; i < n; i++)
    {
        printf("X%d = %.3lf\n", i + 1, equal[i]);
    }
}

void zeidel_method(int n, double matrix[MAX_SIZE][MAX_SIZE], double constants[MAX_SIZE], int exit)
{
    double equal[MAX_SIZE] = {0};

    multiply_by_main_diagonal(n, matrix, constants);
    printf("Матрица A:\n");
    print_matrix(n, matrix, constants);

    for(int i = 0; i < exit; i++)
    {
        printf("================step#%d================\n", i + 1);
        zeidel_step(n, matrix, constants, equal);
        printf("=======================================\n");
    }

    for(int j = 0; j < n; j++)
    {
        printf("X%d = %.4lf\n", j + 1, equal[j]);
    }
}

int main()
{
    int n;
    int exit;
    printf("========================Начало  работы========================\n");
    printf("Введите количество уравнений: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_SIZE)
    {
        printf("Неверный размер.\n");
        return 1;
    }

    double A[MAX_SIZE][MAX_SIZE];
    double B[MAX_SIZE];
    double A_buff[MAX_SIZE][MAX_SIZE];
    double B_buff[MAX_SIZE];
    double Z[MAX_SIZE][MAX_SIZE];

    printf("Введите имя файла для чтения: ");
    char filename[100];
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка в файле %s\n", filename);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &A[i][j]);
        }
        fscanf(file, "%lf", &B[i]);
    }

    fclose(file);

    buff_to_matrix(n, A, B, A_buff, B_buff);
    printf("Матрица на вход:\n");
    print_matrix(n, A_buff, B_buff);

    multiply_by_main_diagonal(n, A_buff, B_buff);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            Z[i][j] = A_buff[i][j];
        }
        Z[i][i] = 0;
    }
    exit = exit_condition(n, Z, B_buff);
    buff_to_matrix(n, A, B, A_buff, B_buff);

    printf("====================Метод простых итераций====================\n");
    simple_iteration_method(n, A_buff, B_buff, exit, Z);
    buff_to_matrix(n, A, B, A_buff, B_buff);
    printf("========================Метод  Зейделя========================\n");
    zeidel_method(n, A_buff, B_buff, exit);
    buff_to_matrix(n, A, B, A_buff, B_buff);
    printf("==============================================================\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 10

void readMatrixFromKeyboard(int n, double matrix[MAX_SIZE][MAX_SIZE + 1], double matr[MAX_SIZE][MAX_SIZE + 1]) {
    printf("Введите элементы матрицы и вектора свободных членов:\n");
    for (int i = 0; i < n; i++) {
        printf("Строка %d: ", i + 1);
        for (int j = 0; j < n + 1; j++) {
            scanf("%lf", &matrix[i][j]);
            matr[i][j] = matrix[i][j];
        }
    }
}

void readMatrixFromFile(int *n, double matrix[MAX_SIZE][MAX_SIZE + 1], double matr[MAX_SIZE][MAX_SIZE + 1]) {
    FILE *file;
    char filename[100];
    printf("Введите имя файла: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        exit(1);
    }
    fscanf(file, "%d", n);
    printf("Размер матрицы: %d\n", *n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n + 1; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
            matr[i][j] = matrix[i][j];
        }
    }
    fclose(file);
}

void printMatrix(int n, double matrix[MAX_SIZE][MAX_SIZE + 1]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void gaussMethod(int n, double matrix[MAX_SIZE][MAX_SIZE + 1]) {
    for (int i = 0; i < n - 1; i++) {
        for (int k = i + 1; k < n; k++) {
            for (int k = n - 1; k >= i + 1; k--) {
                double factor = matrix[k][i] / matrix[i][i];
                for (int j = i; j < n + 1; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }
}

void modification(int n, double matrix[MAX_SIZE][MAX_SIZE + 1])
{
    double max = fabs(matrix[0][0]);
    int rowMarker = 0;

    for (int i = 1; i < n; i++) {
        if (fabs(matrix[i][0]) > max) {
            max = fabs(matrix[i][0]);
            rowMarker = i;
        }
        printf("Столбец #%d: Максимальный элемент = %lf\n", i - 1, max);
    }

    if (rowMarker != 0) {
        for (int j = 0; j <= n; j++) {
            double temp = matrix[0][j];
            matrix[0][j] = matrix[rowMarker][j];
            matrix[rowMarker][j] = temp;
        }
    }
}

int main() {
    int choice, n;
    double matrix[MAX_SIZE][MAX_SIZE + 1];
    double matr[MAX_SIZE][MAX_SIZE + 1];

    printf("Выберите способ ввода:\n");
    printf("1. Ввод с клавиатуры\n");
    printf("2. Ввод из файла\n");
    printf("Введите ваш выбор: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Введите размер матрицы: ");
            scanf("%d", &n);
            if (n > MAX_SIZE || n <= 0) {
                printf("Недопустимый размер\n");
                return 1;
            }
            readMatrixFromKeyboard(n, matrix, matr);
            break;
        case 2:
            readMatrixFromFile(&n, matrix, matr);
            break;
        default:
            printf("Неверный выбор\n");
            return 1;
    }

    system("clear");
    printf("=========================================Метод  Гаусса=========================================\n");
    printf("Матрица:\n");
    printMatrix(n, matrix);

    gaussMethod(n, matrix);

    printf("\nПосле применения метода Гаусса:\n");
    printMatrix(n, matrix);

    double x[MAX_SIZE];
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (matrix[i][n] - sum) / matrix[i][i];
    }

    printf("\nРешения системы уравнений:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }

    printf("=================================Модифицированный метод Гаусса=================================\n");

    printf("Матрица:\n");
    printMatrix(n, matr);
    modification(n, matr);
    printf("Матрица:\n");
    printMatrix(n, matr);
    gaussMethod(n, matr);
    printf("Матрица после модифицированного метода гаусса:\n");
    printMatrix(n, matr);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (matrix[i][n] - sum) / matrix[i][i];
    }

    printf("\nРешения системы уравнений:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }

    printf("===============================================================================================\n");

    return 0;
}
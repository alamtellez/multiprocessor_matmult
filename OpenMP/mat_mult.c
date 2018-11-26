/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

#include <stdio.h>
#include <stdlib.h>
#include "../utils/cheader.h"

void matrix_multiplication(int **a, int **b, int **c, int filasA, int columnasB, int n)
{
    int i, j, k, sum = 0;

    #pragma parallel for shared(a, b, c, filasA) private(j, k, sum)
        for (i = 0; i < filasA; i++){
            for (j = 0; j < columnasB; j++){
                sum = 0;
                for (k = 0; k < n; k++)
                {
                    sum += a[i][k] * b[k][j];
                }
                c[i][j] = sum;
            }
        }
}

int main(int argc, char *argv[])
{
    int i, j, k, sum;
    int filasA;
    int columnasA;
    int filasB;
    int columnasB;
    int **a, **b, **c;
    double ms;

    srand(time(0));
    printf("Rows of matrix A: ");
    scanf("%i", &filasA);
    printf("Columns of matrix A: ");
    scanf("%i", &filasB);
    columnasA = filasB;
    printf("Columns of matrix B: ");
    scanf("%i", &columnasB);

    // printf("%i %i %i", filasA, columnasA, columnasB);

    // Allocate matrix A
    a = (int **)malloc(filasA * sizeof(int *));
    for (i = 0; i < filasA; i++)
        a[i] = (int *)malloc(columnasA * sizeof(int));

    // Allocate matrix B
    b = (int **)malloc(filasB * sizeof(int *));
    i = 0;
    for (i = 0; i < filasB; i++)
        b[i] = (int *)malloc(columnasB * sizeof(int));

    // Allocate matrix C
    c = (int **)malloc(filasA * sizeof(int *));
    i = 0;
    for (i = 0; i < filasA; i++)
        c[i] = (int *)malloc(columnasB * sizeof(int));

    // Fill A with random values
    for (i = 0; i < filasA; i++)
        for (j = 0; j < columnasA; j++)
            a[i][j] = (rand() % 100) + 1;
    // Display A
    int m, n;
    // printf("\nMat A\n");
    // for (m = 0; m < filasA; m++)
    // {
    //     for (n = 0; n < columnasA; n++)
    //     {
    //         printf("%i\t", a[m][n]);
    //     }
    //     printf("\n");
    // }
    for (i = 0; i < filasB; i++)
        for (j = 0; j < columnasB; j++)
            b[i][j] = (rand() % 100) + 1;
    // printf("\nMat B\n");
    // for (m = 0; m < filasB; m++)
    // {
    //     for (n = 0; n < columnasB; n++)
    //     {
    //         printf("%i\t", b[m][n]);
    //     }
    //     printf("\n");
    // }
    // ms = 0;
    start_timer();
    matrix_multiplication(a, b, c, filasA, columnasB, columnasA);
    ms = stop_timer();
    // printf("\nMat Res\n");
    // for (m = 0; m < filasA; m++) {
    //     for (n = 0; n < columnasB; n++){
    //         printf("%i\t", c[m][n]);
    //     }
    //     printf("\n");
    // }
    printf("\nTime = %lf\n", ms);
    free(a);
    free(b);
    free(c);
    return 0;
}

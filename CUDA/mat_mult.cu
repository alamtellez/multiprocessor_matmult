/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

#include <stdio.h>
#include "cuda_runtime.h"
#include <stdlib.h>
#include <time.h>
#include "../utils/cheader.h"

#define BLOCK_SIZE 16

__global__ void matMult(int *a, int *b, int *c, int filasA, int columnasB, int k) {
  // This somehow does the job
  float temp = 0;
  int i;
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  // If the tid is greater than the size of the result matrix, return
  if(row > filasA || col > columnasB) return;
  for (i = 0; i < k; ++i)
    temp += (a[row * k + i]) * (b[i * columnasB + col]);
  c[row * columnasB + col] = temp;

}

int main(){
  // Declare variables
  int *a, *b, *c;
  int *dev_a;
  int *dev_b;
  int *dev_c;
  double ms;
  // Columns and rows to use
  int filasA;
  int columnasA;
  int filasB;
  int columnasB;
  // Get values for rows and columns
  printf ("Rows of matrix A: ");
  scanf ("%i",&filasA);
  printf ("Columns of matrix A: ");
  scanf ("%i",&columnasA);
  filasB = columnasA;
  printf ("Columns of matrix B: ");
  scanf ("%i",&columnasB);
  /*
  filasA = 5;
  columnasA = 5;
  filasB = columnasA;
  columnasB = 5;
  */
  // Define sizes to store in both host and device
  int sizeA = filasA * columnasA * sizeof(int);
  int sizeB = filasB * columnasB * sizeof(int);
  int sizeC = filasA * columnasB * sizeof(int);

  // define matrixes
  a = (int*)malloc(sizeA);
  b = (int*)malloc(sizeB);
  c = (int*)malloc(sizeC);
  // Fill matrix A
  for(int i = 0; i < filasA; i++)
    for(int j = 0; j < columnasA; j++)
      a[i*columnasA + j] = (int)((rand() % 100) + 1);
  //Fill matrix B
  for(int i = 0; i < filasB; i++)
    for(int j = 0; j < columnasB; j++)
      b[i*columnasB + j] = (int)((rand() % 100) + 1);
  // Allocate values in device
  cudaMalloc((void**) &dev_a, sizeA);
  cudaMalloc((void**) &dev_b, sizeB);
  cudaMalloc((void**) &dev_c, sizeC);
  // Copy the values from matrix A and B in host to the GPU
  cudaMemcpy(dev_a, a, sizeA, cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, sizeB, cudaMemcpyHostToDevice);
  // Define the grid that is going to have onw thread per matrix location of the result
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
  dim3 dimGrid((columnasB + dimBlock.x - 1) / dimBlock.x, (filasA + dimBlock.y - 1) / dimBlock.y);
  // Call function in GPU
  ms = 0;
  start_timer();
  matMult<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c, filasA, columnasB, columnasA);
  ms = stop_timer();
  // Get the value from GPU to Host so we can print it
  cudaMemcpy(c, dev_c, sizeC, cudaMemcpyDeviceToHost);
  //Print the three matrixes
  printf("Matrix A \n");
  for(int i = 0; i < filasA; i++){
    for(int j = 0; j < columnasA; j++){
      printf("%i ", a[i*columnasA + j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("Matrix B \n");
  for(int i = 0; i < filasB; i++){
    for(int j = 0; j < columnasB; j++){
      printf("%i ", b[i*columnasB + j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("Matrix C (Result) \n");
  for(int i = 0; i < filasA; i++){
    for(int j = 0; j < columnasB; j++){
      printf("%i \t", c[i*columnasB + j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("Time = %lf\n", ms);
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);

  free(a);
  free(b);
  free(c);
}


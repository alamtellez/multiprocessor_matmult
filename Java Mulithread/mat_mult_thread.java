/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

import java.util.Random;
import java.util.Scanner;

class ThreadMatMult
{   
    private static final int MAXTHREADS = Runtime.getRuntime().availableProcessors();
    // Main
    public static void main(String args[])
    {   
        // Variable declaration
        int filasA, columnasA, filasB, columnasB,i,j,k,sum;
        int block;
        long startTime, stopTime;
        double acum = 0;
        Multiplicator[] threads;
        Scanner in = new Scanner(System.in);
        System.out.println(MAXTHREADS);
        // Ask for matrix dimensions
        // Matrix A
        System.out.print("Rows of matrix A: ");
        filasA = in.nextInt();
        // Matrix A and Bs K (similar value)
        System.out.print("Columns of matrix A = rows matrix B: ");
        columnasA = in.nextInt();
        filasB = columnasA;
        // Matrix B
        System.out.print("Columns of matrix B: ");
        columnasB = in.nextInt();
        // Allocate space for matrices
        int matA[][] = new int[filasA][columnasA]; 
        int matB[][] = new int[filasB][columnasB]; 
        int matC[][] = new int[filasA][columnasB];
        threads = new Multiplicator[MAXTHREADS];
        block = matA.length / MAXTHREADS;
        // Fill with random values
        Utils.fillMatrix(matA);
        Utils.fillMatrix(matB);
        // Create threads that go through the matrix
        for (i = 0; i < threads.length; i++) {
            if (i != threads.length - 1) {
                threads[i] = new Multiplicator(matA, matB, matC, (i * block), ((i + 1) * block));
            } else {
                threads[i] = new Multiplicator(matA, matB, matC, (i * block), matA.length);
            }
        }
        // Start Timer
        startTime = System.currentTimeMillis();
        // Run threads
        for (i = 0; i < threads.length; i++) {
            threads[i].start();
        }
        for (i = 0; i < threads.length; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        // Stop Timer
        stopTime = System.currentTimeMillis();
        acum +=  (stopTime - startTime);
        // Utils.displayMatrix(matA, 'A');
        // Utils.displayMatrix(matB, 'B');
        // Utils.displayMatrix(matC, 'C');
        // Print result
        System.out.printf("Time = %f\n", acum/1000);
        System.out.println();
    }
 
}
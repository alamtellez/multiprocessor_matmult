/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

import java.util.Random;
import java.util.Scanner;

class SeqMatMult
{   
    // Main
    public static void main(String args[])
    {   
        // Variable declaration
        int filasA, columnasA, filasB, columnasB,i,j,k,sum;
        long startTime, stopTime;
        double acum = 0;
        Scanner in = new Scanner(System.in);
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
        // Fill with random values
        Utils.fillMatrix(matA);
        Utils.fillMatrix(matB);
        // Start Timer
        startTime = System.currentTimeMillis();
        for ( i= 0 ; i < filasA ; i++ ){
            for ( j= 0 ; j <columnasB;j++){
                sum=0;
                for ( k= 0 ; k <filasB;k++ ){
                    sum +=matA[i][k]*matB[k][j] ;
                }
                matC[i][j]=sum;
            }
        }
        // Stop Timer
        stopTime = System.currentTimeMillis();
        acum +=  (stopTime - startTime);
        // Utils.displayMatrix(matA, 'A');
        // Utils.displayMatrix(matB, 'B');
        // Utils.displayMatrix(matC, 'C');
        // Print result
        System.out.printf("Time = %f\n", (acum/1000));
        System.out.println();
    }
 
}
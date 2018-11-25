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
    public static final int MAX_VALUE = 100;
    public static void fillMatrix(int mat[][]) {
        Random r = new Random();
		for (int i = 0; i < mat.length; i++) {
            for(int j = 0; j< mat[0].length; j++)
			    mat[i][j] = r.nextInt(MAX_VALUE) + 1;
		}
	}
    public static void displayMatrix(int mat[][], char mat_name) {
        System.out.println("Matrix " + mat_name);
		for (int i = 0; i < mat.length; i++) {
            for(int j = 0; j< mat[0].length; j++)
                System.out.print(mat[i][j] + "\t");
            System.out.print("\n");
        }
        System.out.println();
	}
    public static void main(String args[])
    {
        int filasA, columnasA, filasB, columnasB,i,j,k,sum;
        long startTime, stopTime;
        double acum = 0;
        Scanner in = new Scanner(System.in);
        
        System.out.print("Rows of matrix A: ");
        filasA = in.nextInt();
        
        System.out.print("Columns of matrix A = rows matrix B: ");
        columnasA = in.nextInt();
        filasB = columnasA;
        System.out.print("Columns of matrix B: ");
        columnasB = in.nextInt();
        
        int matA[][] = new int[filasA][columnasA]; 
        int matB[][] = new int[filasB][columnasB]; 
        int matC[][] = new int[filasA][columnasB];
        
        fillMatrix(matA);
        fillMatrix(matB);
        startTime = System.currentTimeMillis();
        for ( i= 0 ; i < filasA ; i++ )
            for ( j= 0 ; j <columnasB;j++){
                sum=0;
                for ( k= 0 ; k <filasB;k++ ){
                    sum +=matA[i][k]*matB[k][j] ;
                }
                matC[i][j]=sum;
            }
        stopTime = System.currentTimeMillis();
        acum +=  (stopTime - startTime);
        displayMatrix(matA, 'A');
        displayMatrix(matB, 'B');
        displayMatrix(matC, 'C');
        System.out.printf("Time = %f\n", acum/1000);
        System.out.println();
    }
 
}
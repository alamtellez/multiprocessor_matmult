/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

import java.util.concurrent.ForkJoinPool;
import java.util.Scanner;

class ForkJoinMatMult {
    // Get maximum number of available threads
	private static final int MAXTHREADS = Runtime.getRuntime().availableProcessors();
	
	public static void main(String args[]) {
		ForkJoinPool pool;
		long startTime, stopTime;
		double acum = 0;
		int filasA, columnasA, filasB, columnasB,i,j,k,sum, size;
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
        size = filasA;
        // Fill with random values
        Utils.fillMatrix(matA);
        Utils.fillMatrix(matB);
		
		acum = 0;
        startTime = System.currentTimeMillis();
        
        pool = new ForkJoinPool(MAXTHREADS);
        pool.invoke(new MultiplicatorFJ(matA, matB, matC, 0, matA.length));
        
        stopTime = System.currentTimeMillis();
        acum +=  (stopTime - startTime);
		Utils.displayMatrix(matA, 'A');
        Utils.displayMatrix(matB, 'B');
        Utils.displayMatrix(matC, 'C');
		System.out.printf("Time = %.5f\n", (acum / 1000));
	}
}


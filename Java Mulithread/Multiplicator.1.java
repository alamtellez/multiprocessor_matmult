/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/
public class Multiplicator extends Thread{
    private int[][] matA; 
    private int[][] matB;
    private int[][] matC;
    private int start, end, cols,k, start1, end1;
    
    public Multiplicator(int[][] A, int[][] B, int[][] C, int start, int end, int start1, int end1){
        this.matA = A;
        this.matB = B;
        this.matC = C;
        this.start = start;
        this.end = end;
        this.start1 = start1;
        this.end1 = end1;
        this.cols = this.matB[0].length;
        this.k = this.matA[0].length;
    }
    public void run(){
        int sum = 0;
        System.out.println(start + " " + end + " " + start1 + " " + end1 + " ");
        for(int i = start; i < end; i++){
            for(int j=start1; j < end1; j++){
                sum = 0;
                for(int n = 0; n < k; n++){
                    sum += matA[i][n] * matB[n][j];
                }
                matC[i][j] = sum;
            }
        }
    }
}

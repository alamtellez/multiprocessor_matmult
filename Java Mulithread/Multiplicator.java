public class Multiplicator extends Thread{
    private int[][] matA; 
    private int[][] matB;
    private int[][] matC;
    private int start, end, cols,k;
    
    public Multiplicator(int[][] A, int[][] B, int[][] C, int start, int end){
        this.matA = A;
        this.matB = B;
        this.matC = C;
        this.start = start;
        this.end = end;
        this.cols = this.matB[0].length;
        this.k = this.matA[0].length;
    }
    public void run(){
        int sum = 0;
        for(int i = start; i < end; i++){
            for(int j=0; j < cols; j++){
                sum = 0;
                for(int n = 0; n < k; n++){
                    sum += matA[i][n] * matB[n][j];
                }
                matC[i][j] = sum;
            }
        }
    }
}

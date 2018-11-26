/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

import java.util.concurrent.RecursiveAction;

public class MultiplicatorFJ extends RecursiveAction {
	private static final long MIN = 100;
	private int[][] a; 
    private int[][] b;
    private int[][] c;
    private int start, end, cols,k;
	
	public MultiplicatorFJ(int[][] a, int[][] b, int[][] c, int start, int end) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.start = start;
        this.end = end;
        this.cols = b[0].length;
        this.k = a[0].length;
	}
	
	protected void computeDirectly() {
        int sum = 0;
		for(int i = this.start; i < this.end; i++){
            for(int j=0; j < cols; j++){
                sum = 0;
                for(int n = 0; n < k; n++){
                    sum += a[i][n] * b[n][j];
                }
                c[i][j] = sum;
            }
        }
	}
	
	@Override
	protected void compute() {
		if ( (this.end - this.start) <= MultiplicatorFJ.MIN ) {
			computeDirectly();
			
		} else {
			int middle = (end + start) / 2;
			
			invokeAll(new MultiplicatorFJ(a, b, c, start, middle), 
					  new MultiplicatorFJ(a, b, c, middle, end));
		}
		
	}
}
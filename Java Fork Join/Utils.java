import java.util.Random;

public class Utils {
	private static final int MAX_VALUE = 100;
	private static final Random r = new Random();
	public static final int N = 10;
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
}
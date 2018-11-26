/*
    *   Arturo Alam Tellez Villagomez
    *   A01205569
    *   Matrix Multiplication
    *   Multiprocessors
    *   Final Project
*/

#include <iostream>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "../utils/cppheader.h"

using namespace std;
using namespace tbb;
const int GRAIN = 10;


class MatrixMultiplication {
private:
	int **array_a, **array_b, **array_c;
    int cols, k;
	
public:
	MatrixMultiplication( int **a, int **b,int **c, int cols, int k) : array_a(a), array_b(b), array_c(c),cols(cols), k(k) {}
	
	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
            for(int j = 0; j < cols; j++){
                for(int n =0; n < k; n++){
                    array_c[i][j] += array_a[i][n] * array_b[n][j];
                }
            }
		}
	}
};

int main()
{   

Timer t;
	double ms;
    int i, j;
    int filasA;
    int columnasA;
    int filasB;
    int columnasB;
    int **a, **b, **c;

    cout << "Rows of matrix A: ";
    cin >> filasA;
    cout << "Columns of matrix A = rows B: ";
    cin >> columnasA;
    filasB = columnasA;
    cout << "Columns of matrix B: ";
    cin >> columnasB;


	a = new int*[filasA];
    for(i = 0; i < filasA; ++i)
        a[i] = new int[columnasA];
	for (i = 0; i < filasA; i++)
        for (j = 0; j < columnasA; j++)
            a[i][j] = (rand() % 100) + 1;
	// display_matrix("Matrix A:", a, filasA, columnasA);
	
	b = new int*[filasB];
    for(i = 0; i < filasB; ++i)
        b[i] = new int[columnasB];
	for (i = 0; i < filasB; i++)
        for (j = 0; j < columnasB; j++)
            b[i][j] = (rand() % 100) + 1;
	// display_matrix("Matrix B:", b, filasB, columnasB);
	
	c = new int*[filasA];
    for(int i = 0; i < filasA; ++i)
        c[i] = new int[columnasB];
	
	cout << "Starting...\n";
	ms = 0;
    t.start();
    parallel_for( blocked_range<int>(0, filasA, GRAIN), MatrixMultiplication(a, b, c, columnasB, columnasA) );
    ms += t.stop();
	// display_matrix("Matrix C: ", c, filasA, columnasB);
	cout << "Time = " << (ms/1000) << " s\n";
	
	delete [] a;
    delete [] b;
    delete [] c;
	return 0;
}
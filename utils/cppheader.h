#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>

const int N = 10;
const int DISPLAY = 100;
const int MAX_VALUE = 10000;

class Timer {
private:
    timeval startTime;
    bool 	started;

public:
    Timer() :started(false) {}

    void start(){
    	started = true;
        gettimeofday(&startTime, NULL);
    }

    double stop(){
        timeval endTime;
        long seconds, useconds;
        double duration = -1;

        if (started) {
			gettimeofday(&endTime, NULL);

			seconds  = endTime.tv_sec  - startTime.tv_sec;
			useconds = endTime.tv_usec - startTime.tv_usec;

			duration = (seconds * 1000.0) + (useconds / 1000.0);
			started = false;
        }
		return duration;
    }
};

void display_matrix(const char *text, int **mat, int rows, int cols) {
	int i, j;

	printf("%s \n", text);
	for (i = 0; i < rows; i++) {
		for(j=0; j < cols; j++)
			printf("%i\t", mat[i][j]);
        printf("\n");
	}
}

#endif

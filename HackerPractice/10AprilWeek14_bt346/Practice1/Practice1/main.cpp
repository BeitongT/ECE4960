/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      One dimensinal parabolic PDE 
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Apr. 24
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/


#include <iostream>
#include <stdio.h>
#include <math.h>
#include "matrix.hpp"
#include <algorithm>
#include <cstdio>
#include <ctime>

using namespace std;

double solver(double x,double t) {
    double before = t - M_PI / 16.0;
    double after = t + M_PI / 16.0;
    
    if (x <= t && x > before) {
        return (x - before) / (t - before)*sin(t);
    }
    else if (x > t && x <= after && t < M_PI / 2.0) return (after - x) / (after - t)*sin(t);
    else return 0;
}

double calArea() {
    double result = 0.0;
    for (double p = 0.0; p <= 8.0; p+=1.0) {
        double solverParameter = p * M_PI / 16.0;
        double temp = 0.0;
        if(p != 8.0) {
            temp = sin(solverParameter) * M_PI / 16.0;
        }
        else {
            temp = sin(solverParameter) * M_PI / 32.0;
        }
        result += temp;
    }
    return result;
}


int main(int argc, const char * argv[]) {
    double start = 0.0;
    double end = M_PI / 2.0;
    double step = M_PI / 2.0 / 100.0;

    for (double i = start; i < end; i+= step) {
        double result = 0.0;
        for (double p = 1.0; p <= 8.0; p+=1.0) {
            double solverParameter = p * M_PI / 16.0;
            result += solver(i, solverParameter);
        }
        printf("%.5f\n",result);

    }
    
    printf("the error is %f %%\n", (1 - calArea()) * 100);
    return 0;
}



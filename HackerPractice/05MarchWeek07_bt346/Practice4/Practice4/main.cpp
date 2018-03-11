/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week7 class on Thursday.
 *      Use Newton method to solve the nonlinear equation.
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Mar. 8
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <stdio.h>

using namespace std;


double　cal_f(double x) {
    return exp(50*x) - 1;
}

double　cal_f_slope(double x) {
    return 50*exp(50*x);
}

int main(int argc, const char * argv[]) {
    double x = 1;
    int i = 0;
    printf("X(0) = 1\n");
    while(abs(cal_f(x))>1e-10) {
        printf("K       = %d \n",i++);
        printf("X       = %.20f \n",x);
        double temp = - cal_f(x)/cal_f_slope(x);
        printf("Delta X = %.20f \n",temp);
        printf("FUNCT X = %.20f \n",cal_f(x));
        printf("\n");
        x = x + temp;
    }
    
    x = 10;
    i = 0;
    printf("X(0) = 10\n");
    while(abs(cal_f(x))>1e-10) {
        printf("K       = %d \n",i++);
        printf("X       = %.20f \n",x);
        double temp = - cal_f(x)/cal_f_slope(x);
        printf("Delta X = %.20f \n",temp);
        printf("FUNCT X = %.20f \n",cal_f(x));
        printf("\n");
        x = x + temp;
    }
    
    return 0;
}



/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week9 class on Tuessday.
 *       Use the quasi-Newton method with line search to solve the same nonlinear
 *       equation by making x(0) = 1 and the local analysis of the Jacobian matrix
 *        by 10-4 perturbation。
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Mar. 23
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

//cal f(x)
double cal_f(double x) {
    return exp(100*x) - 1;
}

//cal f(1.0001x)
double cal_f_plus(double x) {
    return exp(100*x*1.0001) - 1;
}

//cal ||f(x)||
double cal_f_abs(double x) {
    return abs(exp(100*x) - 1);
}

//line search
double find_minimum(double Xnow,double Xnext) {
    int range_l = -5;
    int range_r = 5;
    int range_m = 0;
    
    double scaler_m = pow(2,range_m);
    double scaler_l = pow(2,range_l);
    double scaler_r = pow(2,range_r);
    
    double left = 0;
    double right = 0;
    double middle = 0;
    
    middle = cal_f_abs(Xnow + Xnext*scaler_m);
    left = cal_f_abs(Xnow + Xnext*scaler_l);
    right = cal_f_abs(Xnow + Xnext*scaler_r);
    
    int count = 0;
    
    while (count < 5) {
        //        cout << scaler_m <<endl;
        if(left < middle) {
            scaler_r = scaler_m;
            range_r = range_m;
            range_m = (range_l + range_m)/2;
            
            scaler_m = pow(2,range_m);
            middle = cal_f_abs(Xnow + Xnext*scaler_m);
            right = cal_f_abs(Xnow + Xnext*scaler_r);
        }
        else {
            scaler_l = scaler_m;
            range_l = range_m;
            range_m = (range_r + range_m)/2;
            scaler_m = pow(2,range_m);
            middle = cal_f_abs(Xnow + Xnext*scaler_m);
            left = cal_f_abs(Xnow + Xnext*scaler_l);
        }
        count ++;
    }
    
    return scaler_m;
}

int main(int argc, const char * argv[]) {
    double x = 1;
    int i = 0;
    printf("X(0) = 10\n");
    while(abs(cal_f(x))>1e-10) {
        printf("K       = %d \n",i++);
        printf("X_K     = %.20f \n",x);
        double temp = - cal_f(x)/(cal_f_plus(x) - cal_f(x))*0.0001*x;
        double scalar = find_minimum(x,temp);
        temp = temp * scalar;
        printf("Delta X   = %.20f \n",temp);
        printf("FUNCT X = %.20f \n",cal_f(x));
        printf("\n");
        x = x + temp;
    }
    
    return 0;
}



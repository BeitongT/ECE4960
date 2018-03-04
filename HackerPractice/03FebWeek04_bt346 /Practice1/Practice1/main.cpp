/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week4 class on Tuesday.
 *      This is to observe different methods to approximate the integration result.
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 FEB. 15
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
FILE * pFile1;

int main(int argc, const char * argv[]) {
    pFile1 = fopen ("output.txt","w");
    
    
    double ground_truth = 2.3504;
    double result1 = 0;
    double h = 0.01;
    for (double i = -1.0; i < 1; i+=0.01) {
        result1 += exp(i) * h;
    }
    fprintf(pFile1,"this result for rectangle is: %f\n",result1);
    fprintf(pFile1,"the relative error is       : %.10f%%\n",(result1 - ground_truth)/ground_truth * 100);
    
    double result2 = 0;
    for (double i = -1.0; i < 1; i+=0.01) {
        //        fprintf(pFile1,"this i: %f\n",i);
        
        result2 += (exp(i) + exp(i + 0.01)) / 2 * h;
    }
    fprintf(pFile1,"this result for trapezoid is: %f\n",result2);
    fprintf(pFile1,"the relative error is       : %.10f%%\n",(result2 - ground_truth)/ground_truth * 100);
    
    double result3 = 0;
    for (double i = -1.0; i < 1; i+=0.01) {
        //        fprintf(pFile1,"this i: %f\n",i);
        
        result3 += (exp(i + 0.005))  * h;
    }
    fprintf(pFile1,"this result for mid point is: %f\n",result3);
    fprintf(pFile1,"the relative error is       : %.10f%%\n",(result3 - ground_truth)/ground_truth * 100);
    
    double result4 = 0;
    for (double i = -1.0; i < 1; i+=0.01) {
        //        fprintf(pFile1,"this i: %f\n",i);
        
        result4 += (1.0/6.0 * exp(i) + 4.0/6.0 * exp(i + 0.005) + 1.0/6.0 * exp(i + 0.01))  * h;
        
    }
    fprintf(pFile1,"this result for simpson is: %f\n",result4);
    fprintf(pFile1,"the relative error is       : %.10f%%\n",(result4 - ground_truth)/ground_truth * 100);
    
    
    double result5 = 0;
    for (double i = -1.0; i < 1; i+=0.01) {
        //        fprintf(pFile1,"this i: %f\n",i);
        
        result5 += (1.0/2.0 * exp(i + 0.005 - 1.0/2.0/sqrt(3.0) * h) + 1.0/2.0 * exp(i + 0.005 + 1.0/2.0/sqrt(3.0) * h) )  * h;
        
    }
    fprintf(pFile1,"this result for 2 point Gaussian is: %f\n",result5);
    fprintf(pFile1,"the relative error is       : %.10f%%\n",(result5 - ground_truth)/ground_truth * 100);
    
    fclose (pFile1);
    return 0;
}



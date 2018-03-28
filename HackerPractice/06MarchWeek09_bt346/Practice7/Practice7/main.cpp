/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION : Friday Class
 *       Use the quasi-Newton method with line search to solve the nonlinear optimization
 *       function V by making x(0) = (0,0) and the local analysis of the Hessian matrix by 10-4 perturbation.
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
#include <ctime>

using namespace std;

int main(int argc, const char * argv[]) {

    srand((unsigned)time(0));
    for (int p = 10; p<= 1e6; p*=10) {
        int count = 0;
        for (int i = 0; i < p; i++) {
            
            double x = rand() / double(RAND_MAX);
            double y = rand() / double(RAND_MAX);
            
            if((x * x + y * y) < 1) {
                count ++;
            }
        }
        double PI = double(4.0*count / (double)p);
//        printf("Your N is %d\n",p);
//        printf("Your Pi is %.20f\n",PI);
        printf("N = %10d, RESULT = %.20f\n",p, PI);
    }
    
    
    return 0;
}




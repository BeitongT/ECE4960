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
    double vArray[1000] = {0};
    double fArray[1000] = {0};
    int count = 0;
    for (int i = 0 ; i < 1000 ; i ++) {
        double x = rand() / double(RAND_MAX);
        double v = -1 / 0.2 * log(1-x);
        double F = 1-exp(-0.2 * v);

        if (v >=0 && v <=10) {
            vArray[count] = v;
            fArray[count] = F;
            count ++;
        }
    }
    
    //print v
    printf("The count is %d\n", count);

    printf("The results for v\n");
    for (int i = 0; i < count ; i++) {
        printf("%.10f\n",vArray[i]);
    }
    
    printf("\n");
    
    printf("The results for F\n");

    for (int i = 0; i < count ; i++) {
        printf("%.10f\n",fArray[i]);
    }
    

    
    
    return 0;
}





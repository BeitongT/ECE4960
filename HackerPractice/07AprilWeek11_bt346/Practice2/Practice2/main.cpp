/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      Huen's method
 *
 * AUTHOR :   Beitong Tian        START DATE :    10 Apr. 20
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


#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <stdio.h>

using namespace std;

double calGroundTruth(double t) {
    return 4.0 / 1.3 * (exp(0.8 * t) - exp(-0.5 * t)) + 2 * exp(-0.5 * t);
}

double calFowardEuler(double t,double deltaT, double last) {
    return (4 * exp(0.8 * t) - 0.5 * last) * deltaT + last;
}

double calTrapezoidal(double t,double deltaT, double last) {
    double next = calFowardEuler(t, deltaT, last);
    return last + deltaT / 2 * ((4 * exp(0.8 * t) - 0.5 * last) + (4 * exp(0.8 * (t + deltaT)) - 0.5 * next)) ;
}
bool isLowerThanTol(double xnow, double xnext) {
    double tol = 1e-7;
    return abs((xnow - xnext) / xnext) < tol;
}

double calXHuen(double t,double deltaT, double last) {
    double resultNow = calFowardEuler(t, deltaT, last);
    double resultNext =  last + deltaT / 2 * ((4 * exp(0.8 * t) - 0.5 * last) + (4 * exp(0.8 * (t + deltaT)) - 0.5 * resultNow)) ;
    while ( !isLowerThanTol(resultNext, resultNow)) {
        resultNow = resultNext;
        resultNext = last + deltaT / 2 * ((4 * exp(0.8 * t) - 0.5 * last) + (4 * exp(0.8 * (t + deltaT)) - 0.5 * resultNow)) ;
    }
    return resultNext;
}

double calError(double truth, double simulation) {
    return abs((truth - simulation)/ truth) * 100;
}


int main(int argc, const char * argv[]) {
    double deltaT = 1;
    double groundTruth = 2;
    double lastFowardEuler = 2;
    double lastTrapezoidal = 2;
    double lastXHuen = 2;

    double errorFowardEuler = 0;
    double errorTrapezodial = 0;
    double errorXHuen = 0;

    printf("deltaT = %f \n", deltaT);
    printf("t          groundTruth          FowardEuler             errorBackEuler              Trapezodial           errorTrapezodial              XHuen             errorXhuen\n");
    
    printf("%3.1f           %3.5f                %3.5f                %3.5f                %3.5f                %3.5f\n",0.0,2.0,2.0,0.0,2.0,0.0,2.0,0.0);
    for (double i = 0; i < 4; i+=deltaT) {
        lastFowardEuler = calFowardEuler(i, deltaT, lastFowardEuler);
        lastTrapezoidal = calTrapezoidal(i, deltaT, lastTrapezoidal);
        lastXHuen = calXHuen(i, deltaT, lastXHuen);
        
        groundTruth = calGroundTruth(i + deltaT);
        
        errorFowardEuler = calError(groundTruth, lastFowardEuler);
        errorTrapezodial = calError(groundTruth, lastTrapezoidal);
        errorXHuen = calError(groundTruth, lastXHuen);
        printf("%3.1f           %3.5f                %3.5f                %3.5f                %3.5f                %3.5f               %3.5f                   %3.5f\n",i,groundTruth,lastFowardEuler,errorFowardEuler,lastTrapezoidal,errorTrapezodial,lastXHuen,errorXHuen);
    }
    
    cout << endl;
    
    
    
    return 0;
}





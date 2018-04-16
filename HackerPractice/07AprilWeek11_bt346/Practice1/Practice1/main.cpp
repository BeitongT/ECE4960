/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      Observe backward euler and trapezoidal euler
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

double calGroundTruth(double t) {
    return exp(-t);
}

double calBackEuler(double t,double deltaT, double last) {
    return 1.0 / (1.0 + deltaT) * last;
}

double calTrapezoidal(double t,double deltaT, double last) {
    return (2.0 - deltaT) / (2.0 + deltaT) * last;
}

double calError(double truth, double simulation) {
    return abs(truth - simulation);
}


int main(int argc, const char * argv[]) {
    double deltaT = 0.5;
    double groundTruth = 1;
    double lastBackEuler = 1;
    double lastTrapezoidal = 1;
    double errorBackEuler = 0;
    double errorTrapezodial = 0;

    printf("deltaT = %f \n", deltaT);
    printf("t          groundTruth        BackEuler         errorBackEuler          Trapezoidal           errorTrapezodial\n");

    printf("%3.1f           %.5f                %.5f                %.5f                %.5f                %.5f\n",0.0,1.0,1.0,0.0,1.0,0.0);
    for (double i = 0; i <= 20; i+=deltaT) {
        lastBackEuler = calBackEuler(i, deltaT, lastBackEuler);
        lastTrapezoidal = calTrapezoidal(i, deltaT, lastTrapezoidal);
        groundTruth = calGroundTruth(i + deltaT);
        errorBackEuler = calError(groundTruth, lastBackEuler);
        errorTrapezodial = calError(groundTruth, lastTrapezoidal);
        printf("%3.1f           %.5f                %.5f                %.5f                %.5f                %.5f\n",i,groundTruth,lastBackEuler,errorBackEuler,lastTrapezoidal,errorTrapezodial);
    }
    
    cout << endl;
    
    deltaT = 1;
    groundTruth = 1;
    lastBackEuler = 1;
    lastTrapezoidal = 1;
    errorBackEuler = 0;
    errorTrapezodial = 0;
    printf("deltaT = %f \n", deltaT);
    printf("t          groundTruth        BackEuler         errorBackEuler          Trapezoidal           errorTrapezodial\n");
    
    printf("%3.1f           %.5f                %.5f                %.5f                %.5f                %.5f\n",0.0,1.0,1.0,0.0,1.0,0.0);
    for (double i = 0; i <= 20; i+=deltaT) {
        lastBackEuler = calBackEuler(i, deltaT, lastBackEuler);
        lastTrapezoidal = calTrapezoidal(i, deltaT, lastTrapezoidal);
        groundTruth = calGroundTruth(i + deltaT);
        errorBackEuler = calError(groundTruth, lastBackEuler);
        errorTrapezodial = calError(groundTruth, lastTrapezoidal);
        printf("%3.1f           %.5f                %.5f                %.5f                %.5f                %.5f\n",i,groundTruth,lastBackEuler,errorBackEuler,lastTrapezoidal,errorTrapezodial);
    }
    
    
    
    return 0;
}



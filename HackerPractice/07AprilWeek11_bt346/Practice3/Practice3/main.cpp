/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      RK4 method
 *
 * AUTHOR :   Beitong Tian        START DATE :    12 Apr. 20
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

double calK1(double t,double deltaT, double last) {
    return 4 * exp(0.8 * t) - 0.5 * last;
}


double calK2(double t,double deltaT, double last) {
    double K1 = calK1(t,deltaT, last);
    double halfDeltaT = deltaT / 2;
    return 4 * exp(0.8 * (t + halfDeltaT)) - 0.5 * (last + K1 * halfDeltaT);
}

double calK3(double t,double deltaT, double last) {
    double K2 = calK2(t,deltaT, last);
    double halfDeltaT = deltaT / 2;
    return 4 * exp(0.8 * (t + halfDeltaT)) - 0.5 * (last + K2 * halfDeltaT);
}

double calK4(double t,double deltaT, double last) {
    double K3 = calK3(t,deltaT, last);
    return 4 * exp(0.8 * (t + deltaT)) - 0.5 * (last + K3 * deltaT);
}


double calError(double truth, double simulation) {
    return abs((truth - simulation)/ truth) * 100;
}

double calNext(double K1, double K2, double K3, double K4, double last, double deltaT) {
    return last + 1.0 / 6.0 * deltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
}


int main(int argc, const char * argv[]) {
    double deltaT = 1;
    double RK4last = 2;
    double groundTruth = 2;
    double K1 = 0;
    double K2 = 0;
    double K3 = 0;
    double K4 = 0;

    double errorRK4 = 0;

    
    printf("deltaT = %f \n", deltaT);
    printf("t          groundTruth          K1             K2              K3           K4              XRK4             error\n");
    
//    printf("%3.1f           %3.5f                %3.5f                %3.5f                %3.5f                %3.5f\n",0.0,2.0,2.0,0.0,2.0,0.0,2.0,0.0);
    for (double i = 0; i < 5; i+=deltaT) {
        
        groundTruth = calGroundTruth(i + deltaT);
        K1 = calK1(i, deltaT, RK4last);
        K2 = calK2(i, deltaT, RK4last);
        K3 = calK3(i, deltaT, RK4last);
        K4 = calK4(i, deltaT, RK4last);
        

        
        RK4last = calNext(K1, K2, K3, K4, RK4last, deltaT);
        errorRK4 = calError(groundTruth, RK4last);
        printf("%3.1f           %3.5f            %3.5f            %3.5f            %3.5f            %3.5f           %3.5f                   %3.5f\n",i,groundTruth,K1,K2,K3,K4,RK4last,errorRK4);
    }
    
    cout << endl;
    
    
    
    return 0;
}





//
//  ForwardEuler.cpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "ForwardEuler.hpp"

/* forwardEuler Method */

//forwardEulerTest  => solution vector rank = 1
void forwardEuler_Test(double t,double deltaT,double last) {
    double time = 0.0;
    double truth = last;
    printf("forwardEuler_Test\n");
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,1.0,truth,0.0);
    
    while(time < t) {
        double result = (4 * exp(0.8 * time) - 0.5 * last) * deltaT + last;
        last = result;
        time += deltaT;
        truth = groundTruth_Test(time);
        printf("%-15.5f%-15.5f%-15.5f%.5f%%\n", time,result,truth, calError_test(truth,result));
    }
    printf("\n");
}

//forwardEulerRC  => solution vector rank = 2

void forwardEulerRC(double t,double deltaT,Vector2d last) {
    
    double time = 0.0;
    printf("forwardEulerRC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    double RC = 1.0e4 * 1.0e-12;
    
    while(time < t) {
        Vector2d result;
        result(0) = last(0) + (-1.0 *  (1.0 / RC + 1.0 / RC) * last(0) + 1.0 / RC * last(1) + currentHelper(time) / 1.0e-12) * deltaT;
        result(1) = last(1) + (1.0 / RC * last(0) - (1.0 / RC + 1.0 / RC) * last(1)) * deltaT;
        last = result;
        time += deltaT;
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}


//forwardEulerEKV  => solution vector rank = 2

void forwardEulerEKV(double t,double deltaT,Vector2d last) {
    
    double time = 0.0;
    printf("forwardEulerEKV      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    double RC = 1.0e4 * 1.0e-12;
    double Vdd = 5.0;
    while(time < t) {
        Vector2d result;
        result(0) = last(0) + (-1.0 / RC * last(0) + currentHelper(time) / 1e-12) * deltaT;
        result(1) = last(1) + (-currentHelperEKV(last(0), last(1))/1e-12 - 1.0/RC * last(1) + Vdd / RC) * deltaT;
        last = result;
        time += deltaT;
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}

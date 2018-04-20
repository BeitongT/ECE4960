//
//  RK4.cpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "RK4.hpp"

/* RK34 with out time adaption Method => RK4 method */

//RK4_test  => solution vector rank = 1
void RK4_test(double t, double deltaT, double last) {
    double time = 0.0;
    double truth = last;
    
    printf("RK4_test\n");
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,truth,truth,0.0);
    
    while(time < t) {
        double halfDeltaT = deltaT / 2;
        
        double time1 = time;
        double x1 = last;
        double K1 = 4 * exp(0.8 * time1) - 0.5 * x1;

        double time2 = time + halfDeltaT;
        double x2 = last + K1 * halfDeltaT;
        double K2 = 4 * exp(0.8 * time2) - 0.5 * x2;

        double time3 = time + halfDeltaT;
        double x3 = last + K2 * halfDeltaT;
        double K3 = 4 * exp(0.8 * time3) - 0.5 * x3;

        double time4 = time + deltaT;
        double x4 = last + K3 * deltaT;
        double K4 = 4 * exp(0.8 * time4) - 0.5 * x4;

        double result = last + 1.0 / 6.0 * deltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
        
        last = result;
        time += deltaT;
        truth = groundTruth_Test(time);
        printf("%-15.5f%-15.5f%-15.5f%.5f%%\n", time,result,truth, calError_test(truth,result));
        
    }
    printf("\n");
}

//RK4_RC  => solution vector rank = 2

void RK4_RC(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    
    printf("RK4_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    
    while(time < t) {
        
        double halfDeltaT = deltaT / 2;
        double time1 = time;
        double time2 = time + halfDeltaT;
        double time3 = time + halfDeltaT;
        double time4 = time + deltaT;
        
        Vector2d K1;
        Vector2d x1;
        x1(0) = last(0);
        x1(1) = last(1);
        K1(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x1(0) + 1.0 / RC * x1(1) + currentHelper(time1) / C);
        K1(1) = (1.0 / RC * x1(0) - (1.0 / RC + 1.0 / RC) * x1(1));
        
        Vector2d K2;
        Vector2d x2;
        x2(0) = last(0) + K1(0)*halfDeltaT;
        x2(1) = last(1) + K1(1)*halfDeltaT;
        K2(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x2(0) + 1.0 / RC * x2(1) + currentHelper(time2) / C);
        K2(1) = (1.0 / RC * x2(0) - (1.0 / RC + 1.0 / RC) * x2(1));
        
        Vector2d K3;
        Vector2d x3;
        x3(0) = last(0) + K2(0)*halfDeltaT;
        x3(1) = last(1) + K2(1)*halfDeltaT;
        K3(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x3(0) + 1.0 / RC * x3(1) + currentHelper(time3) / C);
        K3(1) = (1.0 / RC * x3(0) - (1.0 / RC + 1.0 / RC) * x3(1));
        
        Vector2d K4;
        Vector2d x4;
        x4(0) = last(0) + K3(0)*deltaT;
        x4(1) = last(1) + K3(1)*deltaT;
        K4(0)= (-1.0 *  (1.0 / RC + 1.0 / RC) * x4(0) + 1.0 / RC * x4(1) + currentHelper(time4) / C);
        K4(1) = (1.0 / RC * x4(0) - (1.0 / RC + 1.0 / RC) * x4(1));
        
        Vector2d result;
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        last = result;
        time += deltaT;
        
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}


//RK4_EKV  => solution vector rank = 2


void RK4_EKV(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    printf("RK4_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    double Vdd = 5.0;
    while(time < t) {
        double halfDeltaT = deltaT / 2;
        double time1 = time;
        double time2 = time + halfDeltaT;
        double time3 = time + halfDeltaT;
        double time4 = time + deltaT;
        
        Vector2d K1;
        Vector2d x1;
        x1(0) = last(0);
        x1(1) = last(1);
        K1(0) = (-1.0 / RC * last(0) + currentHelper(time1) / C);
        K1(1) = (-currentHelperEKV(x1(0), x1(1)) / 1e-12 - 1.0 / RC * x1(1) + Vdd / RC);
        
        Vector2d K2;
        Vector2d x2;
        x2(0) = last(0) + K1(0)*halfDeltaT;
        x2(1) = last(1) + K1(1)*halfDeltaT;
        K2(0) = (-1.0 / RC * x2(0) + currentHelper(time2) / C);
        K2(1) = (-currentHelperEKV(x2(0), x2(1)) / C - 1.0 / RC * x2(1) + Vdd / RC);
        
        
        Vector2d K3;
        Vector2d x3;
        x3(0) = last(0) + K2(0)*halfDeltaT;
        x3(1) = last(1) + K2(1)*halfDeltaT;
        K3(0) = (-1.0 / RC * x3(0) + currentHelper(time3) / C);
        K3(1) = (-currentHelperEKV(x3(0), x3(1)) / C - 1.0 / RC * x3(1) + Vdd / RC);
        
        Vector2d K4;
        Vector2d x4;
        x4(0) = last(0) + K3(0)*deltaT;
        x4(1) = last(1) + K3(1)*deltaT;
        K4(0) = (-1.0 / RC * x4(0) + currentHelper(time4) / C);
        K4(1) = (-currentHelperEKV(x4(0), x4(1)) / C - 1.0 / RC * x4(1) + Vdd / RC);
        
        Vector2d result;
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        last = result;
        time += deltaT;
        
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}




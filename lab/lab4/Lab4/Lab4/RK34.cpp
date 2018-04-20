//
//  RK34.cpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "RK34.hpp"
/* RK34 with time adaption Method => RK4 method */
//RK34_test  => solution vector rank = 1
/*  t end time
 deltaT initial deltaT
 last initial value */

void RK34_test(double t, double deltaT, double last) {
    double time = 0.0;
    double Er = 1e-4;
    double Ea = 1e-7;
    double deltaTZero = deltaT;
    double timerequirement = time + deltaTZero;
    double truth = last;
    
    printf("RK34_test\n");
    printf("%-15s%-15s%-15s%-15s%-15s\n", "Time", "Step", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,0.0,truth,truth,0.0);
    
    double halfDeltaT, tempDeltaT, temphalfDeltaT;
    double time1, time2, time3, time4;
    double K1, K2, K3, K4;
    double x1, x2, x3, x4;
    double result, error;
    
    while (time < t) {
        
        if(time + deltaT > timerequirement) {
            tempDeltaT = timerequirement - time;
            temphalfDeltaT = tempDeltaT / 2;
            
            time1 = time;
            x1 = last;
            K1 = 4 * exp(0.8 * time1) - 0.5 * x1;
            
            time2 = time + temphalfDeltaT;
            x2 = last + K1 * temphalfDeltaT;
            K2 = 4 * exp(0.8 * time2) - 0.5 * x2;
            
            time3 = time + temphalfDeltaT;
            x3 = last + K2 * temphalfDeltaT;
            K3 = 4 * exp(0.8 * time3) - 0.5 * x3;
            
            time4 = time + tempDeltaT;
            x4 = last + K3 * tempDeltaT;
            K4 = 4 * exp(0.8 * time4) - 0.5 * x4;
            
            result = last + 1.0 / 6.0 * tempDeltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
            
            truth = groundTruth_Test(timerequirement);
            printf("%-15.5f%-15.5f%-15.5f%-15.5f%.5f%%\n", timerequirement, deltaT, result, truth, calError_test(truth,result));
            timerequirement += deltaTZero;
        }
        
        halfDeltaT = deltaT / 2;
        
        time1 = time;
        x1 = last;
        K1 = 4 * exp(0.8 * time1) - 0.5 * x1;
        
        time2 = time + halfDeltaT;
        x2 = last + K1 * halfDeltaT;
        K2 = 4 * exp(0.8 * time2) - 0.5 * x2;
        
        time3 = time + halfDeltaT;
        x3 = last + K2 * halfDeltaT;
        K3 = 4 * exp(0.8 * time3) - 0.5 * x3;
        
        time4 = time + deltaT;
        x4 = last + K3 * deltaT;
        K4 = 4 * exp(0.8 * time4) - 0.5 * x4;
        
        result = last + 1.0 / 6.0 * deltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
        
        error = 1.0 / 72.0 * (-5.0 * K1 + 6.0 * K2 + 8.0 * K3 - 9.0 * K4) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (abs(error) / (abs(result) + Ea))), 1.0/3);
        last = result;
        
        if(time == timerequirement) {
            truth = groundTruth_Test(timerequirement);
            printf("%-15.5f%-15.5f%-15.5f%-15.5f%.5f%%\n", timerequirement, deltaT, result, truth, calError_test(truth,result));
            timerequirement += deltaTZero;
        }
    }
    printf("\n");
    
}


void RK34_RC(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    double Er = 1e-6;
    double Ea = 1e-9;
    double deltaTZero = deltaT;
    double timerequirement = time + deltaTZero;
    printf("RK34_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Step","V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f%-15.5f\n",0.0,deltaT*1e9,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    
    double halfDeltaT, tempDeltaT, temphalfDeltaT;
    double time1, time2, time3, time4;
    Vector2d K1, K2, K3, K4;
    Vector2d x1, x2, x3, x4;
    Vector2d result, error;
    
    while (time < t) {
        
        if(time + deltaT > timerequirement) {
            
            tempDeltaT = timerequirement - time;
            temphalfDeltaT = tempDeltaT / 2;
            
            time1 = time;
            time2 = time + temphalfDeltaT;
            time3 = time + temphalfDeltaT;
            time4 = time + tempDeltaT;
            
            x1(0) = last(0);
            x1(1) = last(1);
            K1(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x1(0) + 1.0 / RC * x1(1) + currentHelper(time1) / C);
            K1(1) = (1.0 / RC * x1(0) - (1.0 / RC + 1.0 / RC) * x1(1));

            x2(0) = last(0) + K1(0)*temphalfDeltaT;
            x2(1) = last(1) + K1(1)*temphalfDeltaT;
            K2(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x2(0) + 1.0 / RC * x2(1) + currentHelper(time2) / C);
            K2(1) = (1.0 / RC * x2(0) - (1.0 / RC + 1.0 / RC) * x2(1));
            
            x3(0) = last(0) + K2(0)*temphalfDeltaT;
            x3(1) = last(1) + K2(1)*temphalfDeltaT;
            K3(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x3(0) + 1.0 / RC * x3(1) + currentHelper(time3) / C);
            K3(1) = (1.0 / RC * x3(0) - (1.0 / RC + 1.0 / RC) * x3(1));

            x4(0) = last(0) + K3(0)*tempDeltaT;
            x4(1) = last(1) + K3(1)*tempDeltaT;
            K4(0)= (-1.0 *  (1.0 / RC + 1.0 / RC) * x4(0) + 1.0 / RC * x4(1) + currentHelper(time4) / C);
            K4(1) = (1.0 / RC * x4(0) - (1.0 / RC + 1.0 / RC) * x4(1));
            
            result(0) = last(0) + 1.0 / 6.0 * tempDeltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
            result(1) = last(1) + 1.0 / 6.0 * tempDeltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));

            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", timerequirement*1e9,deltaT*1e9,result(0),result(1));
            timerequirement += deltaTZero;
        }
        
        halfDeltaT = deltaT / 2;
        
        time1 = time;
        time2 = time + halfDeltaT;
        time3 = time + halfDeltaT;
        time4 = time + deltaT;
    
        x1(0) = last(0);
        x1(1) = last(1);
        K1(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x1(0) + 1.0 / RC * x1(1) + currentHelper(time1) / C);
        K1(1) = (1.0 / RC * x1(0) - (1.0 / RC + 1.0 / RC) * x1(1));
        
        x2(0) = last(0) + K1(0)*halfDeltaT;
        x2(1) = last(1) + K1(1)*halfDeltaT;
        K2(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x2(0) + 1.0 / RC * x2(1) + currentHelper(time2) / C);
        K2(1) = (1.0 / RC * x2(0) - (1.0 / RC + 1.0 / RC) * x2(1));
        
        x3(0) = last(0) + K2(0)*halfDeltaT;
        x3(1) = last(1) + K2(1)*halfDeltaT;
        K3(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x3(0) + 1.0 / RC * x3(1) + currentHelper(time3) / C);
        K3(1) = (1.0 / RC * x3(0) - (1.0 / RC + 1.0 / RC) * x3(1));
        
        x4(0) = last(0) + K3(0)*deltaT;
        x4(1) = last(1) + K3(1)*deltaT;
        K4(0)= (-1.0 *  (1.0 / RC + 1.0 / RC) * x4(0) + 1.0 / RC * x4(1) + currentHelper(time4) / C);
        K4(1) = (1.0 / RC * x4(0) - (1.0 / RC + 1.0 / RC) * x4(1));
        
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        error(0) = 1.0 / 72.0 * (-5.0 * K1(0) + 6.0 * K2(0) + 8.0 * K3(0) - 9.0 * K4(0)) * deltaT;
        error(1) = 1.0 / 72.0 * (-5.0 * K1(1) + 6.0 * K2(1) + 8.0 * K3(1) - 9.0 * K4(1)) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (error.norm() / (result.norm() + Ea))), 1.0/3);
        last = result;
        
        if(time == timerequirement) {
            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", timerequirement*1e9,deltaT*1e9,result(0),result(1));
            timerequirement += deltaTZero;
        }
    }
    printf("\n");
    
}



void RK34_EKV(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    double Er = 1e-7;
    double Ea = 1e-10;
    double deltaTZero = deltaT;
    double timerequirement = time + deltaTZero;
    
    printf("RK34_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Step","V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f%-15.5f\n",0.0,deltaT*1e9,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double Vdd = 5.0;
    double C = 1.0e-12;
    
    double halfDeltaT, tempDeltaT, temphalfDeltaT;
    double time1, time2, time3, time4;
    Vector2d K1, K2, K3, K4;
    Vector2d x1, x2, x3, x4;
    Vector2d result, error;
    
    while (time < t) {
        
        if(time + deltaT > timerequirement) {
            tempDeltaT = timerequirement - time;
            temphalfDeltaT = tempDeltaT / 2;
            
            time1 = time;
            time2 = time + temphalfDeltaT;
            time3 = time + temphalfDeltaT;
            time4 = time + tempDeltaT;
            
            x1(0) = last(0);
            x1(1) = last(1);
            K1(0) = (-1.0 / RC * last(0) + currentHelper(time1) / C);
            K1(1) = (-currentHelperEKV(x1(0), x1(1)) / 1e-12 - 1.0 / RC * x1(1) + Vdd / RC);
            
            x2(0) = last(0) + K1(0)*temphalfDeltaT;
            x2(1) = last(1) + K1(1)*temphalfDeltaT;
            K2(0) = (-1.0 / RC * x2(0) + currentHelper(time2) / C);
            K2(1) = (-currentHelperEKV(x2(0), x2(1)) / C - 1.0 / RC * x2(1) + Vdd / RC);
            
            x3(0) = last(0) + K2(0)*temphalfDeltaT;
            x3(1) = last(1) + K2(1)*temphalfDeltaT;
            K3(0) = (-1.0 / RC * x3(0) + currentHelper(time3) / C);
            K3(1) = (-currentHelperEKV(x3(0), x3(1)) / C - 1.0 / RC * x3(1) + Vdd / RC);
            
            x4(0) = last(0) + K3(0)*tempDeltaT;
            x4(1) = last(1) + K3(1)*tempDeltaT;
            K4(0) = (-1.0 / RC * x4(0) + currentHelper(time4) / C);
            K4(1) = (-currentHelperEKV(x4(0), x4(1)) / C - 1.0 / RC * x4(1) + Vdd / RC);
            
            result(0) = last(0) + 1.0 / 6.0 * tempDeltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
            result(1) = last(1) + 1.0 / 6.0 * tempDeltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
            
            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", timerequirement*1e9,deltaT*1e9,result(0),result(1));
            timerequirement += deltaTZero;
        }
        
        halfDeltaT = deltaT / 2;
        
        time1 = time;
        time2 = time + halfDeltaT;
        time3 = time + halfDeltaT;
        time4 = time + deltaT;
        
        x1(0) = last(0);
        x1(1) = last(1);
        K1(0) = (-1.0 / RC * last(0) + currentHelper(time1) / C);
        K1(1) = (-currentHelperEKV(x1(0), x1(1)) / 1e-12 - 1.0 / RC * x1(1) + Vdd / RC);
        
        x2(0) = last(0) + K1(0)*halfDeltaT;
        x2(1) = last(1) + K1(1)*halfDeltaT;
        K2(0) = (-1.0 / RC * x2(0) + currentHelper(time2) / C);
        K2(1) = (-currentHelperEKV(x2(0), x2(1)) / C - 1.0 / RC * x2(1) + Vdd / RC);
        
        x3(0) = last(0) + K2(0)*halfDeltaT;
        x3(1) = last(1) + K2(1)*halfDeltaT;
        K3(0) = (-1.0 / RC * x3(0) + currentHelper(time3) / C);
        K3(1) = (-currentHelperEKV(x3(0), x3(1)) / C - 1.0 / RC * x3(1) + Vdd / RC);

        x4(0) = last(0) + K3(0)*deltaT;
        x4(1) = last(1) + K3(1)*deltaT;
        K4(0) = (-1.0 / RC * x4(0) + currentHelper(time4) / C);
        K4(1) = (-currentHelperEKV(x4(0), x4(1)) / C - 1.0 / RC * x4(1) + Vdd / RC);
        
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        error(0) = 1.0 / 72.0 * (-5.0 * K1(0) + 6.0 * K2(0) + 8.0 * K3(0) - 9.0 * K4(0)) * deltaT;
        error(1) = 1.0 / 72.0 * (-5.0 * K1(1) + 6.0 * K2(1) + 8.0 * K3(1) - 9.0 * K4(1)) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (error.norm() / (result.norm() + Ea))), 1.0/3);
        last = result;
        
        if(time == timerequirement) {
            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", timerequirement*1e9,deltaT*1e9,result(0),result(1));
            timerequirement += deltaTZero;
        }
    }
    printf("\n");
    
}







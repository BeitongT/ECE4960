/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
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
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
//cal f(x)


Vector2d cal_Jacobi(Vector2d Xnow) {
    Vector2d output;
    double x1 = Xnow(0);
    double x2 = Xnow(1);
    
    output(0) = 40 * pow(x1, 3) - 40 * x1;
    output(1) = 20 * x2 - 20;
    return output;
}


Matrix2d cal_Hessian(Vector2d Xnow) {
    Matrix2d output;
    double x1 = Xnow(0);
    double x2 = Xnow(1);
    output(0,0) = 120 * pow(x1, 2) -40;
    output(0,1) = 0;
    output(1,0) = 0;
    output(1,1) = 20;
    return output;
}

Vector2d cal_delta(Vector2d Xnow) {
    Matrix2d Hessian;
    Vector2d Jacobi;
    Hessian = cal_Hessian(Xnow);
    //    cout << Hessian <<endl;
    
    Jacobi = cal_Jacobi(Xnow);
    //    cout << Jacobi <<endl;
    
    Vector2d out;
    out = -1 * Hessian.inverse() * Jacobi;
    //    cout << out <<endl;
    return out;
}

double cal_f_abs(Vector2d Xnow) {
    double x1 = Xnow(0);
    double x2 = Xnow(1);
    double result = pow((3*x1*x1 + x2 - 4), 2) + pow(x1*x1 - 3*x2 + 2, 2);
    return abs(result);
}

double cal_x_second(Vector2d Xnow) {
    double x1 = Xnow(0);
    double x2 = Xnow(1);
    return sqrt(x1*x1 + x2*x2);
}




int main(int argc, const char * argv[]) {
    
    Vector2d result;
    result << 10,1;
    double delta = 1e-4;
    int i = 0;
    
    printf("X(0) = (%f,%f)\n",result(0),result(1));
    do {
        printf("K             = %d \n",i++);
        printf("||X(k)||2     = %.20f \n",cal_x_second(result));
        
        Vector2d temp;
        Vector2d result_temp1;
        Vector2d result_temp2;
        result_temp1 = result;
        result_temp1(0) = result_temp1(0) + delta;
//        cout <<result_temp1<<endl;
        result_temp2 = result;
        result_temp2(1) = result_temp2(1) + delta;

        temp(0)= -1 * (cal_f_abs(result_temp1) - cal_f_abs(result)) / delta;
        temp(1)= -1 * (cal_f_abs(result_temp2) - cal_f_abs(result)) / delta;
        
        //line search
        double minI = 0;
        double minJ = 0;
        double min = 1e10;
        for(double i = 1e-5;i < 1e5; i*=10) {
            for(double j = 1e-5;j < 1e5; j*=10) {
                Vector2d tempin;
                tempin = temp;
                tempin(0) *= i;
                tempin(1) *= j;
                double tempresult =cal_f_abs(tempin + result);
                if (tempresult< min) {
                    min =tempresult;
                    minI = i;
                    minJ = j;
                }
            }
        }
        temp(0) *= minI;
        temp(1) *= minJ;
        
        
//        cout << temp << endl;

        
        //double scalar = find_minimum(x,temp);
        //temp = temp * scalar;
        
        printf("||ΔX(k)||2    = %.20f \n",cal_x_second(temp));
        printf("V(X(k))       = %.20f \n",cal_f_abs(result));
        printf("\n");
        result = result + temp;
        //        cout << result << endl;
    } while(cal_f_abs(result) > 1e-7);
    
    cout << "result" <<endl;
    cout <<result<< endl;
    return 0;
}



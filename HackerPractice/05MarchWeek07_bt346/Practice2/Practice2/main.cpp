/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week7 class on Thursday.
 *       SOR iteration method to solve the problem.
 *
 *
 * AUTHOR :   Beitong Tian        START DATE : 18 Mar.8
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <array>
#include <stdio.h>
#include <Eigen/Dense>
using namespace std;



int main(int argc, const char * argv[]) {
    

    Eigen::MatrixXd A(5,5);
    A << -4,1,0,0,1,4,-4,1,0,0,0,1,-4,1,0,0,0,1,-4,1,1,0,0,1,-4;
    Eigen::VectorXd B(5);
    B << 1,0,0,0,0;
    Eigen::VectorXd Borigin(5);
    Borigin = B;
    Eigen::MatrixXd D(5,5);
    D <<-4,0,0,0,0,0,-4,0,0,0,0,0,-4,0,0,0,0,0,-4,0,0,0,0,0,-4;
    Eigen::MatrixXd Dinverse(5,5);
    Dinverse = D.inverse();
    Eigen::VectorXd X(5);
    X << -0.25,0,0,0,0;
    Eigen::VectorXd Xnew(5);
    Xnew << -0.25,0,0,0,0;
    Eigen::VectorXd R(5);
    R << 1,1,1,1,1;
    int count = 0;
    double difference = 1;
    while(difference>1e-7) {
        cout << "K = " << ++count<< endl;
        cout << "X1(k) = "<<X(0)<<endl;
        R = B - A*X;
        Xnew = X + 0.5 * Dinverse * R;
        cout << "X1(k+1) = "<<Xnew(0)<<endl;
        difference = (Xnew - X).norm();
        cout << "||deltaX||2 = " << difference << endl;
        cout << "||R(k)||2 = " << R.norm() << endl;
        cout << endl;
        X = Xnew;
    }
    cout << "the result is" << endl;
    cout << X << endl;
    
    return 0;
    
}


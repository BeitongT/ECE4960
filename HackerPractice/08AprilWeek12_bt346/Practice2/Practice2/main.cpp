/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      2D PDE solver
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Apr. 20
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/




#include <iostream>
#include <stdio.h>
#include <math.h>
#include "matrix.hpp"
#include <algorithm>
#include <cstdio>
#include <ctime>

using namespace std;

int main(int argc, const char * argv[]) {
    
    //use the matrix solever to solve the matrix
    double arrayA[81] = {-4, 1, 0, 1, 0, 0, 0, 0, 0,
                          1,-4, 1, 0, 1, 0, 0, 0, 0,
                          0, 1,-4, 0, 0, 1, 0, 0, 0,
                          1, 0, 0,-4, 1, 0 ,1, 0, 0,
                          0, 1, 0, 1,-4, 1, 0, 1, 0,
                          0, 0, 1, 0, 1,-4, 0, 0, 1,
                          0, 0, 0, 1, 0, 0,-4, 1, 0,
                          0, 0, 0, 0, 1, 0, 1,-4, 1,
                          0, 0, 0, 0, 0, 1, 0, 1,-4 };
    Matrix *matrixA = new Matrix(arrayA,9,9);
    double h = 10 * 1.0e-6;
    double hs = h * h;
    double BC = 1.0;
    double Na = -1.0e17 / 1.0e6;
    double Nd = 1.0e15 / 1.0e6;
    double temp1 = hs * Na - 2.0 * BC;
    double temp2 = - hs * Nd;
    
    double b[9] = { temp1,
                    temp1,
                    temp2,
                    temp2,
                    temp2,
                    temp2,
                    temp2,
                    temp2,
                    temp2
    };
    Matrix *matrixB = new Matrix(b,9,1);
    
    double result[9] = {0};
    fill_n(result,9,1.0);
    Matrix *matrixResult = new Matrix(result,9,1);
    
    Jacobi(matrixA, matrixB, matrixResult);
    
    printMatrix(matrixResult);
    
    return 0;
}



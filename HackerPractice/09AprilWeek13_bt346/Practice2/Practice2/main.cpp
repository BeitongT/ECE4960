/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      Downwind backward euler to solve the 1D Hyperbolic Problem
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
    double arrayA[49] = { 0, 0, 0, 0, 0, 0, 0,
                          1, 0, 0, 0, 0, 0, 0,
                          0, 1, 0, 0, 0, 0, 0,
                          0, 0, 1, 0, 0, 0, 0,
                          0, 0, 0, 1, 0, 0, 0,
                          0, 0, 0, 0, 1, 0, 0,
                          0, 0, 0, 0, 0, 0, 0};
    Matrix *matrixA = new Matrix(arrayA,7,7);

    
    double b[7] = { 0,
                    0,
                    10,
                    0,
                    0,
                    0,
                    0
    };
    Matrix *matrixB = new Matrix(b,7,1);
    
    double result[7] = {0};
    fill_n(result,7,1.0);
    Matrix *matrixResult = new Matrix(result,7,1);
    Matrix *matrixResultKeep = new Matrix(result,7,1);

    
    productAx(matrixA, matrixB, matrixResult);
    cout << "time = " << 1 << " ";
    printMatrix(matrixResult);
    for (int i = 2; i <= 5; i++) {
        matrixB = matrixResult;
        Matrix *matrixResult = new Matrix(result,7,1);
        cout << "time = " << i << " ";
        productAx(matrixA, matrixB, matrixResult);
        printMatrix(matrixResult);
       
    }
    return 0;
}



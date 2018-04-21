/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      discretized Poisson equation
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Apr. 17
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
    double arrayA[25] = {-2,1,0,0,1,-2,1,0,0,1,-2,1,0,0,1,-2};
    Matrix *matrixA = new Matrix(arrayA,4,4);
    
    double b[4] = {-1,0,0,0};
    Matrix *matrixB = new Matrix(b,4,1);
    
    double result[4] = {0};
    fill_n(result,4,1.0);
    Matrix *matrixResult = new Matrix(result,4,1);
    
    Jacobi(matrixA, matrixB, matrixResult);
    
    printMatrixAll(matrixResult);
    
    return 0;
}



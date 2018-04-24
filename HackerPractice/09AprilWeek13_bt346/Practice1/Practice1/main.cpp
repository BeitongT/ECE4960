/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      One dimensinal parabolic PDE 
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Apr. 24
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
    double D = 1.0;
    double hsquare = 1.0;
    double deltaT = 1.0;
    double side = -D / hsquare * deltaT;
    double middle = 2.0 * D / hsquare * deltaT  + 1.0;
    //use the matrix solever to solve the matrix
    double arrayA[9] = {middle,side,0,
                        side,middle,side,
                        0,side,middle};
    Matrix *matrixA = new Matrix(arrayA,3,3);
    
    double b[3] = {0,10.0,0};
    Matrix *matrixB = new Matrix(b,3,1);
    
    double result[3] = {0};
    fill_n(result,3,1.0);
    

    Matrix *matrixResult = new Matrix(result,3,1);
    Matrix *matrixResultKeep = new Matrix(result,3,1);

    //productAx(matrixA, matrixB, matrixResult); forward Euler not good
    Jacobi(matrixA, matrixB, matrixResult);
    cout << "time = " << 1 << " ";
    printMatrix(matrixResult);
    copyMatrix(matrixResult, matrixB);
    copyMatrix(matrixResultKeep, matrixResult);




    
    for (int i = 2; i <= 5; i++) {
        
        cout << "time = " << i << " ";
        Jacobi(matrixA, matrixB, matrixResult);
        printMatrix(matrixResult);
        copyMatrix(matrixResult, matrixB);
        copyMatrix(matrixResultKeep, matrixResult);
    }
    
    
    
    return 0;
}



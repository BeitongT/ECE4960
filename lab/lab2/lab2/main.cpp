//
//  main.cpp
//  homework4
//
//  Created by Beitong Tian on 2/22/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "matrix.hpp"
#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

int main(int argc, const char * argv[]) {
    
    printf("******LAB2******\n\n");
    
    //define the sparse matrix
    int rank = 5000;
    int elements =253677;
    Matrix *hugematrix = new Matrix(rank,rank,elements);
    hugematrix -> rowIndex = new int[rank+1]();
    hugematrix -> colIndex = new int[elements]();
    hugematrix -> matrix = new double[elements]();
    
    //read in the mat1
    readValues(hugematrix);
    
    //initial the B vector
    double b1[5000] = {0};
    b1[0] = 1.0;
    Matrix *matrixB1 = new Matrix(b1,5000,1);
    
    double b2[5000] = {0};
    b2[4] = 1.0;
    Matrix *matrixB2 = new Matrix(b2,5000,1);
    
    double b3[5000] = {0};
    fill_n(b3,5000,1.0);
    Matrix *matrixB3 = new Matrix(b3,5000,1);
    
    //initial the X vector
    double resultLab2_b1[5000] = {0};
    fill_n(resultLab2_b1,5000,1.0);
    Matrix *matrixResult_b1 = new Matrix(resultLab2_b1,5000,1);

    double resultLab2_b2[5000] = {0};
    fill_n(resultLab2_b2,5000,1.0);
    Matrix *matrixResult_b2 = new Matrix(resultLab2_b2,5000,1);
    
    double resultLab2_b3[5000] = {0};
    fill_n(resultLab2_b3,5000,1.0);
    Matrix *matrixResult_b3 = new Matrix(resultLab2_b3,5000,1);
    
    
    //verify if the matrix will converge
    isConvergenceC(hugematrix);
    
    //calculate the X
    printf("\n");

    std::clock_t start;
    double duration;
    start = std::clock();
    printf("iteration time: ");
    Jacobi(hugematrix, matrixB1, matrixResult_b1);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration <<" s"<<'\n';
    cout << "residual for b1 : " << calResidual(hugematrix, b1, matrixResult_b1)<<endl;
    printf("\n");
    
    std::clock_t start2;
    double duration2;
    start2 = std::clock();
    printf("iteration time: ");
    Jacobi(hugematrix, matrixB2, matrixResult_b2);
    duration2 = ( std::clock() - start2 ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration2 <<" s"<<'\n';
    cout << "residual for b2 : " << calResidual(hugematrix, b2, matrixResult_b2)<<endl;
    printf("\n");

    
    std::clock_t start3;
    double duration3;
    start3 = std::clock();
    printf("iteration time: ");
    Jacobi(hugematrix, matrixB3, matrixResult_b3);
    duration3= ( std::clock() - start3 ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration3 <<" s"<<'\n';
    cout << "residual for b3 : " << calResidual(hugematrix, b3, matrixResult_b3)<<endl;
    printf("\n");

//    printMatrixAll(matrixResult_b2);
//    printMatrixValues(matrixResult_b1);

    //ouput the result
    

    
    
    return 0;
}


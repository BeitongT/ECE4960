//
//  main.cpp
//  lab2 
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
    
    /*test sparse matrix constructor*/
    double arrayA[25] = {1,2,0,0,3,4,5,6,0,0,0,7,8,0,9,0,0,0,10,0,11,0,0,0,12};
    Matrix *matrixA = new Matrix(arrayA,5,5);
    //finish construct the matrix
    double testConstructorResult = testConstructor(matrixA,arrayA);
    
    cout << "The result for testing Constructor module: "<< testConstructorResult<<endl;
    if(testConstructorResult!=0) {
        cout << "constructor test failed"<<endl;
        return 0;
    }
    else {cout << "constructor test passed"<<endl;}
    /*test end*/
    

    
    
    
    //define the sparse matrix
    int rank = 5000;
    int elements =253677;
    Matrix *hugematrix = new Matrix(rank,rank,elements);
    hugematrix -> rowIndex = new int[rank+1]();
    hugematrix -> colIndex = new int[elements]();
    hugematrix -> matrix = new double[elements]();
    
    //read in the mat1
    readValues(hugematrix);
    
    
    
    /*test the product function*/
    double testProductResult = 0;
    testProductResult = mattixProductTest(hugematrix);
    cout <<endl<< "The test result for testing matrix product: "<< testProductResult << endl;
    if(testProductResult>1e-5) {
        cout << "matrix product test failed"<<endl;
        return 0;
    }
    else {cout << "matrix product test passed"<<endl;}
    /*test end*/
    
    
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
    cout<<endl;
    cout<<"Check if the matrix will convergence."<<endl;
    isConvergenceC(hugematrix);
    
    
    //calculate the X and output the result
    printf("\n");
    cout << "the tolerance is 1e-7"<<endl;
    
    /*initial the memory test variable*/
    long long mem = 0;
    long long mem_current = 0;
    
    //test vector b1
    std::clock_t start;
    double duration;
    start = std::clock();
    printf("iteration time: ");
    mem = current_used_mem();
    Jacobi(hugematrix, matrixB1, matrixResult_b1);
    mem_current = current_used_mem();
    cout << "current mem use for b1: " <<mem_current - mem<<endl;
    mem = mem_current;
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration <<" s"<<'\n';
    cout << "residual for b1 : " << calResidual(hugematrix, b1, matrixResult_b1)<<endl;
    printf("\n");
    

    //test vector b2
    std::clock_t start2;
    double duration2;
    start2 = std::clock();
    printf("iteration time: ");
    mem = current_used_mem();
    Jacobi(hugematrix, matrixB2, matrixResult_b2);
    mem_current = current_used_mem();
    cout << "current mem use for b2: " <<mem_current - mem<<endl;
    mem = mem_current;
    duration2 = ( std::clock() - start2 ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration2 <<" s"<<'\n';
    cout << "residual for b2 : " << calResidual(hugematrix, b2, matrixResult_b2)<<endl;
    printf("\n");


    //test vector b3
    std::clock_t start3;
    double duration3;
    start3 = std::clock();
    printf("iteration time: ");
    mem = current_used_mem();
    Jacobi(hugematrix, matrixB3, matrixResult_b3);
    mem_current = current_used_mem();
    cout << "current mem use for b3: " <<mem_current - mem<<endl;
    mem = mem_current;
    duration3= ( std::clock() - start3 ) / (double) CLOCKS_PER_SEC;
    std::cout<<"time for b1: "<< duration3 <<" s"<<'\n';
    cout << "residual for b3 : " << calResidual(hugematrix, b3, matrixResult_b3)<<endl;
    printf("\n");
    



    

    
    
    return 0;
}


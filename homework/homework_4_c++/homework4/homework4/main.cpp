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
#include <fstream>
#include <algorithm>
#include "matrix.hpp"
using namespace std;



int main(int argc, const char * argv[]) {
    
    
    printf("This is the PART I for homework4.\n\n");
    
    //define all the initial values
    Eigen::MatrixXd A(5,5);
    A << 1,2,0,0,3, 4,5,6,0,0, 0,7,8,0,9, 0,0,0,10,0, 11,0,0,0,12;
    Eigen::VectorXd X(5);
    X << 5,4,3,2,1;
    Eigen::VectorXd B;


    
    double tempMatrix[25] = {1,2,0,0,3,4,5,6,0,0,0,7,8,0,9,0,0,0,10,0,11,0,0,0,12};
    Matrix *matrix1 = new Matrix(tempMatrix,5,5);
    
    double tempMatrix2[5] = {5,4,3,2,1};
    Matrix *matrix2 = new Matrix(tempMatrix2,5,1);
    //printMatrixAll(matrix2);
    double tempMatrix3[5] = {1,1,1,1,1};
    Matrix *matrix3 = new Matrix(tempMatrix3,5,1);
    //end
    
    //(1)Permutation of (1, 3) and then (1, 5).
    
    printf("(1)Permutation of (1, 3) and then (1, 5).  \n\n");
    rowPermute(matrix1, matrix2, 1-1, 3-1);
    rowPermute(matrix1, matrix2, 1-1, 5-1);
    
    printMatrix(matrix1);
    printMatrix(matrix2);

    A.row(1-1).swap(A.row(3-1));
    A.row(1-1).swap(A.row(5-1));
    X.row(1-1).swap(X.row(3-1));
    X.row(1-1).swap(X.row(5-1));
    
    printFullMatrix(A);
    printFullMatrix(X);



    printf("The result for A permutation(1,3)(1,5) is %s.\n",testMatrix(matrix1, A) == 0 ? "right":"false");
    printf("The result for X permutation(1,3)(1,5) is %s.\n",testMatrix(matrix2, X) == 0 ? "right":"false");
    printf("\n");
    
    //(2)    Test 3.0*row[1] + row [4] and -4.4*row[5] + row[2].
    printf("(2)Test 3.0*row[1] + row [4] and -4.4*row[5] + row[2]. \n\n");
    rowScale(matrix1, matrix2, 1-1, 4-1, 3.0);
    rowScale(matrix1, matrix2, 5-1, 2-1, -4.4);
    printMatrix(matrix1);
    printMatrix(matrix2);
    
    A.row(4-1) += 3.0 * A.row(1-1);
    A.row(2-1) += -4.4 * A.row(5-1);
    X.row(4-1) += 3.0 * X.row(1-1);
    X.row(2-1) += -4.4 * X.row(5-1);
    printFullMatrix(A);
    printFullMatrix(X);
    
    printf("The result for A 3.0*row[1] + row [4] and -4.4*row[5] + row[2] is %s.\n",testMatrix(matrix1, A) == 0 ? "right":"false");
    printf("The result for X 3.0*row[1] + row [4] and -4.4*row[5] + row[2]) is %s.\n",testMatrix(matrix2, X) == 0 ? "right":"false");
    printf("\n");

    
    //(3)    Test Ax = b
    printf("(3)Test Ax = b. \n\n");
    
    productAx(matrix1, matrix2, matrix3);
    printMatrix(matrix3);
    
    B = A*X;
    printFullMatrix(B);
    printf("The result for Ax = b is %s.\n",testMatrix(matrix3, B) == 0 ? "right":"false");
    printf("\n");
    
    
    printf("This is the PART II for homework4.\n\n");

    ifstream fin("memplus.mtx");
    
    int M, N, L;
    
    while (fin.peek() == '%') fin.ignore(2048, '\n');
    
    fin >> M >> N >> L;
    
    Matrix *bigmatrix = new Matrix(M,N,L);
    bigmatrix -> rowIndex = (int*)malloc((M+1)*sizeof(int));
    memset(bigmatrix -> rowIndex, 0, (M+1)*sizeof(int));
    bigmatrix -> colIndex = (int*)malloc(L*sizeof(int));
    memset(bigmatrix -> colIndex, 0, L*sizeof(int));
    bigmatrix -> matrix = (double*)malloc(L*sizeof(double));
    memset(bigmatrix -> matrix, 0, L*sizeof(double));
    double sum = 0;
    (bigmatrix -> rowIndex)[0] = 0;;
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        fin >> m >> n >> data;
        sum +=data;
        (bigmatrix -> rowIndex)[n]++;
        (bigmatrix -> colIndex)[l] = m-1;
        (bigmatrix -> matrix)[l] = data;
    }
    
    for(int i = 1;i<M+1;i++) {
        (bigmatrix -> rowIndex)[i] += (bigmatrix -> rowIndex)[i-1];
    }
    
    fin.close();
//    printMatrixRowIndex(bigmatrix);
//    printMatrixNumber(bigmatrix);
//    printMatrixColIndex(bigmatrix);
//    printMatrixValues(bigmatrix);

    rowPermuteSingle(bigmatrix, 1-1, 3-1);
    rowPermuteSingle(bigmatrix, 1-1, 5-1);
    rowPermuteSingle(bigmatrix, 10-1, 3000-1);
    rowPermuteSingle(bigmatrix, 5000-1, 10000-1);
    rowPermuteSingle(bigmatrix, 6-1, 15000-1);

    rowScaleSingle(bigmatrix, 2-1, 4-1, 3.0);
    rowPermuteSingle(bigmatrix, 2-1, 5-1);
    rowScaleSingle(bigmatrix, 5-1, 4-1, -3.0);
    
    double vector[M];
    for (int i = 0; i< M ; i++) {
        vector[i] = 1.0;
    }
    Matrix *smallmatrix = new Matrix(vector,M,1);
//    printMatrixAll(smallmatrix);
    Matrix *resultmatrix = new Matrix(vector,M,1);
    
    productAx(bigmatrix, smallmatrix, resultmatrix);

    
//    printMatrixValues(smallmatrix);
//    printMatrixValues(resultmatrix);
    
    double resultPart2 = testMatrix2(bigmatrix,resultmatrix);
    
    printf("the result for part2 is %e.\n",resultPart2);
//    printf("the result real is %e.\n",sum);


    
    freeMemory(matrix1);
    freeMemory(matrix2);
    freeMemory(matrix3);

    
    
    return 0;
}


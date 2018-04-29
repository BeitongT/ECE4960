//
//  matrix.hpp
//  lab2 version
//
//  Created by Beitong Tian on 3/2/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <algorithm>    // std::max
#include <fstream>

#include <mach/mach.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

using namespace std;

#define SUCCESS 0;
#define FAILED 1;


int retrieveElement(double *matrix, double **outmatrix,int **rowId, int **colID, int row, int col);

//constructor and construct functions
typedef struct Matrix{
public:
    int row;
    int col;
    int totalElement;
    double *matrix;
    int *rowIndex;
    int *colIndex;
    
    Matrix(int rowData, int colData,int total){
        row = rowData;
        col = colData;
        totalElement = total;
        matrix = NULL;
        rowIndex = NULL;
        colIndex = NULL;
    }
    
    Matrix(double *data, int rowData, int colData){
        matrix = NULL;
        rowIndex = NULL;
        colIndex = NULL;

        row = rowData;
        col = colData;

        totalElement = retrieveElement(data,&matrix,&rowIndex,&colIndex,row,col);
    }
    
    ~Matrix(){
        delete [] matrix;
        delete [] rowIndex;
        delete [] colIndex;
        matrix = NULL;
        rowIndex = NULL;
        colIndex = NULL;
    }
} Matrix;

void readValues(Matrix *A);
void isConvergenceC(Matrix *A);

//calculate function
int productAx(Matrix* A, Matrix* X, Matrix* B);
int Jacobi(Matrix *A, Matrix *B, Matrix *C);

//print function
void printMatrixAll(Matrix *A);
void printMatrix(Matrix *A);
void printMatrixNumber(Matrix *A);
void printMatrixRowIndex(Matrix *A);
void printMatrixColIndex(Matrix *A);
void printMatrixValues(Matrix *A);

//free heap memory
void freeMemory(Matrix *A);

//calculate the residual
double* twoArraySub(double *A, double*B, int length);
double second_Norm(double *A, int length);
double calResidual(Matrix *A, double *B, Matrix *X);

//test functions
double mattixProductTest(Matrix *A);
long long current_used_mem();
double testConstructor(Matrix *A,double * B);

void copyMatrix(Matrix *sourse, Matrix *copy);


#endif /* matrix_hpp */

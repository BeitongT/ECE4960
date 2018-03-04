//
//  matrix.hpp
//  homework4
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
#include <Eigen/Dense>


#define SUCCESS 0;
#define FAILED 1;
#define NULLERROR 2;
#define STACKERROR 3;

int retrieveElement(double *matrix, double **outmatrix,int **rowId, int **colID, int row, int col);



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

int rowPermuteSingle(Matrix *A, int i, int j);
int rowPermute(Matrix *A, Matrix *B, int i, int j);
int rowScaleSingle(Matrix *A, int i, int j, double a);
int rowScale(Matrix *A, Matrix *B, int i, int j, double a);
int productAx(Matrix* A, Matrix* X, Matrix* B);

void printMatrixAll(Matrix *A);
void printMatrix(Matrix *A);
void printMatrixNumber(Matrix *A);
void printMatrixRowIndex(Matrix *A);
void printMatrixColIndex(Matrix *A);
void printMatrixValues(Matrix *A);
void printFullMatrix(Eigen::MatrixXd A);

void freeMemory(Matrix *A);
double testMatrix(Matrix *A,Eigen::MatrixXd B);
double testMatrix2(Matrix *A,Matrix *B);




#endif /* matrix_hpp */

/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week4 class on Thursday.
 *       Using the row-compressed storage to implement the vector product
 *
 *
 * AUTHOR :   Beitong Tian        START DATE : 18 Feb. 15
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
#include "matrix.hpp"
FILE * pFile1;

using namespace std;

int main(int argc, const char * argv[]) {
    //this is the full matrix version
    Eigen::MatrixXd A(5,5);
    A << 1,2,0,0,3, 4,5,6,0,0, 0,7,8,0,9, 0,0,0,10,0, 11,0,0,0,12;
    
    Eigen::VectorXd B(5);
    B << 1,1,1,1,1;
    
    Eigen::VectorXd maxRow = A*B;
    cout << maxRow<<endl;
    cout << "Maximum row vector sum" << endl;
    cout << maxRow.maxCoeff() << endl;
    cout << endl;

    Eigen::MatrixXd C(1,5);
    C << 1,1,1,1,1;
    Eigen::MatrixXd maxCol = C*A;
   cout << maxCol<<endl;
    cout << "Maximum col vector sum" << endl;
    cout << maxCol.maxCoeff() << endl;
    cout << endl;

    //this is the sparse matrix version
    
    double tempMatrix[25] = {1,2,0,0,3,4,5,6,0,0,0,7,8,0,9,0,0,0,10,0,11,0,0,0,12};
    Matrix *matrix1 = new Matrix(tempMatrix,5,5);
    
    double tempMatrix2[5] = {1,1,1,1,1};
    Matrix *matrix2 = new Matrix(tempMatrix2,5,1);

    double tempMatrix3[5] = {1,1,1,1,1};
    Matrix *matrix3 = new Matrix(tempMatrix3,5,1);
    
    productAx(matrix1, matrix2, matrix3);
//    retrieveElement(matrix3->matrix, &(matrix3->matrix), &(matrix3->rowIndex), &(matrix3->colIndex), matrix3->row, matrix3->col);
    

    printMatrix(matrix3);
    
    cout << "Sparse Maximum row vector sum" << endl;
    double maxR = 0;
    for (int i = 0; i < matrix3->totalElement;i++) {
        if ((matrix3->matrix)[i]>maxR)
            maxR =(matrix3->matrix)[i];
    }
    cout << maxR << endl;
    cout << endl;

    
    double tempMatrix4[5] = {1,1,1,1,1};
    Matrix *matrix4 = new Matrix(tempMatrix4,1,5);
    
    double tempMatrix5[5] = {1,1,1,1,1};
    Matrix *matrix5 = new Matrix(tempMatrix5,1,5);
    
    productAx(matrix4, matrix1, matrix5);

    printMatrix(matrix5);
    
    cout << "Sparse Maximum col vector sum" << endl;
    double maxC = 0;
    for (int i = 0; i < matrix5->totalElement;i++) {
        if ((matrix5->matrix)[i]>maxC)
            maxC =(matrix5->matrix)[i];
    }
    cout << maxC<< endl;
    
    
    

    
    
    
    
    
    

    
   
    
    return 0;
}

















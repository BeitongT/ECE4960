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
FILE * pFile1;

using namespace std;
void retrive_elements(int *, int *, int *, int * ,int ,int);
int productAx(int *,int *,int *,int,int);

int row1 = 5;
int col1 = 5;
int row2 = 5;
int col2 = 1;
int values1[12];
int rowPtr1[6];
int colInd1[12];
int values2[12];
int rowPtr2[6];
int colInd2[12];
int result[5][1] = {{0},{0},{0},{0},{0}};
int matrix1[5][5] = {{1,2,0,0,3},{4,5,6,0,0},{0,7,8,0,9},{0,0,0,10,0},{11,0,0,0,12}};
int matrix2[5][1] = {{5},{4},{3},{2},{1}};


int main(int argc, const char * argv[]) {
    
    pFile1 = fopen ("output.txt","w");
    
    
    //////////ground truth//////////
    int ground_truth[5][1] = {{0},{0},{0},{0},{0}};
    
    cout <<"the groundtruth are: ";
    fprintf(pFile1,"the groundtruth are: ");
    for (int i = 0; i<5; i++) {
        for (int j = 0; j< 1;j++) {
            for (int k = 0; k< 5; k++) {
                ground_truth[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        fprintf(pFile1,"%3d ",ground_truth[i][0]);
        cout <<setw(3)<<ground_truth[i][0]<<" ";
    }
    cout << endl;
    fprintf(pFile1,"\n");
    
    //////////ground truth//////////
    
//    retrive_elements((int*)matrix1, values1, rowPtr1, colInd1,row1,col1);
//    retrive_elements((int*)matrix2, values2, rowPtr2, colInd2 ,row2,col2);

    cout << endl;
    productAx((int*)matrix1,(int*)matrix2,(int*)result,row1,col2);
    
    
    
    return 0;
}

void retrive_elements(int *array, int *values, int *rowPtr, int *colInd ,int r, int c) {
    int rowcount = 0;
    int rowhis = 0;
    int count = 0;
    for (int i = 0; i< r; i ++) {
        for (int j = 0; j< c; j ++) {
            //            printf("%d\n", matrix[i][j]);
            if (array[i*c + j] != 0) {
                //                printf("yes\n");
                values[count] = array[i*c +j];
                colInd[count] = j;
                rowcount ++;
                count ++;
            }
            
        }
        rowPtr[i] =rowcount + rowhis;
        rowhis =rowPtr[i];
        rowcount = 0;
    }
    cout <<"the values are: ";
    fprintf(pFile1,"the values are: ");
    
    for (int i = 0; i < 12; i++) {
        fprintf(pFile1,"%3d ",values[i]);
        cout <<setw(3)<<values[i]<<" ";
    }
    
    cout << endl;
    fprintf(pFile1,"\n");
    
    cout <<"the points are: ";
    fprintf(pFile1,"the points are: ");
    
    for (int i = 0; i < 6; i++){
        fprintf(pFile1,"%3d ",rowPtr[i]);
        cout <<setw(3)<< rowPtr[i]<<" ";
        
    }
    cout << endl;
    fprintf(pFile1,"\n");
    
    cout <<"the index  are: " ;
    fprintf(pFile1,"the index are: ");
    for (int i = 0; i < 12; i++) {
        cout <<setw(3)<<colInd[i]<<" ";
        fprintf(pFile1,"%3d ",colInd[i]);
    }
    
    
    cout << endl;
    fprintf(pFile1,"\n");
    
}


int productAx(int * A,int *,int *b,int r,int c ) {
    retrive_elements((int*)matrix1, values1, rowPtr1, colInd1,row1,col1);
    retrive_elements((int*)matrix2, values2, rowPtr2, colInd2 ,row2,col2);
    int start = 0;
    int start2 =0;
    for (int i = 0; i< r; i++) {
        for (int j = 0; j < c; j ++) {
            if (i - 1 < 0) start = 0;
            else start = rowPtr1[i - 1];
            for (int k = start; k < rowPtr1[i]; k++) {
                if ((k - 1)<0) start2 = 0;
                else start2 = rowPtr2[colInd1[k]-1];
                for (int p = start2; p < rowPtr2[colInd1[k]];p++) {
                    if (colInd2[p] == j) {
                        b[j*r+i] += values1[k] * values2[p];
                    }
                }
            }
            start2 = 0;
        }
        start = 0;
    }
    cout << endl;
    fprintf(pFile1,"\n");
    cout <<"my results are: ";
    fprintf(pFile1,"my results are: ");
    for (int i = 0; i < 5; i++){
        fprintf(pFile1,"%3d ",b[i]);
        cout <<setw(3)<< b[i]<<" ";
        
    }
    cout << endl;
    
    return 0;
}


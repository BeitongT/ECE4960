/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week4 class on Thursday.
 *       Compress the matrix with row index
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
void retrive_elements(int *, int *, int *, int * ,int r, int c);

int values[12];
int rowPtr[6];
int colInd[12];
int matrix[5][5] = {{1,2,0,0,3},{4,5,6,0,0},{0,7,8,0,9},{0,0,0,10,0},{11,0,0,0,12}};

int main(int argc, const char * argv[]) {
    pFile1 = fopen ("output.txt","w");

    retrive_elements((int*)matrix, values, rowPtr, colInd ,5,5);

    
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


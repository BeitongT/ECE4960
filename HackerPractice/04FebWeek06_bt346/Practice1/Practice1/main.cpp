/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week6 class on Tuesday.
 *      This is to observe different result for different A.
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 FEB. 27
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <stdio.h>

using namespace std;
void print_matrix(double matrix[][3]);

void print_matrix(double matrix[][3])
{
    printf("the matrix is: \n");
    for(int i =0; i< 6; i++) {
        int index = i / 3;
        int index2 = i %3;
        
        printf("%.9f ", matrix[index][index2]);
        if(index == 0 && index2 == 2 || index == 1 && index2 == 2)
            cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    double x = pow(10,-1);
    for (int i = 0; i< 8 ; i++) {
        double matrix[2][3] = {100,99,199,99,98.01, 197};
        x = x / 10;
        matrix[1][1] -=x;
        print_matrix(matrix);
        double first = matrix[0][0] / matrix[1][0];
        for (int i = 0; i< 3; i++) {
            matrix[1][i] *= first;
            matrix[1][i] -= matrix[0][i];
        }
        double second = matrix[0][1] / matrix[1][1];
        
        for (int i = 0; i< 3; i++) {
            matrix[0][i] -= (matrix[1][i] * second);
        }
        matrix[0][2] /= matrix[0][0];
        matrix[1][2] /= matrix[1][1];

        double second_norm =sqrt(matrix[0][2] * matrix[0][2] + matrix[1][2] * matrix[1][2]);
        printf("the result is: \n");
        printf("e = %e x = %.5f y = %.5f second norm = %.5f\n", x, matrix[0][2], matrix[1][2],second_norm);
        printf("\n");
        
        
        
    }
    
    return 0;
}



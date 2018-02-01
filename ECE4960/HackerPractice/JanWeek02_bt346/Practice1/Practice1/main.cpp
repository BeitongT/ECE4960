/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week2 class on Tuesday.
 *
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Jan 30
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <string>
using namespace std;

void print_result(double answer[][2]);
void output_result(double answer[][2]);

int main(int argc, const char * argv[]) {

    
    double a = 1e-20;
    double b = 1e3;
    double c = 1e3;
    double answer[3][2];

    
    answer[0][0] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    answer[0][1] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    answer[1][0] = (2 * c) / (-b + sqrt(b * b - 4 * a * c));
    answer[1][1] = (2 * c) / (-b - sqrt(b * b - 4 * a * c));
    answer[2][0] = - (c / b);
    answer[2][1] = -(b / a) + (c / b);
    

    output_result(answer);
    print_result(answer);
    return 0;
}

void print_result(double answer[][2]) {
    
    string equation[3] = {"(-b +- sqrt(b * b - 4 * a * c)) / (2 * a)",
        "(2 * c) / (-b + sqrt(b * b - 4 * a * c))",
        "- (c / b); -(b / a) + (c / b)"};
    
    for (int i = 0; i < 3; i++){
        cout << "The result for equation: " << equation[i] << " is:"<< endl;
        cout << "x1 = " << answer[i][0] << endl;
        cout << "x2 = " << answer[i][1] << endl;
    }
}

void output_result(double answer[][2]) {
    ofstream outdata;
    outdata.open("output.txt"); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    for (int i = 0; i < 3; i++){
        string equation[3] = {"(-b +- sqrt(b * b - 4 * a * c)) / (2 * a)",
            "(2 * c) / (-b + sqrt(b * b - 4 * a * c))",
            "- (c / b); -(b / a) + (c / b)"};
        
        outdata << "The result for equation: " << equation[i] << " is:"<< endl;
        outdata << "x1 = " << answer[i][0] << endl;
        outdata << "x2 = " << answer[i][1] << endl;
    }
    outdata.close();
}

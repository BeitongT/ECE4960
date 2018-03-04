/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice3 for the week2 class on Thursday. This is to observe the signed 0.
 *
 *
 * AUTHOR :   Beitong Tian        START DATE :    1 Feb. 30
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
using namespace std;

void isPositiveZero(double y);
void isNegativeZero(double y);
ofstream outdata;

int main(int argc, const char * argv[]) {
//    freopen("out.txt","w",stdout);
    
    outdata.open("output.txt"); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    double pos_zero = 1 / (1/0.0);
    double neg_zero = -1 / (1/0.0);
    double infinity = 1 / 0.0;
    double neg_infinity = -1 / 0.0;
    double nan = infinity - infinity;
    

    isPositiveZero(+1.0);
    isNegativeZero(+1.0);
    
    isPositiveZero(-1.0);
    isNegativeZero(-1.0);
    
    isPositiveZero(__DBL_MAX__);
    isNegativeZero(__DBL_MAX__);
    
    isPositiveZero(-1.0 * __DBL_MAX__);
    isNegativeZero(-1.0 * __DBL_MAX__);
    
    isPositiveZero(pos_zero);
    isNegativeZero(pos_zero);

    isPositiveZero(neg_zero);
    isNegativeZero(neg_zero);
    
    
    isPositiveZero(infinity);
    isNegativeZero(infinity);
    
    
    isPositiveZero(neg_infinity);
    isNegativeZero(neg_infinity);
    
    isPositiveZero(nan);
    isNegativeZero(nan);
    
    // Generating NaN and INF in double
    //
    
    return 0;
}

void isPositiveZero(double y) {
    double x = 1 / (1/0.0);
    //    cout << x << endl;
    if (x == y) {
        outdata << y << "\t" << " true. It is +0."<< endl;
        cout << y  << "\t" << " true. It is +0."<< endl; }
    else {
        outdata << y << "\t" << " false. It is not +0."<< endl;
        cout << y << "\t" << " false. It is not +0."<< endl;}
}

void isNegativeZero(double y) {
    double x = -1 / (1/0.0);
    //    cout << x << endl;
    if (x == y) {
        outdata << y << "\t" << " true. It is -0."<< endl;
        cout << y << "\t" << " true. It is -0."<< endl; }
    else {
        outdata << y << "\t" << " false. It is not -0."<< endl;
        cout << y << "\t" << " false. It is not -0."<< endl;}
    cout << endl;
    outdata << endl;
    
}

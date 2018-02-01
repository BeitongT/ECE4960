/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice4 for the week2 class on Thursday. Underflowing.
 *
 *
 * AUTHOR :   Beitong Tian        START DATE :    1 Feb. 30
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/
#include <iostream>
#include <math.h>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[]) {
    
    ofstream outdata;
    outdata.open("output.txt"); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    double x = 1.234567890123456;
    int i = 1;
    x *= pow(10, -307);
    
    for (i=1; i<20; i++) {
        x /= 10.0;
        cout << i << "  "<< std::setprecision(std::numeric_limits<long double>::digits10 + 1) << x << endl;
        outdata << i << "  "<< std::setprecision(std::numeric_limits<long double>::digits10 + 1) << x << endl;
    }
    
    return 0;
}

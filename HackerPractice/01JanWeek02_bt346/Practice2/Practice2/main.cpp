/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week2 class on Thursday. Generate the
 * INF and NAN.
 *
 *
 * AUTHOR :   Beitong Tian        START DATE : 18 Feb. 1
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[]) {
    
    ofstream outdata;
    outdata.open("output.txt"); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    // Generating NaN and INF in double
    
    double x = 0.0;
    double y = 0.0;
    double doubleResult1;
    double doubleResult2;
    doubleResult1 = 1/x;  doubleResult2 = y/x;
    
    cout <<doubleResult1 << endl;
    cout << doubleResult2 << endl;
    outdata <<doubleResult1 << endl;
    outdata << doubleResult2 << endl;
    outdata.close();
    // Observe NaN and INF handling in integers

    long m = 0;
    long n = 0;
    long intResult1;
    long intResult2;
    intResult1 = 1/m;  intResult2 = m/n;
    cout << intResult1 << endl;
    cout << intResult2 << endl;
    
    return 0;
}

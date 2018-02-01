/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice2 for the week2 class on Thursday. This is to observe the integer overflow.
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

int main(int argc, const char * argv[]) {
    
    ofstream outdata;
    outdata.open("output.txt"); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    long i = 1;
    int Factorial = 1;
    for (i=2; i<20; i++) {
        Factorial *= i;
        cout << i << "\t" << Factorial << endl;
        outdata << i << "\t" << Factorial << endl;
    }
    
    cout << endl;
    outdata << endl;
    
    for (i=2; i<20; i++) {
        Factorial *= i;
        cout << i << "\t" << Factorial << endl;
        outdata << i << "\t" << Factorial << endl;

    }
    outdata.close();
    return 0;
}

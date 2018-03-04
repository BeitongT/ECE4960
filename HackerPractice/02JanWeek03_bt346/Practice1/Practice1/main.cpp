/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week3 class on Tuesday.
 *      This is to observe the h dominate or p dominate error
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 FEB. 8
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
using namespace std;

void print_result(double answer[][2]);
void output_result(double answer[][2]);

int main(int argc, const char * argv[]) {
    ofstream outdata;
    outdata.open("output.txt");
    if (!outdata) {
        cerr << "ERROR" << endl;
        exit(1);
    }
    
    double x = 1;
    double xd = 0;
    double h = 0.1;

    double error = 0;
    
    cout << "h" << endl;
    outdata << "h" << endl;
    cout << "this is the result of x^2" << endl;
    outdata << "this is the result of x^2" << endl;

    for (double h = 0.1;h >= 1e-18; h = h / 10) {
        xd = ((x + h) * (x + h) - x*x) / h;
        error = abs(2.0 - xd);
        cout << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        outdata << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;

    }
    cout << endl;
    outdata << endl;
    cout << "this is the result of x^2 + 10^10" << endl;
    outdata << "this is the result of x^2 + 10^10" << endl;
    for (double h = 0.1;h >= 1e-18; h = h / 10) {
        xd = ((x + h) * (x + h)  + 1e10 - (x - h)*(x - h) - 1e10) / (2 *h);
        error = abs(2.0 - xd);
        cout << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        outdata << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;

    }
    cout << endl;
    outdata << endl;
    cout << endl;
    outdata << endl;

    cout << "2h" << endl;
    outdata << "2h" << endl;
    cout << "this is the result of x^2" << endl;
    outdata << "this is the result of x^2" << endl;
    
    for (double h = 0.1;h >= 1e-18; h = h / 10) {
        xd = ((x + h) * (x + h) - (x - h)*(x-h)) /2 / h;
        error = abs(2.0 - xd);
        cout << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        outdata << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        
    }
    cout << endl;
    outdata << endl;
    cout << "this is the result of x^2 + 10^10" << endl;
    outdata << "this is the result of x^2 + 10^10" << endl;
    for (double h = 0.1;h >= 1e-18; h = h / 10) {
        xd = ((x + h) * (x + h) + 1e10 - (x - h)*(x - h) - 1e10) /2 / h;
        error = abs(2.0 - xd);
        cout << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        outdata << "h = " <<setw(6) <<h << "  the result is: " << setw(8)<<xd << " the relative error is: " << error / 2.0 * 100 << "%"<< endl;
        
    }



    
    outdata.close();
    return 0;
}



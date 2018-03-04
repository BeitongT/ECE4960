/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week3 class on Thursday.
 *       Observe the error in back and forward Euler relation
 *
 *
 * AUTHOR :   Beitong Tian        START DATE : 18 Feb. 8
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;
int main(int argc, const char * argv[]) {
    ofstream outdata;
    outdata.open("output.txt");
    if(!outdata) {
        cerr << "ERROR:file could not be opened" << endl;
        exit(1);
    }
    
    double result1 = 0;
    cout<< "this is the ground truth" << endl;
    outdata<< "this is the ground truth" << endl;

    for (int i = 0; i < 21; i ++) {
        result1 = exp(-i);
        cout <<"i = " <<setw(2)<< i << "   result: " <<result1 << endl;
        outdata <<"i = " <<setw(2)<< i << "   result: " <<result1 << endl;
    }
    
    
    cout << endl;
    outdata << endl;
    
    cout<< "this is the second method" << endl;
    outdata<< "this is the second method" << endl;
    double result2 = 1;
    double resulthis = 1;
    double deltat[3] = {0.5, 1.0, 2.0};
    double x = 0;
    for (int p = 0; p<3; p++) {
        cout<< "delta is "<< deltat[p] << endl;
        outdata<< "delta is "<< deltat[p] << endl;

        for (int i = 0; i < 21; i ++) {
            for (x = i; x>0;x-=deltat[p]) {
                result2 = resulthis * (1 - deltat[p]);
                resulthis = result2;
            }
            cout <<"i = " <<setw(2)<< i << "   result: " <<result2 << endl;
            outdata <<"i = " <<setw(2)<< i << "   result: " <<result2 << endl;
            result2 = 0;
            resulthis = 1;
        }
        cout << endl;
        outdata << endl;
    }

    cout << endl;
    outdata << endl;
    cout<< "this is the third method" << endl;
    outdata<< "this is the third method" << endl;
    double result3 = 1;
    resulthis = 1;
    x = 0;
    for (int p = 0; p<3; p++) {
        cout<< "delta is "<< deltat[p] << endl;
        outdata<< "delta is "<< deltat[p] << endl;
        
        for (int i = 0; i < 21; i ++) {
            for (x = i; x>0;x-=deltat[p]) {
                result3 = resulthis * (1/(1 + deltat[p]));
                resulthis = result3;
            }
            cout <<"i = " <<setw(2)<< i << "   result: " <<result3 << endl;
            outdata <<"i = " <<setw(2)<< i << "   result: " <<result3 << endl;
            result3 = 0;
            resulthis = 1;
        }
        cout << endl;
        outdata << endl;
    }
    
    outdata.close();
    
    return 0;
}

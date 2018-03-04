/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice2 for the week3 class on Thursday.
 *       Observe the Richardson Extrapolation Coefficient and
 *        Richardson Coefficient Without Known Truth
 *
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Feb. 8
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {
    ofstream outdata;
    outdata.open("output.txt");
    if(!outdata) {
        cerr << "ERROR" << endl;
        exit(1);
    }
    
    double h = pow(2,-4);
    double fx1 = 0;
    double fx2 = 0;
    double fx3 = 0;
    double fx4 = 0;
    double x = 1;
    double n1 = 0;
    double n2 = 0;
    for(; h>=pow(2,-10); h/=2) {
        cout << "h now is: " << h<< endl;
        fx1 = ((x + h)*(x + h)*(x + h) - x*x*x)/h;
        fx2 = ((x + 2*h)*(x + 2*h)*(x + 2*h) - x*x*x)/2/h;
        fx3 = -0.5 * (x + 2*h)*(x + 2*h)*(x + 2*h) / h - 1.5*x*x*x/h + 2*(x + h)*(x + h)*(x + h)/h;
        fx4 = ((x + 4*h)*(x + 4*h)*(x + 4*h) - x*x*x)/4/h;
        n1 = abs(3 - fx2) / abs(3 - fx1);
        n2 = (fx4 - fx2) / (fx2 - fx1);
        cout << "function 1(h)   h = " << h << "the result is: " <<fx1 << " the relative error is: " << abs(3 - fx1) / 3 * 100 << "%"<< endl;
        cout << "function 2(2h)  h = " << h << "the result is: " <<fx2 << " the relative error is: " << abs(3 - fx2) / 3 * 100 << "%"<< endl;
        cout << "function 3(2rd) h = " << h << "the result is: " <<fx3 << " the relative error is: " << abs(3 - fx3) / 3 * 100 << "%" << endl;
        cout << "Richardson Coefficient Without Known Truth h = " << h << " the result is : " <<n1 << endl;
        cout << "Richardson Extrapolation Coefficient       h = " << h << " the result is : " <<n2 << endl;
        cout << endl;
        
        outdata << "function 1(h)   h = " << h << "the result is: " <<fx1 << " the relative error is: " << abs(3 - fx1) / 3 * 100 << "%"<< endl;
        outdata << "function 2(2h)  h = " << h << "the result is: " <<fx2 << " the relative error is: " << abs(3 - fx2) / 3 * 100 << "%"<< endl;
        outdata << "function 3(2rd) h = " << h << "the result is: " <<fx3 << " the relative error is: " << abs(3 - fx3) / 3 * 100 << "%" << endl;
        outdata << "Richardson Coefficient Without Known Truth h = " << h << " the result is : " <<n1 << endl;
        outdata << "Richardson Extrapolation Coefficient       h = " << h << " the result is : " <<n2 << endl;
        outdata << endl;
        
        


    }
    outdata.close();
    return 0;
}

/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       B - Spline. I didn't understand the meaning of the matrix so I used a program in the stackoverflow to
 *      observe the B- Spline.
 *
 * AUTHOR :   https://stackoverflow.com/questions/25379422/b-spline-curves        START DATE :    18 Mar. 28
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
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;


#define N 5

void Spline(double x[N+1],double y[N+1], // input
            double A[N],double B[N],     // output
            double C[N],double D[N])     // output
{
    double w[N];
    double h[N];
    double ftt[N+1];
    
    for (int i=0; i<N; i++)
    {
        w[i] = (x[i+1]-x[i]);
        h[i] = (y[i+1]-y[i])/w[i];
    }
    
    ftt[0] = 0;
    for (int i=0; i<N-1; i++)
        ftt[i+1] = 3*(h[i+1]-h[i])/(w[i+1]+w[i]);
    ftt[N] = 0;
    
    for (int i=0; i<N; i++)
    {
        A[i] = (ftt[i+1]-ftt[i])/(6*w[i]);
        B[i] = ftt[i]/2;
        C[i] = h[i]-w[i]*(ftt[i+1]+2*ftt[i])/6;
        D[i] = y[i];
    }
}

void PrintSpline(double x[N+1],            // input
                 double A[N], double B[N], // input
                 double C[N], double D[N]) // input
{
    for (int i=0; i<N; i++)
    {
        cout << x[i] << " <= x <= " << x[i+1] << " : f(x) = ";
        cout << A[i] << "(x-" << x[i] << ")^3 + ";
        cout << B[i] << "(x-" << x[i] << ")^2 + ";
        cout << C[i] << "(x-" << x[i] << ")^1 + ";
        cout << D[i] << "(x-" << x[i] << ")^0";
        cout << endl;
    }
}




int main(int argc, const char * argv[]) {
    double x[6] = {1,2,3,4,5,6};
    double y[6] = {0,1,0,-1,0,1};
    double a[6] = {0};
    double b[6] = {0};
    double c[6] = {0};
    double d[6] = {0};
    Spline(x,y,a,b,c,d);
    PrintSpline(x,a,b,c,d);
    
    for(double i = 1; i<=6; i+=1e-3) {
        if (i<=2) {
            double temp = i - 1;
            cout << -0.5 * pow(temp, 3) + 1.5 * pow(temp, 1) << endl;
        }
        else if (i<=3) {
            double temp = i - 2;
            cout << 0.5 * pow(temp, 3) -1.5 * pow(temp,2) + 1 << endl;
        }
        
        else if (i<=4) {
            double temp = i - 3;
            cout << 0.5 * pow(temp, 3) -1.5 * pow(temp,1) << endl;
        }
        
        else if (i<=5) {
            double temp = i - 4;
            cout << -0.5 * pow(temp, 3) + 1.5 * pow(temp,2) -1 << endl;
        }
        else  {
            double temp = i - 5;
            cout <<temp << endl;
        }
    }
}




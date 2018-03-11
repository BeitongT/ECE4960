/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week7 class on Thursday.
 *      use bisection method to solve the foloowing nonlinear equation
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Mar. 8
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

bool cal_fun1(double x,double y) {
//    cout <<"fun1 " <<exp(x)-exp(y)<<endl;
    if (exp(x)-exp(y)>0)return 1;
    else return 0;
}

double cal_fun1_re(double x,double y) {
    return (exp(x)-exp(y));
}
bool cal_fun2(double x,double y) {
//    cout <<"fun2 " <<exp(x)+exp(y)-2<<endl;

    if(exp(x)+exp(y)-2>0) return 1;
    else return 0;
}
double cal_fun2_re(double x,double y) {
    return (exp(x)+exp(y)-2);
}

bool isEmpty_fun1(double xstart, double xend, double ystart, double yend) {
    if(cal_fun1(xstart, ystart) == 0 && cal_fun1(xstart, yend) == 0 && cal_fun1(xend, ystart) == 0 &&cal_fun1(xend, yend==0)) return 0;
    if(cal_fun1(xstart, ystart) == 1 && cal_fun1(xstart, yend) == 1 && cal_fun1(xend, ystart) == 1 &&cal_fun1(xend, yend==1)) return 0;
       return 1;
}

bool isEmpty_fun2(double xstart, double xend, double ystart, double yend) {
    if(cal_fun2(xstart, ystart) == 0 && cal_fun2(xstart, yend) == 0 && cal_fun2(xend, ystart) == 0 &&cal_fun2(xend, yend)==0) return 0;
    if(cal_fun2(xstart, ystart) == 1 && cal_fun2(xstart, yend) == 1 && cal_fun2(xend, ystart) == 1 &&cal_fun2(xend, yend)==1) return 0;
    return 1;
}

double* solver(double xstart, double xend, double ystart, double yend) {
    if(isEmpty_fun1(xstart, xend, ystart, yend)==0 || isEmpty_fun2(xstart, xend, ystart, yend)==0) return NULL;
    double xnew = (xstart + xend)/2;
    double ynew = (ystart + yend)/2;
    cout << xnew << " "<<ynew << endl;
    double *result = new double[2];

    result[0] = xnew;
    result[1] = ynew;
    if(abs(cal_fun1_re(xnew, ynew))<1e-7 && abs(cal_fun2_re(xnew, ynew))<1e-7) return result;
    else{
        delete [] result;
        result = solver(xstart,xnew,ystart,ynew);
        if (result != NULL) return result;
        result = solver(xnew,xend,ynew,yend);
        if (result != NULL) return result;
        result = solver(xnew,xend,ystart,yend);
        if (result != NULL) return result;
        result = solver(xstart,xend,ynew,yend);
        if (result != NULL) return result;
        }
    
    return NULL;
}



int main(int argc, const char * argv[]) {
    
    double result = 0;
    double start = -5;
    double end = 10;
    double half;
    cout << "bisection method" << endl;
    do{
        half =(start+end)/2;
        cout<< half<<endl;
        
        result =exp(half)-1;
        if (result>0) end = half;
        else start = half;
    }while (abs(result) > 1e-7 );
    
    cout << start << " "<<half<<" "<<end<<endl;
    cout << "exp("<<half<<") -1 is " << exp(half) -1<<endl<<endl;
    
    
    cout << "bisection method" << endl;
    double *re = new double[2];
    re = solver(-5,10,-5,10);
    cout <<"the final result is "<< re[0] << "  " << re[1]<<endl;
    delete [] re;
    
    
    
    
    
    return 0;
    
    
}



/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week4 class on Tuesday.
 *      This is to observe different methods to approximate the integration result.
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 FEB. 15
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


int main(int argc, const char * argv[]) {
    double result = 0;
    double start = -5;
    double end = 10;
    double half;
     do{
         half =(start+end)/2;
         cout<< half<<endl;

         result =exp(half)-1;
        if (result>0) end = half;
        else start = half;
     }while (abs(result) > 1e-7 );

    cout << start << " "<<half<<" "<<end<<endl;
    cout << "exp("<<half<<") -1 is " << exp(half) -1<<endl;
    return 0;
}



/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week6 class on Thursday.
 *       Backward substitution and minimal fill-in algorithm
 *
 *
 * AUTHOR :   Beitong Tian        START DATE : 18 Mar. 1
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <array>
#include <stdio.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;



int main(int argc, const char * argv[]) {
    
    MatrixXd A(5,5);
    A << 1,2,0,0,3, 4,5,6,0,0, 0,7,8,0,9, 0,0,0,10,0, 11,0,0,0,12;
    
    MatrixXd upper(5,5); /*For gaussian elimination*/
    upper = A;
    
    VectorXd B(5);
    B << 5,4,3,2,1;
    VectorXd Borigin(5);
    Borigin = B;
    
    VectorXi sequence(5); /*To record the origin row sequence*/
    sequence << 1,2,3,4,5;
    
    VectorXi Pivotnum(5); /*To record the fill in number*/
    Pivotnum<< 25,25,25,25,25;
    
    VectorXi choosePivot(5); /*To record the chosen pivot row*/
    
    MatrixXi BestChoice(5,2); /*To record the best Pivot for each row*/

    
    //start LU Factorization
    //find the best fill in plan
    for (int j = 0 ; j < 5; j++) {
        for (int i = j; i < 5; i++) {
            if(upper(i,j)!=0) {
                MatrixXd temp(5,5);
                temp = upper;
                temp.row(i).swap(temp.row(j));
                int count = 0;
                for(int p = j+1; p < 5; p++) {
                    if(temp(j,p)!=0) {
                        for(int q = j+1; q < 5;q++) {
                            if(temp(q,p)==0) count++;
                        }
                    }
                }
                if(count < Pivotnum(j)) {
                    Pivotnum(j) = count;
                    choosePivot(j) = i;
                }
            }
//debug information
//            cout <<"j is " <<j << endl;
//            cout <<"i is " <<i << endl;
//            cout << "upper(i,j) = "<<upper(i,j)<<endl;
//            if(upper(i,j)!=0){
//            cout <<Pivotnum[j]<< endl;
//            }
//            else cout << "pass" << endl;
//            cout << endl;
        }
        
        //Gaussian elimination
        int realI =choosePivot(j);
        BestChoice(j,0) = sequence(realI)-1;
        BestChoice(j,1) = j;
        
        upper.row(realI).swap(upper.row(j));
        B.row(realI).swap(B.row(j));
        
        sequence.row(realI).swap(sequence.row(j));

        for (int m = j+1; m< 5;m++) {
            if(upper(m,j)!=0) {
                double val = upper(m,j)/upper(j,j);
                upper.row(m) = upper.row(m) - val*upper.row(j);
                B.row(m) = B.row(m) - val*B.row(j);
            }
        }
    }
    //end
    
    //back substitution
    for (int a = 4;a >=0; a--) {
        for (int b = a -1; b >=0; b--) {
            if(upper(b,a)!=0) {
                double val = upper(b,a)/upper(a,a);
                upper.row(b) = upper.row(b) - val*upper.row(a);
                B.row(b) = B.row(b) - val*B.row(a);
            }
        }
    }
    //end
    

    //output other information.
    cout << "A is "<< endl;
    cout << A<< endl;
    cout << endl;
    cout << "B is "<< endl;
    cout << Borigin << endl;
    cout << endl;
    cout << "The best fill in choice is "<< endl;
    cout << "(x,y) " << endl;
    cout << BestChoice << endl;
    cout << endl;
    cout << "The best fill in numbers for each row are "<< endl;
    cout << Pivotnum << endl;
    cout << endl;

    //output my result
    VectorXd result(5);
    for (int i = 0; i< 5; i++)
    {
        result(i) = B(i)/upper(i,i);
    }
    cout << "my result is "<< endl;
    cout << result << endl;
    cout << endl;
    
    //output eigen result
    MatrixXd a(5,5);
    a << 1,2,0,0,3, 4,5,6,0,0, 0,7,8,0,9, 0,0,0,10,0, 11,0,0,0,12;
    VectorXd b(5);
    b << 5,4,3,2,1;
    VectorXd eigenResult = a.fullPivLu().solve(b);
    cout << "Eigen result is "<< endl;
    cout << eigenResult<< endl;
    cout << endl;

    //output matlab result
    VectorXd resultMatlab(5);
    resultMatlab << 0.2915,2.6301,-1.7194,0.2,-0.1839;
    cout << "Matlab result is "<< endl;
    cout << resultMatlab<< endl;
    
    return 0;
    
}


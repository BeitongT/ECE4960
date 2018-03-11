/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *       This is the HackPractice for the week7 class on Tuesday.
 *      Use jacobi method to calculate the solution. Observe the convergence conditions.
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Mar. 6
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include "matrix.hpp"
#include <Eigen/Dense>

using namespace std;

int main(int argc, const char * argv[]) {
    
//    This is the Jocobi solver
    double tempA[25] = {-4,1,0,0,1,4,-4,1,0,0,0,1,-4,1,0,0,0,1,-4,1,1,0,0,1,-4};
    Matrix *Aj = new Matrix(tempA,5,5);
    double tempB[5] = {1,0,0,0,0};
    Matrix *Bj = new Matrix(tempB,5,1);
    double tempC[25] = {1,1,1,1,1};
    Matrix *Cj = new Matrix(tempC,5,1);
    
    //Use D-1*b as the initial guess
    int count = Jacobi(Aj, Bj, Cj);
    printf("The total iteration time is: %d\n", count);
    printMatrix(Cj);
    cout << "||b-Ax||2 for iterative solver : " << calResidual(Aj, Bj->matrix, Cj)<<endl;
    
//This is the direct solver
    
    Eigen::MatrixXd A(5,5);
    A << -4,1,0,0,1,4,-4,1,0,0,0,1,-4,1,0,0,0,1,-4,1,1,0,0,1,-4;
    
    Eigen::MatrixXd upper(5,5); /*For gaussian elimination*/
    upper = A;
    
    Eigen::VectorXd B(5);
    B << 1,0,0,0,0;
    Eigen::VectorXd Borigin(5);
    Borigin = B;
    
    Eigen::VectorXi sequence(5); /*To record the origin row sequence*/
    sequence << 1,2,3,4,5;
    
    Eigen::VectorXi Pivotnum(5); /*To record the fill in number*/
    Pivotnum<< 25,25,25,25,25;
    
    Eigen::VectorXi choosePivot(5); /*To record the chosen pivot row*/
    
    Eigen::MatrixXi BestChoice(5,2); /*To record the best Pivot for each row*/
    
    
    //start LU Factorization
    //find the best fill in plan
    for (int j = 0 ; j < 5; j++) {
        for (int i = j; i < 5; i++) {
            if(upper(i,j)!=0) {
                Eigen::MatrixXd temp(5,5);
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
//    cout << "A is "<< endl;
//    cout << A<< endl;
//    cout << endl;
//    cout << "B is "<< endl;
//    cout << Borigin << endl;
//    cout << endl;
//    cout << "The best fill in choice is "<< endl;
//    cout << "(x,y) " << endl;
//    cout << BestChoice << endl;
//    cout << endl;
//    cout << "The best fill in numbers for each row are "<< endl;
//    cout << Pivotnum << endl;
//    cout << endl;
    
    //output my result
    Eigen::VectorXd result(5);
    for (int i = 0; i< 5; i++)
    {
        result(i) = B(i)/upper(i,i);
    }
    cout << endl;
    cout << "direct solver result is "<< endl;
    cout << result << endl;
    
    Eigen::VectorXd productTemp(5); /*To record the origin row sequence*/
    productTemp = A*result;
    Eigen::VectorXd subTemp(5); /*To record the origin row sequence*/
    subTemp = Borigin - productTemp;
    double residual = subTemp.norm();
    cout << "||b-Ax||2 for direct solver : " << residual<<endl;

    Eigen::MatrixXd D(5,5);
    D <<-4,0,0,0,0,0,-4,0,0,0,0,0,-4,0,0,0,0,0,-4,0,0,0,0,0,-4;
    
    Eigen::MatrixXd upperPluslower(5,5);

    upperPluslower = (A - D);
    cout << upperPluslower<<endl;
    
    Eigen::MatrixXd check(5,5);
    check =D.inverse()*upperPluslower;
    cout << check<< endl;
    cout << "||D-1(L+U)|| first norm : " << check.colwise().lpNorm<1>().maxCoeff()<<endl;

    cout << "||D-1(L+U)|| infinite norm : " << check.rowwise().lpNorm<1>().maxCoeff()<<endl;

    Eigen::MatrixXd upperMatrix(5,5);
    upperMatrix = (A - D).triangularView<Eigen::Upper>();
//    cout << upperMatrix;
    Eigen::MatrixXd lowerMatrix(5,5);
    lowerMatrix = (A - D).triangularView<Eigen::Lower>();
    Eigen::MatrixXd check2(5,5);
    check2 = (D-lowerMatrix).inverse()*upperMatrix;
    cout << "||(D-L)-1*U|| first norm : " << check2.colwise().lpNorm<1>().maxCoeff()<<endl;
    
    cout << "||(D-L)-1*U|| infinite norm : " << check2.rowwise().lpNorm<1>().maxCoeff()<<endl;

    
    return 0;
}



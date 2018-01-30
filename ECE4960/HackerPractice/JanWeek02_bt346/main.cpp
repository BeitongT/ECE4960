//
//  main.cpp
//  My first C++ project
//
//  Created by Beitong Tian on 1/25/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include <iostream>
#include <math.h>

int main(int argc, const char * argv[]) {
    double a = 1e-20;
    double b = 1e3;
    double c = 1e3;
    double x1_1 = 0;
    double x1_2 = 0;
    double x2_1 = 0;
    double x2_2 = 0;
    double x3_1 = 0;
    double x3_2 = 0;
    x1_1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    x1_2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    x2_1 = (-2 * c) / (-b + sqrt(b * b - 4 * a * c));
    x2_2 = (-2 * c) / (-b - sqrt(b * b - 4 * a * c));
    x3_1 = - (c / b);
    x3_2 = -(b / a) + (c / b);
    double check1_1 = 0;
    double check1_2 = 0;
    double check2_1 = 0;
    double check2_2 = 0;
    double check3_1 = 0;
    double check3_2 = 0;
    
    check1_1 = x1_1 * x1_1 * a + x1_1 * b + c;
    check1_2 = x1_2 * x1_2 * a + x1_2 * b + c;
    check2_1 = x2_1 * x2_1 * a + x2_1 * b + c;
    check2_2 = x2_2 * x2_2 * a + x2_2 * b + c;
    check3_1 = x3_1 * x3_1 * a + x3_1 * b + c;
    check3_2 = x3_2 * x3_2 * a + x3_2 * b + c;
    
    std::cout  << "x1_1: " << x1_1 << "\n" << "check1_1: " << check1_1 << "\n";
    std::cout  << "x1_2: " << x1_2 << "\n" << "check1_2: " << check1_2 << "\n";
    std::cout  << "x2_1: " << x2_1 << "\n" << "check2_1: " << check2_1 << "\n";
    std::cout  << "x2_2: " << x2_2 << "\n" << "check2_2: " << check2_2 << "\n";
    std::cout  << "x3_1: " << x3_1 << "\n" << "check3_1: " << check3_1 << "\n";
    std::cout  << "x3_2: " << x3_2 << "\n" << "check3_2: " << check3_2 << "\n";

    return 0;
}


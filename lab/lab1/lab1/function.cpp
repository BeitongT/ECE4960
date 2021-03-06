//
//  function.cpp
//  lab1
//
//  Created by Beitong Tian on 2/11/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "header.h"
extern FILE * pFile1;
extern FILE * pFile2;

//using the 2 power to detect the unsigned int overflow. default result 0
void overflow_unsigned_int_multi(int x) {
    fprintf(pFile2,"The max unsigned int value is %u\n", UINT_MAX);
    unsigned int result = 1;
    for (int i = 1; i <= x; i ++) {
        if (2 > (UINT_MAX / result)) {
            fprintf(pFile2,"The overflow happens when 2^%u \n", i);
            result *= 2;
            if (result == index_result) {
                fprintf(pFile2,"The overflow result is  %u\n" , result);
                throw "unsigned integer multiply overflow error";
            }
            break;
        }
        result *= 2;
    }
    fprintf(pFile2,"The result is  %u\n.", result);
}

//using the Fibonacci sequence to detect the unsigned int overflow. default result 512559680
void overflow_unsigned_int_add(int x) {
    fprintf(pFile2,"The max unsigned int value is %u\n", UINT_MAX);
    unsigned int result[2] = {1, 1};
    unsigned int buffer = 1;
    for (int i = 1; i <= x; i ++) {
        if ( result[0] + result[1] < result[0] && result[0] + result[1] < result[1]) {
            fprintf(pFile2,"The overflow happens when %u+%u\n", result[0], result[1]);
            result[0] = result[0] + result[1];
            if (result[0] == add_result) {
            fprintf(pFile2,"The overflow result is %u\n" , result[0]);
            throw "unsigned integer add overflow error";
            }
            break;

        }
        result[0] = result[0] + result[1];
        //        fprintf(pFile2,"the result is %u\n", result[0]);
        buffer = result[1];
        result[1] = result[0];
        result[0] = buffer;
    }
}

//using the 2 power to detect the signed int overflow. default result -2147483648
void overflow_signed_int_multi(int x) {
    fprintf(pFile2,"The max signed int value is %d\n", INT_MAX);
    int result = 1;
    for (int i = 1; i <= x; i ++) {
        if (2 > (INT_MAX / result)) {
            fprintf(pFile2,"The overflow happens when 2^%u \n", i);
            result *= 2;
            if (result == -signed_index_result) {
            fprintf(pFile2,"The overflow result is  %d\n" , result);
            throw "signed integer multiply overflow error";
            }
        }
        result *= 2;
    }
    fprintf(pFile2,"The result is  %d\n.", result);
}


//using the Fibonacci sequence to detect the signed int overflow. default result -1323752223
void overflow_signed_int_add(int x) {
    fprintf(pFile2,"The max signed int value is %d\n", INT_MAX);
    int result[2] = {1, 1};
    int buffer = 1;
    //    fprintf(pFile2,"the result is %d\n", result[0]);
    //    fprintf(pFile2,"the result is %d\n", result[1]);
    for (int i = 1; i <= x; i ++) {
        if ( result[0] + result[1] < result[0] && result[0] + result[1] < result[1]) {
            fprintf(pFile2,"The overflow happens when %d+%d\n", result[0], result[1]);
            result[0] = result[0] + result[1];
            if (result[0] == -signed_add_result) {
            fprintf(pFile2,"The overflow result is %d\n" , result[0]);
            throw "signed integer add overflow error";
            }
        }
        result[0] = result[0] + result[1];
        //        fprintf(pFile2,"the result is %d\n", result[0]);
        buffer = result[1];
        result[1] = result[0];
        result[0] = buffer;
    }
}


//because divide by zero will cause a compiler error, so we use this method to detect the divided by zero
int zero_devided_overflow(int x, int y) {
    if (y == 0) {
        fprintf(pFile2,"You want to devide %d by %d\n" ,x, y);
        throw "this will cause a devide by zero error";
    }
    return x / y;
    
}

//using 2 power to detect the float overflow. Default result inf
void overflow_float_multi(int x) {
    fprintf(pFile2,"The max signed float value is %e\n", __FLT_MAX__);
    float result = 1;
    for (int i = 1; i <= x; i ++) {
        result *= 2;
        if (isinf(result)) {
            fprintf(pFile2,"The overflow happens when 2^%u \n", i);
            fprintf(pFile2,"The overflow result is  %f\n" , result);
            throw "float multiply overflow error";
        }
    }
    fprintf(pFile2,"The result is  %f\n.", result);
}

//create and detect the inf adn ninf
float inf_create() {
    return 1.0/0;
}

bool inf_detect(float x) {
    return isinf(x) && x > 0;
}

bool ninf_detect(float x) {
    return isinf(x) && x < 0;
}

float ninf_create() {
    return -1.0/0;
}

//observe the infinity properties
void observe_inf_ninf() {
    float inf = inf_create();
    float ninf = ninf_create();
    float result_1dx_inf = 1 / inf;
    float result_1dx_ninf = 1 / ninf;
    float result_sinx_inf = sin(inf);
    float result_sinx_ninf = sin(ninf);
    float result_expx_inf = exp(inf);
    float result_expx_ninf = exp(ninf);
    fprintf(pFile2,"The result of 1/inf is %f\n", result_1dx_inf);
    fprintf(pFile2,"The result of 1/ninf is %f\n", result_1dx_ninf);
    fprintf(pFile2,"The result of sin(inf) is %f\n", result_sinx_inf);
    fprintf(pFile2,"The result of sin(ninf) is %f\n", result_sinx_ninf);
    fprintf(pFile2,"The result of exp(inf) is %f\n", result_expx_inf);
    fprintf(pFile2,"The result of exp(ninf) is %f\n", result_expx_ninf);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"Here are the propagation and interaction between INF and NINF\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"INF  +  INF is %f\n", inf + inf);
    fprintf(pFile2,"INF  -  INF is %f\n", inf - inf);
    fprintf(pFile2,"INF  *  INF is %f\n", inf * inf);
    fprintf(pFile2,"INF  /  INF is %f\n", inf / inf);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"NINF + NINF is %f\n", ninf + ninf);
    fprintf(pFile2,"NINF - NINF is %f\n", ninf - ninf);
    fprintf(pFile2,"NINF * NINF is %f\n", ninf * ninf);
    fprintf(pFile2,"NINF / NINF is %f\n", ninf / ninf);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"INF  + NINF is %f\n", inf + ninf);
    fprintf(pFile2,"INF  - NINF is %f\n", inf - ninf);
    fprintf(pFile2,"INF  * NINF is %f\n", inf * ninf);
    fprintf(pFile2,"INF  / NINF is %f\n", inf / ninf);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"NINF +  INF is %f\n", ninf + inf);
    fprintf(pFile2,"NINF -  INF is %f\n", ninf - inf);
    fprintf(pFile2,"NINF *  INF is %f\n", ninf * inf);
    fprintf(pFile2,"NINF /  INF is %f\n", ninf / inf);
    fprintf(pFile2,"\n");
    
    
}


//create nan and detect nan
float nan_create() {
    //    return sqrt(-1);
    return inf_create()-inf_create();
}

bool detect_nan (float x) {
    return isnan(x);
}

//observe the nan
void observe_nan() {
    float nan = nan_create();
    float inf = inf_create();
    float ninf = ninf_create();
    float result_1dx_nan = 1 / nan;
    float result_sinx_nan = sin(nan);
    float result_expx_nan = exp(nan);
    fprintf(pFile2,"The result of 1/nan is %f\n", result_1dx_nan);
    fprintf(pFile2,"The result of sin(nan) is %f\n", result_sinx_nan);
    fprintf(pFile2,"The result of exp(nan) is %f\n", result_expx_nan);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"Here are the propagation and interaction between NAN and NAN\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"NAN  +  NAN is %f\n", nan + nan);
    fprintf(pFile2,"NAN  -  NAN is %f\n", nan - nan);
    fprintf(pFile2,"NAN  *  NAN is %f\n", nan * nan);
    fprintf(pFile2,"NAN  /  NAN is %f\n", nan / nan);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"NAN  +  INF is %f\n", nan + inf);
    fprintf(pFile2,"NAN  -  INF is %f\n", nan - inf);
    fprintf(pFile2,"NAN  *  INF is %f\n", nan * inf);
    fprintf(pFile2,"NAN  /  INF is %f\n", nan / inf);
    fprintf(pFile2,"\n");
    
    fprintf(pFile2,"NAN  +  NINF is %f\n", nan + ninf);
    fprintf(pFile2,"NAN  -  NINF is %f\n", nan - ninf);
    fprintf(pFile2,"NAN  *  NINF is %f\n", nan * ninf);
    fprintf(pFile2,"NAN  /  NINF is %f\n", nan / ninf);
    fprintf(pFile2,"\n");
    
    
}

//create and detect signed zero

float create_pos_zero() {
    return 1/inf_create();
}

bool detect_pos_zero(float x) {
    return isinf(1.0/x);
}


float create_neg_zero() {
    return 1/ninf_create();
}

bool detect_neg_zero(float x) {
    return isinf(-1.0/x);
}


void observe_signed_zero(){
    float result = 1;
    int i = 1;
    fprintf(pFile2,"Test log(x) when x -> 0+\n");
    while(!(result == 0)) {
        result/=10;
        fprintf(pFile2,"The result for log(10^(-%d)) is %f\n", i, log(result));
        i ++;
    }
    
    fprintf(pFile2,"\n");
    
    result = -1;
    i = 1;
    fprintf(pFile2,"Test log(x) when x -> 0-\n");
    while(!(result == 0)) {
        result/=10;
        fprintf(pFile2,"The result for log(10^(-%d)) is %f\n", i, log(result));
        i ++;
    }
    fprintf(pFile2,"\n");
    
    
    result = 1;
    i = 1;
    fprintf(pFile2,"Test sinx/x when x -> 0+\n");
    while(!(result == 0)) {
        result/=10;
        fprintf(pFile2,"The result for sin(10^(-%d))/ 10^(-%d) is %f\n", i, i, sin(result)/result);
        i ++;
    }
    fprintf(pFile2,"\n");
    
    
    result = -1;
    i = 1;
    fprintf(pFile2,"Test sinx/x when x -> 0-\n");
    while(!(result == 0)) {
        result/=10;
        fprintf(pFile2,"The result for sin(10^(-%d))/ 10^(-%d) is %f\n", i, i, sin(result)/result);
        i ++;
    }
    fprintf(pFile2,"\n");
    
    result = -1;
    i = 1;
    fprintf(pFile2,"Test sinx/|x| when x -> 0-\n");
    while(!(result == 0)) {
        result/=10;
        fprintf(pFile2,"The result for sin(10^(-%d))/ |10^(-%d)| is %f\n", i, i, sin(result)/abs(result));
        i ++;
    }
    fprintf(pFile2,"\n");
    
}


//testing the floating underflow to find if this system will use denormals to land to zero softly
void floating_underflow() {
    
    float x = 1.23456 * mypow(10,-20) ;
    float y = 10;
    for (int i = 0; i < 50 ; i ++) {
        x = x / y;
        fprintf(pFile2,"x / y is %e\n", x);
    }
    
    fprintf(pFile2,"\n");
    x = 1.0;
    y = 10.0;
    for (int i = 0; i > -50 ; i --) {
        x = x / y;
        fprintf(pFile2,"x is %e, the result is %e\n", x, sin(1.23456789012345*x)/ x);
    }
    
    fprintf(pFile2,"\n");
    
    double a = 1.6875 * mypow(2,-1020);
    double b = 1.625 * mypow(2,-1020);
    
    for (int i = 0; i <60 ; i ++) {
        a = a / 2.0;
        b = b / 2.0;
        fprintf(pFile2,"i = %d, x - y is %e\n", -1020-i, a - b);
    }
    fprintf(pFile2,"\n");
    
    a = 1.6875 * mypow(2,-1020);
    b = 1.625 * mypow(2,-1020);
    fprintf(pFile2,"Now we test x - y\n");
    fprintf(pFile2,"The x value is %e\n", a);
    fprintf(pFile2,"The y value is %e\n", b);
    
    if (a - b == 0) {
        fprintf(pFile2,"x != y, but x - y = 0.\n");
    }
    
    else {
        fprintf(pFile2,"x != y, and x - y != 0.\n");
        throw "Using denormals";
    }
    
    fprintf(pFile2,"\n");
    
    
    
}



// pi approximation
//I use the long double to do it.
//If we need to use only double to do it. Shall we write add , multiply function to achieve it.

void pi_approximation() {
    long double pi = 1;
    
    pi = 4.0 * (12.0 * cal_single(49) + 32.0 * cal_single(57) - 5.0 * cal_single(239) + 12.0 * cal_single(110443));
    
    fprintf(pFile2,"pi now is    %.30Lf\n", pi);
    fprintf(pFile2,"pi should be %.30f\n", 3.14159265358979323846264338327);
    
}

double cal_single(int x) {
    long double result = 1.0/x;
    for (long i = 0; i<10; i++) {
        result =  result + mypow(-1.0,i%2+1) * mypow(1.0/x,(2.0*(i+1.0)+1.0)) / (2.0*(i+1.0)+1.0);
    }
    fprintf(pFile2,"result now is %.30Lf\n", result);
    return result;
}


//power function
double mypow(double x, int y)
{
    double temp;
    if( y == 0)
        return 1;
    temp = mypow(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
    {
        if(y > 0)
            return x*temp*temp;
        else
            return (temp*temp)/x;
    }
}


//
//  header.h
//  lab1
//
//  Created by Beitong Tian on 2/11/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#ifndef header_h
#define header_h
#include <iostream>
#include <math.h>
#include <cfenv>
#include <limits>
#include <iomanip>
#include <fstream>
#include <stdio.h>
using namespace std;

//define some constant for overflow detection
#define index_result 0
#define add_result 512559680
#define signed_index_result 2147483648
#define signed_add_result 1323752223

//INTEGER OVERFLOW DETECTION
void overflow_unsigned_int_multi(int);
void overflow_signed_int_multi(int);
void overflow_unsigned_int_add(int);
void overflow_signed_int_add(int);

//ZERO DIVIDE ZERO DETECTION
int zero_devided_overflow(int,int);

//FLOAT OVERFLOW DETECTION
void overflow_float_multi(int);

//INFINITY CREATE DETECT AND PROPAGATION
float inf_create();
bool inf_detect(float x);
float ninf_create();
bool ninf_detect(float x);
void observe_inf_ninf();

//NAN CREATE DETECT AND PROPAGATION
float nan_create();
void observe_nan();
bool detect_nan (float x);

//SIGNED ZERO CREATE DETECT AND PROPAGATION
float create_neg_zero();
bool detect_neg_zero(float x);
float create_pos_zero();
bool detect_pos_zero(float x);
void observe_signed_zero();

//FLOATING UNDERFLOW
void floating_underflow();

//PI APPROXIMATION
void pi_approximation();
double cal_single(int x);
double cal_single_2(int x);

//EXCEPTION
bool handle_exception(void (*f)());
bool handle_exception(void (*f)(int),int para);
bool handle_exception(void (*f)(int,int),int,int);
bool handle_exception(int (*f)(int,int),int, int);

//POWER
double mypow(double x, int y);
#endif /* header_h */

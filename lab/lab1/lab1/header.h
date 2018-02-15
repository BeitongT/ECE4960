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


void overflow_unsigned_int_multi(int);
void overflow_signed_int_multi(int);
void overflow_unsigned_int_add(int);
void overflow_signed_int_add(int);
int zero_devided_overflow(int,int);
int zero_devided_overflow_strange(int, int);
void overflow_float_multi(int);
void overflow_float_multi_double(int x);
float inf_create();
bool inf_detect(float x);

float ninf_create();
bool ninf_detect(float x);

void observe_inf_ninf();
float nan_create();
void observe_nan();
bool detect_nan (float x);
float create_neg_zero();
bool detect_pos_zero(float x);
bool detect_neg_zero(float x);

float create_pos_zero();
void observe_signed_zero();
void floating_underflow();
void pi_approximation();
double cal_single(int x);
double cal_single_2(int x);
void zero_devided_overflow_new(int);

bool handle_exception(void (*f)());
bool handle_exception(void (*f)(int),int para);
bool handle_exception(void (*f)(int,int),int,int);
bool handle_exception(int (*f)(int,int),int, int);
double mypow(double x, double y);
#endif /* header_h */
//
//  main.cpp
//  lab1
//
//  Created by Beitong Tian on 2/10/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//


#include "header.h"
bool INT_OVERFLOW;
bool DIVIDE_ZERO;
bool FLOAT_OVERFLOW;
bool INFINITY_CREATE;
bool NAN_CREATE;
bool SIGNED_ZERO;
bool FLOATING_UNDERFLOW;
FILE * pFile1;
FILE * pFile2;

int main(int argc, const char * argv[]) {
    
    pFile1 = fopen ("IEEE_compliance_report.txt","w");
    pFile2 = fopen ("Detailed Log.txt","w");
    
    fprintf(pFile1,"OS: MAC OS; LANGUAGE: C++; CODING WITH XCODE\n");
    
    //INTEGER OVERFLOW DETECTION
    fprintf(pFile2,"###########Detect the integer overflow.###########\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"#Using 2 index to detect the unsigned int overflow");
    INT_OVERFLOW = handle_exception(overflow_unsigned_int_multi, 100);
    fprintf(pFile2,"\n");
    fprintf(pFile2,"#Using 2 index to detect the signed int overflow");
    INT_OVERFLOW &= handle_exception(overflow_signed_int_multi, 100);
    fprintf(pFile2,"\n");
    fprintf(pFile2,"#Using Fibonacci sequence to detect the unsigned int overflow");
    INT_OVERFLOW &= handle_exception(overflow_unsigned_int_add, 10000);
    fprintf(pFile2,"\n");
    fprintf(pFile2,"#Using Fibonacci sequence to detect the signed int overflow");
    INT_OVERFLOW &= handle_exception(overflow_signed_int_add, 10000);
    fprintf(pFile2,"\n");
    if (INT_OVERFLOW) {
        fprintf (pFile1,"Detect the Integer Overflow             PASS\n");
    }
    else fprintf(pFile1,"Detect the Integer Overflow             WRONG\n");
    fprintf(pFile2,"\n");

    
    
    
    //ZERO DIVIDE ZERO DETECTION
    fprintf(pFile2,"###########Detect the Integer Divide Zero.###########\n");
    
    DIVIDE_ZERO = handle_exception(zero_devided_overflow, 10,0);
    if (DIVIDE_ZERO) {
        fprintf(pFile1,"Detect Integer Divide Zero              PASS\n");
    }
    else fprintf(pFile1,"Detect Integer Divide Zero             WRONG\n");
    fprintf(pFile2,"\n");

    
    
    //FLOAT OVERFLOW DETECTION
    fprintf(pFile2,"###########Detect the float overflow.###########\n");
    FLOAT_OVERFLOW = handle_exception(overflow_float_multi, 10000);
    if (FLOAT_OVERFLOW) {
        fprintf(pFile1,"Detect float overflow                   PASS\n");
    }
    else fprintf(pFile1,"Detect float overflow                  WRONG\n");
    fprintf(pFile2,"\n");

    
    
    //INFINITY CREATE DETECT AND PROPAGATION
    fprintf(pFile2,"###########INF and NINF###########\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"the result of create inf is %f\n", inf_create());
    fprintf(pFile2,"Is it Infinity? %s\n", inf_detect(inf_create()) ? "yes" : "no" );
    
    fprintf(pFile2,"\n");
    fprintf(pFile2,"the result of create ninf is %f\n", ninf_create());
    fprintf(pFile2,"Is it NInfinity? %s\n", ninf_detect(ninf_create()) ? "yes" : "no" );
    fprintf(pFile2,"\n");
    INFINITY_CREATE = inf_detect(inf_create()) && ninf_detect(ninf_create());
    if(INFINITY_CREATE) {
        observe_inf_ninf();
    }
    if (INFINITY_CREATE) {
        fprintf(pFile1,"Create inf and ninf                     PASS\n");
//        fprintf(pFile1,"After observing the result, all the result are like the default results.\n");

    }
    else fprintf(pFile1,"Create inf and ninf                    WRONG\n");
    fprintf(pFile2,"\n");

    
    
    //NAN CREATE DETECT AND PROPAGATION
    fprintf(pFile2,"###########NAN###########\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"the result of create nan is %f\n", nan_create());
    fprintf(pFile2,"Is it NAN? %s\n", detect_nan(nan_create()) ? "yes" : "no" );
    fprintf(pFile2,"\n");
    NAN_CREATE = detect_nan(nan_create());
    
    if (NAN_CREATE) {
        observe_nan();
    }
    
    if (NAN_CREATE) {
        fprintf(pFile1,"Create nan                              PASS\n");
    }
    else fprintf(pFile1,"Create nan                             WRONG\n");
    fprintf(pFile2,"\n");

    
    
    
    //SIGNED ZERO CREATE DETECT AND PROPAGATION
    //    ??signed zero
    fprintf(pFile2,"###########SIGNED ZERO###########\n");
    fprintf(pFile2,"\n");
    fprintf(pFile2,"the result of create positive zero is %f\n", create_pos_zero());
    fprintf(pFile2,"Is it Positive ZERO? %s\n", detect_pos_zero(create_pos_zero()) ? "yes" : "no" );
    fprintf(pFile2,"\n");
    fprintf(pFile2,"the result of create negative zero is %f\n", create_neg_zero());
    fprintf(pFile2,"Is it Negative ZERO? %s\n", detect_neg_zero(create_neg_zero()) ? "yes" : "no" );
    fprintf(pFile2,"\n");
    SIGNED_ZERO = detect_pos_zero(create_pos_zero()) && detect_neg_zero(create_neg_zero());
    if(SIGNED_ZERO) {
        observe_signed_zero();
    }
    if (SIGNED_ZERO) {
        fprintf(pFile1,"Create positive zero and negative zero  PASS\n");
//        fprintf(pFile1,"After observing the result, all the result are like the default results.\n");

    }
    else fprintf(pFile1,"Create positive zero and negative zero  WRONG\n");
    fprintf(pFile2,"\n");

    
    //FLOATING UNDERFLOW
    fprintf(pFile2,"###########FLOATING UNDERFLOW###########\n");
    fprintf(pFile2,"\n");
    FLOATING_UNDERFLOW = handle_exception(floating_underflow);
    if (FLOATING_UNDERFLOW) {
        fprintf(pFile1,"Denormals with soft landing             PASS\n");
    }
    else fprintf(pFile1,"Denormals with soft landing            WRONG\n");
    fprintf(pFile2,"\n");

    //FLOATING UNDERFLOW
    fprintf(pFile2,"###########PI CALCULATION###########\n");
    
    
    //PI APPROXIMATION
    pi_approximation();
    
    fclose (pFile1);
    fclose (pFile2);
    
    return 0 ;
    
    
}


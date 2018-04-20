/*H**********************************************************************
 * FILENAME :  main.cpp
 *
 * DESCRIPTION :
 *      Lab4
 *
 * AUTHOR :   Beitong Tian        START DATE :    18 Apr. 16
 *
 * PLATFORM : C++ in MAC OS  IDE: Xcode
 *
 *H*/




#include "ForwardEuler.hpp"
#include "RK4.hpp"
#include "RK34.hpp"

int main(int argc, const char * argv[]) {

    //test function
    forwardEuler_Test(5.0, 1.0, 2.0);
    RK4_test(5.0, 1.0, 2.0);
    RK34_test(5.0, 1.0, 2.0);

    //RC
    Vector2d initialRC;
    initialRC << 0.0, 0.0;
    forwardEulerRC(100 * 1e-9, 1e-9, initialRC);
    forwardEulerRC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    RK4_RC(100 * 1e-9, 1e-9, initialRC);
    RK4_RC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    RK34_RC(100 * 1e-9, 1e-9, initialRC);
    RK34_RC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    //EKV model
    Vector2d initialEKV;
    initialRC << 2.5, 2.5;
    forwardEulerEKV(100 * 1e-9, 1e-9, initialEKV);
    forwardEulerEKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);
    
    RK4_EKV(100 * 1e-9, 1e-9, initialEKV);
    RK4_EKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);
    
    RK34_EKV(100 * 1e-9, 1e-9, initialEKV);
    RK34_EKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);


    return 0;
}






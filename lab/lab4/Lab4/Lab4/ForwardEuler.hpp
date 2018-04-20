//
//  ForwardEuler.hpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#ifndef ForwardEuler_hpp
#define ForwardEuler_hpp

#include "ODEhelper.hpp"

void forwardEuler_Test(double t,double deltaT,double last);

//forwardEulerRC  => solution vector rank = 2

void forwardEulerRC(double t,double deltaT,Vector2d last);


//forwardEulerEKV  => solution vector rank = 2

void forwardEulerEKV(double t,double deltaT,Vector2d last);


#endif /* ForwardEuler_hpp */

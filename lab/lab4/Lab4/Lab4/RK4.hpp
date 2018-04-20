//
//  RK4.hpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#ifndef RK4_hpp
#define RK4_hpp

#include "ODEhelper.hpp"


//RK4_test  => solution vector rank = 1
void RK4_test(double t, double deltaT, double last);
//RK4_RC  => solution vector rank = 2
void RK4_RC(double t, double deltaT, Vector2d last);
//RK4_EKV  => solution vector rank = 2
void RK4_EKV(double t, double deltaT, Vector2d last);

#endif /* RK4_hpp */

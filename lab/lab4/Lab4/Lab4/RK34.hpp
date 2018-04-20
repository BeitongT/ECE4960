//
//  RK34.hpp
//  Lab4
//
//  Created by Beitong Tian on 4/20/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#ifndef RK34_hpp
#define RK34_hpp

#include "ODEhelper.hpp"

/* RK34 with time adaption Method => RK4 method */
//RK34_test  => solution vector rank = 1
void RK34_test(double t, double deltaT, double last);

void RK34_RC(double t, double deltaT, Vector2d last);

void RK34_EKV(double t, double deltaT, Vector2d last);


#endif /* RK34_hpp */

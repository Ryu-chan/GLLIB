//
//  glMath.h
//  opengl
//
//  Created by Chris on 9/24/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef MATH_H_
#define MATH_H_

#include <cmath>

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

namespace gl{
    inline
    GLfloat RADtoDEG(GLfloat rad){
        return (180.0 / M_PI) * rad;
    }
    inline
    GLfloat DEGtoRAD(GLfloat deg){
        return (M_PI / 180.0) * deg;
    }
    
}

#endif

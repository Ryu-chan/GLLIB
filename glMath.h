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
#include "glVec.h"

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
    
    
    inline
    GLfloat dot( const vec4& u, const vec4& v ) {
        return u.x*v.x + u.y*v.y + u.z*v.z + u.w+v.w;
    }
    
    inline
    GLfloat length( const vec4& v ) {
        return std::sqrt( dot(v,v) );
    }
    
    inline
    vec4 normalize( const vec4& v ) {
        return v / length(v);
    }
    
    inline
    vec4 cross(const vec4& a, const vec4& b )
    {
        return vec4(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
            1
        );
    }
    
    inline
    GLfloat norm_sqr(const vec4& v){
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }
    
    inline
    GLfloat norm(const vec4& v){
        return sqrt(norm_sqr(v));
    }
    
    inline
    vec4* normal(vec4* p1,vec4* p2,vec4* p3){
        vec4* n = new vec4(
           (p2->y - p1->y)*(p3->z - p1->z) - (p2->z - p1->z)*(p3->y - p1->y),
           (p2->z - p1->z)*(p3->x - p1->x) - (p2->x - p1->x)*(p3->z - p1->z),
           (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x),
            0
        );
        return n;
    }
}

#endif

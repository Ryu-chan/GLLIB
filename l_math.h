//
//  l_math.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _L_MATH_H_
#define _L_MATH_H_

#define X 0
#define Y 1
#define Z 2
#define W 3

#include <math.h>
#include "l_util.h"

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

float RADtoDEG(float rad){
    return (180.0 / M_PI) * rad;
}

float DEGtoRAD(float deg){
    return (M_PI / 180.0) * deg;
}


float dot( float* u, float* v ) {
    return
        u[X] * v[X] +
        u[Y] * v[Y] +
        u[Z] * v[Z] +
        u[W] + v[W];
}

float length( float* v ) {
    return sqrt(dot(v,v));
}

void normalize( float* v ) {
    float div = length(v);
    v[X] /= div;
    v[Y] /= div;
    v[Z] /= div;
    v[W] /= div;
}

float* cross(float* a, float* b )
{
    float* v = (float*)xmalloc(4*sizeof(float));
    v[X] = a[Y] * b[Z] - a[Z] * b[Y];
    v[Y] = a[Z] * b[X] - a[X] * b[Z];
    v[Z] = a[X] * b[Y] - a[Y] * b[X];
    v[W] = 1;
    return v;
}

float norm_sqr(float* v){
    return v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z];
}

float norm(float* v){
    return sqrt(norm_sqr(v));
}

float* normal(float* p1,float* p2,float* p3){
    float* v = (float*)xmalloc(4*sizeof(float));
    v[X] = (p2[Y]-p1[Y]) * (p3[Z]-p1[Z]) - (p2[Z]-p1[Z]) * (p3[Y]-p1[Y]);
    v[Y] = (p2[Z]-p1[Z]) * (p3[X]-p1[X]) - (p2[X]-p1[X]) * (p3[Z]-p1[Z]);
    v[Z] = (p2[X]-p1[X]) * (p3[Y]-p1[Y]) - (p2[Y]-p1[Y]) * (p3[X]-p1[X]);
    v[W] = 0;
    return v;
}


#endif

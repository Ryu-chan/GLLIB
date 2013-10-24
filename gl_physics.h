//
//  gl_physics.h
//  opengl
//
//  Created by Chris on 10/22/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_PHYSICS_H_
#define _GL_PHYSICS_H_

#include "gl_vec.h"

typedef struct s_line{
    point first;
    point second;
} line;
typedef struct s_plane{
    point pt;
    point normal;
} plane;

line makeLine(point a,point b){
    line l;
    l.first = a;
    l.second = b;
    return l;
}
plane makePlane(point pt,point normal){
    plane p;
    p.pt = pt;
    p.normal = normal;
    return p;
}
plane makePlane(point p1,point p2,point p3){
    plane p;
    p.pt = p1;
    p.normal = normal(p1,p2,p3);
    return p;
}

void randomDisplacement(GLfloat magnitude, vec4& v)
{
	GLfloat angle = ((GLfloat)rand()/(GLfloat)RAND_MAX) * (2 * M_PI);
    GLfloat a = magnitude * cos(angle);
	GLfloat b = magnitude * sin(angle);
    GLfloat c = magnitude * cos(angle)*sin(angle);
    
    v[X] = a/50.0;
    v[Y] = b/50.0;
    v[Z] = c/50.0;
    v[W] = 0;
    
}

char intersect2_SEG_SEG(point p0, point p1, point p2, point p3, float *x, float *y)
{
    //Algorithm inspired by vector cross product magnitude algortihm
    
    point scalar = vec_4(
         //scalar 1
         p1[X] - p0[X],
         p1[Y] - p0[Y],
         //scalar 2
         p3[X] - p2[X],
         p3[Y] - p2[Y]
    );
    
    float
    s = ( scalar[X] * (p0[Y] - p2[Y]) - scalar[Y] * (p0[X] - p2[X])) / (-scalar[Z] * scalar[Y] + scalar[X] * scalar[W]),
    t = ( scalar[Z] * (p0[Y] - p2[Y]) - scalar[W] * (p0[X] - p2[X])) / (-scalar[Z] * scalar[Y] + scalar[X] * scalar[W]);
    
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
        // Collision detected
        if (x != NULL)
            *x = p0[X] + (t * scalar[X]);
        if (y != NULL)
            *y = p0[Y] + (t * scalar[Y]);
        return 1;
    }
    
    return 0; // No collision
}

char intersect3_SEG_PLANE(line s, plane pn, vec4& i){
    point u = vec_sub(s.second,s.first);
    point w = vec_sub(s.first, pn.pt);
    
    GLfloat d = dot(pn.normal,u);
    GLfloat n = -dot(pn.normal,w);
    
    //segment is parallel
    if (fabs(d) < 0.00000001) {
        //segment is in plane
        if (n == 0){
            return 2;
        //no intersection
        }else
            return 0;
    }
    
    float si = n / d;
    
    //no intersection
    if (si < 0 || si > 1)
        return 0;
    
    //compute segment intersection point
    i = vec_mul(&si,u);
    i = vec_add(i,s.first);
    
    return 1;
}

#endif

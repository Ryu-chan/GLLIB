//
//  glPhysics.h
//  opengl
//
//  Created by Chris on 9/26/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLPHYSICS_H_
#define GLPHYSICS_H_

#include <vector>
#include <cmath>

namespace gl{
    
    struct line{
        point* first;
        point* second;
    };
    
    inline
    GLfloat dot(const point u, const point v){
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }
    
    inline
    GLfloat norm_sqr(const point v){
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }
    
    inline
    GLfloat norm(const point v){
        return sqrt(norm_sqr(v));
    }
    
    inline
    point cross(const point b, const point c){
        return point(b.y * c.z - c.y * b.z, b.z * c.x - c.z * b.x, b.x * c.y - c.x * b.y,1);
    }
    
    bool
    infiniteIntersection(line a, line b, point& i){
        point da = *(a.second) - *(a.first);
        point db = *(b.second) - *(b.first);
        point dc = *(b.first)  - *(a.first);
        
        if (dot(dc, cross(da,db)) != 0.0) // lines are not coplanar
            return false;
        
        GLfloat s = dot(cross(dc,db),cross(da,db)) / norm_sqr(cross(da,db));
        if (s >= 0.0 && s <= 1.0){
            i = *(a.first) + da * point(s,s,s,1);
            return true;
        }
        
        return false;
    }
    
    
    char doesIntersect(point p0, point p1, point p2, point p3, float *x, float *y)
    {
        //Algorithm inspired by vector cross product magnitude algortihm
        
        point scalar(
                     //scalar 1
                     p1.x - p0.x,
                     p1.y - p0.y,
                     //scalar 2
                     p3.x - p2.x,
                     p3.y - p2.y
                     );
        
        float
        s = ( scalar.x * (p0.y - p2.y) - scalar.y * (p0.x - p2.x)) / (-scalar.z * scalar.y + scalar.x * scalar.w),
        t = ( scalar.z * (p0.y - p2.y) - scalar.w * (p0.x - p2.x)) / (-scalar.z * scalar.y + scalar.x * scalar.w);
        
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
            // Collision detected
            if (x != NULL)
                *x = p0.x + (t * scalar.x);
            if (y != NULL)
                *y = p0.y + (t * scalar.y);
            return 1;
        }
        
        return 0; // No collision
    }
    
}

#endif

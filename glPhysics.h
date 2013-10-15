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
    
    typedef struct s_line{
        point* first;
        point* second;
    } line;
    typedef struct s_plane{
        point* pt;
        point* normal;
    } plane;
    
    line makeLine(point* a,point* b){
        line l;
            l.first = a;
            l.second = b;
        return l;
    }
    plane makePlane(point* pt,point* normal){
        plane p;
            p.pt = pt;
            p.normal = normal;
        return p;
    }
    plane makePlane(point* p1,point* p2,point* p3){
        plane p;
            p.pt = p1;
            p.normal = normal(p1,p2,p3);
        return p;
    }
    
    
    char intersect_SEG_SEG(point p0, point p1, point p2, point p3, float *x, float *y)
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

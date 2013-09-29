//
//  glMesh.h
//  opengl
//
//  Created by Chris on 9/24/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLMESH_H_
#define GLMESH_H_

#include <cmath>
#include <vector>
#include "glVec.h"

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

namespace gl{
 
    typedef vec4 point;
    typedef std::vector<point> mesh;
    
    mesh meshPolygon(GLuint sample){
        GLfloat rate = (M_PI*2)/sample;
        
        mesh poly;
        for(int i=0;i<sample;i++)
            poly.push_back(point(cos(i*rate),sin(i*rate),0,1));
        
        return poly;
        
    }
    
    
    
}

#endif

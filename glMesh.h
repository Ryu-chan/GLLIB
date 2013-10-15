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
#include "glGraphics.h"

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
    
    void meshGroupPolygon(GLuint sample,GLuint thickness,char** ref){
        mesh circle = meshPolygon(sample);
        
        GLuint* buffers = genBuffers(3);
        
        addBuffer(ref[0],buffers[0],makeStaticArrayBuffer(GL_TRIANGLE_FAN,&circle));
        addBuffer(ref[1],buffers[1],makeStaticArrayBuffer(GL_TRIANGLE_FAN,&circle));
        
        translateView(ref[1],translate(0,0,thickness));
        print((mat4)getBuffer(ref[1])->mview);
        /*
        std::vector<point> walls;
        for(auto w:circle){
            walls.push_back(w);
            walls.push_back(w+point(0,0,thickness,0));
        }
        walls.push_back(circle.at(0));
        walls.push_back(circle.at(0)+point(0,0,thickness,0));
        
        
        addBuffer(ref[2],buffers[2],makeStaticArrayBuffer(GL_QUAD_STRIP,&walls));//*/
        
    }
    
    
}

#endif

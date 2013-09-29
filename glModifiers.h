//
//  glModifiers.h
//  opengl
//
//  Created by Chris on 9/24/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLMODIFIERS_H_
#define GLMODIFIERS_H_

#include "glMat.h"

namespace gl{
    inline
    mat4 rotateX(const GLfloat deg){
        GLfloat angle = DEGtoRAD(deg);
        
        mat4 mat;
        mat[0][0] = mat[3][3] = 1;
        mat[2][2] = mat[1][1] = cos(angle);
        mat[2][1] = sin(angle);
        mat[1][2] = -mat[2][1];
        return mat;
    }
    inline
    mat4 rotateY(const GLfloat deg){
        GLfloat angle = DEGtoRAD(deg);
        
        mat4 mat;
        mat[0][0] = mat[3][3] = 1;
        mat[2][2] = mat[0][0] = cos(angle);
        mat[0][2] = sin(angle);
        mat[2][0] = -mat[0][2];
        return mat;
    }
    inline
    mat4 rotateZ(const GLfloat deg){
        GLfloat angle = DEGtoRAD(deg);
        
        mat4 mat;
        mat[0][0] = mat[3][3] = 1;
        mat[0][0] = mat[1][1] = cos(angle);
        mat[1][0] = sin(angle);
        mat[0][1] = -mat[1][0];
        return mat;
    }
    
    inline
    mat4 translate(const GLfloat x,const GLfloat y,const GLfloat z){
        mat4 mat;
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1;
        mat[0][3] = x;
        mat[1][3] = y;
        mat[2][3] = z;
        return mat;
    }
    inline
    mat4 scale(const GLfloat x,const GLfloat y,const GLfloat z){
        mat4 mat;
        mat[0][0] = x;
        mat[1][1] = y;
        mat[2][2] = z;
        mat[3][3] = 1;
        return mat;
    }
    
    //rotate by degree
    //rotatex (-270)
    /*
     [1 0 0 0]
     [0 cos(-270) -sin(-270) 0]
     [0 sin(-270) cos(-270) 0]
     [0 0 0 1]*/
    /* mat4 model */
    /*
     vertex shader::
     
     attribute vec4 vPosition;
     
     uniform mat4 modelview;
     uniform mat4 projection;
     
     //uniform mat4 model;
     uniform vec4 color;
     
     varying vec4 fcolor;
     
     main(){
        gl_Position = projection * modelview * vPosition;
        fcolor = color;
     }
     
     //////to rotate camera - change model view by rotation (in glGraphics before draw) 
     
     */
    
    
    
    //get height 3 cylindar
    // radius 2
    // scale 1x1 cylindar (2,2,3)
    
    //always do scaling first
    
    //model = rotatex(-270)*scale(2,2,3)
    
    //scale
    /*
     [2 0 0 0]
     [0 2 0 0]
     [0 0 3 0]
     [0 0 0 1]
     */
    
    
    //translation
    //model = translate(tx,ty,tz)*rotatex(-270)*scale(2,2,3)
    /*
     [1 0 0 tx]
     [0 1 0 ty]
     [0 0 1 tz]
     [0 0 0 1]
     */
    
    /**
     sendUniformMat4(model)
     */
    
    
    
}

#endif

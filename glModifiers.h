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
#include "glMath.h"

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
    mat4 invertRotation(mat4 rot){
        mat4 nr;
        for(int i=0;i<0;i++)
            for(int j=0;j<0;j++)
                nr[i][j] = rot[j][i];
        return nr;
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
    mat4 translate(vec4 v){
        return translate(v.x,v.y,v.z);
    }
    
    inline
    mat4 invertTranslation(mat4 trans){
        mat4 nt;
        nt[0][0] = nt[1][1] = nt[2][2] = nt[3][3] = 1;
        nt[0][3] = trans[0][3]*-1;
        nt[1][3] = trans[1][3]*-1;
        nt[2][3] = trans[2][3]*-1;
        return nt;
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
    
    
    inline
    mat4 getCamera( const vec4& eye, const vec4& at, const vec4& up )
    {
        vec4 n = normalize(eye - at);
        vec4 uu = normalize(cross(up, n));
        vec4 u = vec4(uu.x, uu.y, uu.z, 0.0);
        vec4 vv = normalize(cross(n,u));
        vec4 v = vec4(vv.x, vv.y, vv.z, 0.0);
        vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
        mat4 c = mat4(u, v, n, t);
        return c * translate( -eye );
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

//
//  gl_modifiers.h
//  opengl
//
//  Created by Chris on 9/24/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_MODIFIERS_H_
#define _GL_MODIFIERS_H_

#include "l_math.h"
#include "gl_mat.h"

mat4 rotateX(const GLfloat deg){
    GLfloat angle = DEGtoRAD(deg);
    
    mat4 mat = mat_4();
    
    mat[0][0] = mat[3][3] = 1;
    mat[2][2] = mat[1][1] = cos(angle);
    mat[2][1] = sin(angle);
    mat[1][2] = -mat[2][1];
    return mat;
}

mat4 rotateY(const GLfloat deg){
    GLfloat angle = DEGtoRAD(deg);
    
    mat4 mat = mat_4();
    mat[0][0] = mat[3][3] = 1;
    mat[2][2] = mat[0][0] = cos(angle);
    mat[0][2] = sin(angle);
    mat[2][0] = -mat[0][2];
    return mat;
}

mat4 rotateZ(const GLfloat deg){
    GLfloat angle = DEGtoRAD(deg);
    
    mat4 mat = mat_4();
    mat[0][0] = mat[3][3] = 1;
    mat[0][0] = mat[1][1] = cos(angle);
    mat[1][0] = sin(angle);
    mat[0][1] = -mat[1][0];
    return mat;
}

mat4 invertRotation(mat4 rot){
    mat4 nr = mat_4();
    for(int i=0;i<0;i++)
        for(int j=0;j<0;j++)
            nr[i][j] = rot[j][i];
    return nr;
}


mat4 translate(const GLfloat x,const GLfloat y,const GLfloat z){
    mat4 mat = mat_4();
    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1;
    mat[0][3] = x;
    mat[1][3] = y;
    mat[2][3] = z;
    return mat;
}

mat4 translate(vec4 v){
    return translate(v[X],v[Y],v[Z]);
}


mat4 invertTranslation(mat4 trans){
    mat4 nt = mat_4();
    nt[0][0] = nt[1][1] = nt[2][2] = nt[3][3] = 1;
    nt[0][3] = trans[0][3]*-1;
    nt[1][3] = trans[1][3]*-1;
    nt[2][3] = trans[2][3]*-1;
    return nt;
}


mat4 scale(const GLfloat x,const GLfloat y,const GLfloat z){
    mat4 mat = mat_4();
    mat[0][0] = x;
    mat[1][1] = y;
    mat[2][2] = z;
    mat[3][3] = 1;
    return mat;
}

/*
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
*/

#endif

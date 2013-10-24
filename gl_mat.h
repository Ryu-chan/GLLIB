//
//  gl_mat4.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_MAT_H_
#define _GL_MAT_H_

#include "gl_vec.h"

typedef GLfloat** mat4;
#define mat4_s 16*sizeof(GLfloat)


mat4 mat_4(GLfloat d = GLfloat(1.0)){
    GLfloat* ref = (GLfloat*)xmalloc(mat4_s);
    
    mat4 m = (mat4)xmalloc(4*sizeof(GLfloat*));
    
    m[0] = vec_4(&ref[0 ],(GLfloat)0);
    m[1] = vec_4(&ref[4 ],(GLfloat)0);
    m[2] = vec_4(&ref[8 ],(GLfloat)0);
    m[3] = vec_4(&ref[12],(GLfloat)0);
    
    m[0][X] = d;
    m[1][Y] = d;
    m[2][Z] = d;
    m[3][W] = d;
    
    return m;
}

void mat_print(mat4 m){
    for(int i=0;i<4;i++)
        vec_print(m[i]);
}


mat4 mat_mul(mat4 a,mat4 b){
    
    mat4 m = mat_4(0);
    
    if(a==NULL||b==NULL){
        return NULL;
    }
    
    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 4; ++j ) {
            for ( int k = 0; k < 4; ++k ) {
                m[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return m;
}

void mat_mul_eq(mat4* a,mat4 b){
    if(b!=NULL && a!=NULL && *a!=NULL)
        *a = mat_mul(*a,b);
}
void mat_mul_eq_free(mat4* a,mat4 b){
    if(b!=NULL && a!=NULL && *a!=NULL){
        mat4 c = *a;
        *a = mat_mul(c,b);
        free(c);
        free(b);
    }
}

#endif
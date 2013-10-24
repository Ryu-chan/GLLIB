//
//  gl_vec.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_VEC_H_
#define _GL_VEC_H_

#include "l_util.h"
#include "l_math.h"

typedef GLfloat* vec4;
#define vec4_s 4*sizeof(GLfloat)


vec4 vec_4(GLfloat _x,GLfloat _y,GLfloat _z,GLfloat _w){
    vec4 v = (vec4)xmalloc(vec4_s);
    v[X]=_x;
    v[Y]=_y;
    v[Z]=_z;
    v[W]=_w;
    return v;
}
vec4 vec_4(GLfloat l = GLfloat(0.0)){
    return vec_4(l,l,l,l);
}
vec4 vec_4(vec4* vec){
    return vec_4((*vec)[X],(*vec)[Y],(*vec)[Z],(*vec)[W]);
}



vec4 vec_4(GLfloat* mem,GLfloat _x,GLfloat _y,GLfloat _z,GLfloat _w){
    mem[X] = _x;
    mem[Y] = _y;
    mem[Z] = _z;
    mem[W] = _w;
    
    return mem;
}
vec4 vec_4(GLfloat* mem,GLfloat l = GLfloat(0.0)){
    return vec_4(mem,l,l,l,l);
}
vec4 vec_4(GLfloat* mem,vec4* vec){
    return vec_4(mem,(*vec)[X],(*vec)[Y],(*vec)[Z],(*vec)[W]);
}

void vec_print(vec4 v){
    xstr(" (");
    xint(v[X]*100);
    xstr(", ");
    xint(v[Y]*100);
    xstr(", ");
    xint(v[Z]*100);
    xstr(", ");
    xint(v[W]*100);
    xstr(") \n");
    
}

vec4 vec_add(vec4 a,vec4 b){
    vec4 v = (vec4)xmalloc(vec4_s);
    v[X]=a[X]+b[X];
    v[Y]=a[Y]+b[Y];
    v[Z]=a[Z]+b[Z];
    v[W]=a[W]+b[W];
    return v;
}
vec4 vec_sub(vec4 a,vec4 b){
    vec4 v = (vec4)xmalloc(vec4_s);
    v[X]=a[X]-b[X];
    v[Y]=a[Y]-b[Y];
    v[Z]=a[Z]-b[Z];
    v[W]=a[W]-b[W];
    return v;
}
vec4 vec_mul(vec4 a,vec4 b){
    vec4 v = (vec4)xmalloc(vec4_s);
    v[X]=a[X]*b[X];
    v[Y]=a[Y]*b[Y];
    v[Z]=a[Z]*b[Z];
    v[W]=a[W]*b[W];
    return v;
}


#endif

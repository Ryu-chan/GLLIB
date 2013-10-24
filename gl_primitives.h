//
//  gl_primitives.h
//  opengl
//
//  Created by Chris on 10/8/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_PRIMITIVES_H_
#define _GL_PRIMITIVES_H_

#include <map>
#include <vector>

#include "gl_vec.h"
#include "gl_scene.h"

typedef vec4 point;
typedef std::vector<point> mesh;
typedef std::map<const char*,unsigned int> simap;
typedef std::pair<const char*,unsigned int> sipair;

simap pmap;
//UTILS

GLfloat* contigify(mesh m){
    unsigned int s = (unsigned int)m.size() * vec4_s;
    GLfloat* ma = (GLfloat*)xmalloc(s);
    
    int i=0;
    for(auto d:m){
        ma[i++] = d[X];
        ma[i++] = d[Y];
        ma[i++] = d[Z];
        ma[i++] = d[W];
    }
    
    return ma;
}

void free_mesh(mesh m){
    for(auto d:m){
        free(d);
    }
}


void bufferMesh(const char* ref,mesh m){
    unsigned int size = (unsigned int)m.size() * vec4_s;
    GLfloat* data = contigify(m);
    
    GLuint* b = new GLuint[1];
    if(pmap.count(ref)){
        *b = pmap.at(ref);
        glBindBuffer(GL_ARRAY_BUFFER,*b);
        glBufferData(GL_ARRAY_BUFFER,size,&data[0],GL_STREAM_DRAW);
    }else{
        glGenBuffers(1,&b[0]);
        pmap.insert(sipair(ref,*b));
        glBindBuffer(GL_ARRAY_BUFFER,*b);
        glBufferData(GL_ARRAY_BUFFER,size,&data[0],GL_STATIC_DRAW);
    }
}
void bufferFreeMesh(const char* ref,mesh m){
    bufferMesh(ref,m);
    free_mesh(m);
}
void draw(GLenum mode,const char* ref,GLuint n){
    glBindBuffer(GL_ARRAY_BUFFER,pmap[ref]);
    sendAttrib("vPosition");
    sendUniformM("modelview",model_view);
    glDrawArrays(mode, 0, n);
}
mesh lace(const char* ref,mesh m1,vec4 offset){
    mesh m;
    for(int i=0;i<m1.size();i++){
        m.push_back(m1[i]);
        m.push_back(vec_add(m1[i],offset));
    }
    m.push_back(m1[0]);
    m.push_back(vec_add(m1[0],offset));
    
    bufferMesh(ref,m);
    
    return m;
}
// SQUARE
mesh square(const char* ref){
    mesh sqr;
    sqr.push_back(vec_4(-0.5,-0.5,0,1));
    sqr.push_back(vec_4(-0.5, 0.5,0,1));
    sqr.push_back(vec_4( 0.5, 0.5,0,1));
    sqr.push_back(vec_4( 0.5,-0.5,0,1));
    
    bufferMesh(ref,sqr);
    
    return sqr;
}
void drawSquare(const char* ref){
    draw(GL_LINE_LOOP,ref,4);
}
void fillSquare(const char* ref){
    draw(GL_QUADS,ref,4);
}
// POLYGON
mesh polygon(const char* ref, GLuint sample){
    GLfloat rate = (M_PI*2)/sample;
    
    mesh poly;
    for(int i=0;i<sample;i++)
        poly.push_back(vec_4(cos(i*rate),sin(i*rate),0,1));
    
    bufferMesh(ref,poly);
    
    return poly;
}
void drawPolygon(const char* ref,GLuint n){
    draw(GL_LINE_LOOP,ref,n);
}
void fillPolygon(const char* ref,GLuint n){
    draw(GL_TRIANGLE_FAN,ref,n);
}





#endif

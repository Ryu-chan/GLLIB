//
//  gl_frame.h
//  opengl
//
//  Created by Chris on 10/17/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_FRAME_H_
#define _GL_FRAME_H_

#include "l_util.h"

#include "gl_shaders.h"


typedef struct      s_gl_frame_env{
    unsigned int    dispmode    = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
    
    unsigned int    width       = 512;
    unsigned int    height      = 512;
    
    unsigned int    x           = 50;
    unsigned int    y           = 50;
    
}                   t_gl_frame_env;

t_gl_frame_env gl_frame_env;

void changeDefaultWindowSize(unsigned int width,unsigned int height){
    gl_frame_env.width = width;
    gl_frame_env.height = height;
}
void changeDefaultWindowPosition(unsigned int x,unsigned int y){
    gl_frame_env.x = x;
    gl_frame_env.y = y;
}
void changeDefaultWindowDisplayMode(unsigned int mode){
    gl_frame_env.dispmode = mode;
}


void render();
static void display(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    render();
    glutSwapBuffers();
    
}

void idle();

void makeFrame(const char* title = "OpenGL Project"){
    glutInitDisplayMode(gl_frame_env.dispmode);
    glutInitWindowSize(gl_frame_env.width,gl_frame_env.height);
    glutInitWindowPosition(gl_frame_env.x,gl_frame_env.y);
    glutCreateWindow(title);
    
    if( (gl_frame_env.dispmode & GLUT_RGBA) == GLUT_RGBA){
        xstr("Enabled Alpha Blending\n");
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    if( (gl_frame_env.dispmode & GLUT_DEPTH) == GLUT_DEPTH){
        xstr("Enabled Depth Testing\n");
        glEnable (GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);

}





#endif

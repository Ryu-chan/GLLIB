//
//  gl_animate.h
//  opengl
//
//  Created by Chris on 10/23/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_ANIMATE_H_
#define _GL_ANIMATE_H_

#include "l_util.h"

typedef struct  s_gl_anim{
    
    char        paused;
    char        ended;
    
}               t_gl_anim;
t_gl_anim         gl_anim;

void animate();

void anim(int i){
    if(gl_anim.ended)
        return;
    if(!gl_anim.paused)
        animate();
    
    glutTimerFunc(i,anim,i);
}

void anim_pause(){
    gl_anim.paused = TRUE;
}
void anim_resume(){
    gl_anim.paused = FALSE;
}
void anim_end(){
    gl_anim.ended = TRUE;
}

void anim_start(int i){
    gl_anim.paused = FALSE;
    gl_anim.ended = FALSE;
    anim(i);
}
void anim_start(){
    anim_start(17);
}

#endif

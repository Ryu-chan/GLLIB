//
//  gl_camera.h
//  opengl
//
//  Created by Chris on 10/23/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_CAMERA_H_
#define _GL_CAMERA_H_

typedef struct  s_gl_cam{
    
    unsigned char   moving;
    GLint           startx;
    GLint           starty;
    GLint           phi;
    GLint           theta;
    
    GLfloat         scale;
    GLfloat         panx;
    GLfloat         pany;
    
}               t_gl_cam;
t_gl_cam          gl_cam;

void initCamera(){
    
    gl_cam.moving    = FALSE;
    gl_cam.startx    = 0;
    gl_cam.starty    = 0;
    gl_cam.phi       = 0;
    gl_cam.theta     = 0;
    gl_cam.scale     = -1;
    gl_cam.panx      = 0;
    gl_cam.pany      = 0;
    
    addMouseListener([](t_mouseevent* e)->void{
        if (e->button == GLUT_LEFT_BUTTON) {
            if (e->state == GLUT_DOWN) {
                gl_cam.moving = TRUE;
                gl_cam.startx = e->x;
                gl_cam.starty = e->y;
            }
            if (e->state == GLUT_UP) {
                gl_cam.moving = FALSE;
            }
        }
    });
    addMouseDragListener([](t_mousedragevent* e)->void{
        
        if (gl_cam.moving) {
            
            switch(getModifier()){
                case 1: //SHIFT - pan
                    gl_cam.panx     += (e->x - gl_cam.startx)/100.0;
                    gl_cam.pany     += (e->y - gl_cam.starty)/100.0;
                    break;
                case 2: //CTRL - scale
                    gl_cam.scale    += (e->y - gl_cam.starty)/100.0;
                    break;
                default: //Nothing - rotate
                    gl_cam.phi      += (e->x - gl_cam.startx);
                    gl_cam.theta    += (e->y - gl_cam.starty);
                    break;
            }
            
            gl_cam.startx  =   e->x;
            gl_cam.starty  =   e->y;
            glutPostRedisplay();
        }
    });
}

void modifyWorldView(mat4* view){
    mat_mul_eq_free(view,translate(gl_cam.panx,-gl_cam.pany,0));
    mat_mul_eq_free(view,rotateY(-gl_cam.phi));
    mat_mul_eq_free(view,rotateX(-gl_cam.theta));
    mat_mul_eq_free(view,scale(-gl_cam.scale,-gl_cam.scale,-gl_cam.scale));
}

#endif

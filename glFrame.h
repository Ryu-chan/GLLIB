//
//  glFrame.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLFRAME_H_
#define GLFRAME_H_

#include "glData.h"
#include "glEvents.h"
#include "glGraphics.h"

namespace gl{

    typedef pair<unsigned int> dim;
    typedef pair<unsigned int> pos;

    class glFrame{
    private:
        //static Graphics g;
        
        static std::vector< void(*)(KeyEvent) >  keylist;
        static std::vector< void(*)(MouseEvent) > mouselist;
        static std::vector< void(*)(MouseMotionEvent) > mousemotionlist;
        static std::vector< void(*)(MouseDragEvent) > mousedraglist;
        static void (*render)();
        
        static void keylistener(unsigned char key,int x,int y){
            KeyEvent evt(key,x,y);
            for(auto e:glFrame::keylist){
                (*e)(evt);
            }
        }
        static void mouselistener(int button,int state,int x,int y){
            MouseEvent evt(button,state,x,y);
            for(auto e:mouselist){
                (*e)(evt);
            }
        }
        static void mousemotionlistener(int x,int y){
            MouseMotionEvent evt(x,y);
            for(auto e:mousemotionlist){
                (*e)(evt);
            }
        }
        static void mousedraglistener(int x,int y){
            MouseDragEvent evt(x,y);
            for(auto e:mousedraglist){
                (*e)(evt);
            }
        }
        static void display(){
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            //glGraphics::renderBuffers();
            renderBuffers();
            render();
            glFlush();
        }
        
       
        
    public:
        glFrame(
            const char*     title    = "OpenGL Project",
            unsigned int    dispMode = GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH,
            dim             size     = dim(512,512),
            pos             position = pos(50,50)
        ){
            glutInitDisplayMode(dispMode);
            glutInitWindowPosition(position.x,position.y);
            glutInitWindowSize(size.x,size.y);
            glutCreateWindow(title);
            
            //Listeners
            glutKeyboardFunc(glFrame::keylistener);
            glutMouseFunc(glFrame::mouselistener);
            glutPassiveMotionFunc(glFrame::mousemotionlistener);
            glutMotionFunc(glFrame::mousedraglistener);
            
            glutDisplayFunc(glFrame::display);
            
            glEnable (GL_DEPTH_TEST);
            
            addAttrib("vPosition");
            addUniform("color");
            addUniform("modelview");
        }
        
        /*Graphics getGraphics(){
            return g;
        }*/
        
        void addKeyListener(void(*listener)(KeyEvent)){
            keylist.push_back(listener);
        }
        void addMouseListener(void(*listener)(MouseEvent)){
            mouselist.push_back(listener);
        }
        void addMouseMotionListener(void(*listener)(MouseMotionEvent)){
            mousemotionlist.push_back(listener);
        }
        void addMouseDragListener(void(*listener)(MouseDragEvent)){
            mousedraglist.push_back(listener);
        }
        void setRenderFunction(void(*_render)()){
            render=_render;
        }
        void setIdleFunction(void(*_idle)()){
            glutIdleFunc(_idle);
        }
        
        int getWidth(){
            return glutGet(GLUT_WINDOW_WIDTH);
        }
        int getHeight(){
            return glutGet(GLUT_WINDOW_HEIGHT);
        }

    };
    
    std::vector< void(*)(KeyEvent) >            glFrame::keylist;
    std::vector< void(*)(MouseEvent) >          glFrame::mouselist;
    std::vector< void(*)(MouseMotionEvent) >    glFrame::mousemotionlist;
    std::vector< void(*)(MouseDragEvent) >      glFrame::mousedraglist;
    void (*glFrame::render)() = [](){};
    
}

#endif

//
//  gl_events.h
//  opengl
//
//  Created by Chris on 10/17/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_EVENTS_H_
#define _GL_EVENTS_H_

#include "l_data.h"
#include "l_util.h"

/** KEY EVENT **/

unsigned char gl_modifier;

typedef struct      s_keyevent{
    
    unsigned char   key;
    int             x;
    int             y;
    
}                   t_keyevent;

t_keyevent* makeKeyEvent(unsigned char _key,int _x,int _y){
    t_keyevent* ke = (t_keyevent*)xmalloc(sizeof(t_keyevent));
    ke -> key = _key;
    ke -> x = _x;
    ke -> y = _y;
    return ke;
}

LinkedList gl_keylisteners;

typedef void(*keylistener)(t_keyevent*);

void addKeyListener(keylistener kl){
    gl_keylisteners.add((void*)kl);
}

void pass_keylistener(unsigned char key,int x,int y){
    t_keyevent* ke = makeKeyEvent(key,x,y);
    
    for(llnode* node = gl_keylisteners.head;node!=NULL;node=node->next)
        ((keylistener)(node->elem))(ke);
    
    free(ke);
    
    gl_modifier = glutGetModifiers();
}

/** END KEY EVENT **/

/** MOUSE EVENT **/

typedef struct      s_mouseevent{
    
    int             button;
    int             state;
    int             x;
    int             y;
    
}                   t_mouseevent;

t_mouseevent* makeMouseEvent(int _button,int _state,int _x,int _y){
    t_mouseevent* me = (t_mouseevent*)xmalloc(sizeof(t_mouseevent));
    me -> button = _button;
    me -> state = _state;
    me -> x = _x;
    me -> y = _y;
    return me;
}

LinkedList gl_mouselisteners;

typedef void(*mouselistener)(t_mouseevent*);

void addMouseListener(mouselistener kl){
    gl_mouselisteners.add((void*)kl);
}

void pass_mouselistener(int button,int state,int x,int y){
    t_mouseevent* me = makeMouseEvent(button,state,x,y);
    
    for(llnode* node = gl_mouselisteners.head;node!=NULL;node=node->next)
        ((mouselistener)(node->elem))(me);
    
    free(me);
    
    gl_modifier = glutGetModifiers();
}

/** END MOUSE EVENT **/

/** MOUSE MOTION EVENT **/

typedef struct      s_mousemotionevent{
    
    int             x;
    int             y;
    
}                   t_mousemotionevent;

t_mousemotionevent* makeMouseMotionEvent(int _x,int _y){
    t_mousemotionevent* mme = (t_mousemotionevent*)xmalloc(sizeof(t_mousemotionevent));
    
    mme -> x = _x;
    mme -> y = _y;
    
    return mme;
}

LinkedList gl_mousemotionlisteners;

typedef void(*mousemotionlistener)(t_mousemotionevent*);

void addMouseMotionListener(mouselistener kl){
    gl_mouselisteners.add((void*)kl);
}

void pass_mousemotionlistener(int x,int y){
    t_mousemotionevent* mme = makeMouseMotionEvent(x,y);
    
    for(llnode* node = gl_mousemotionlisteners.head;node!=NULL;node=node->next)
        ((mousemotionlistener)(node->elem))(mme);
    
    free(mme);

}

/** END MOUSE MOTION EVENT **/

/** MOUSE DRAG EVENT **/

typedef struct      s_mousedragevent{
    
    int             x;
    int             y;

}                   t_mousedragevent;

t_mousedragevent* makeMouseDragEvent(int _x,int _y){
    t_mousedragevent* mde = (t_mousedragevent*)xmalloc(sizeof(t_mousedragevent));
    
    mde -> x = _x;
    mde -> y = _y;
    
    return mde;
}

LinkedList gl_mousedraglisteners;

typedef void(*mousedraglistener)(t_mousedragevent*);

void addMouseDragListener(mousedraglistener kl){
    gl_mousedraglisteners.add((void*)kl);
}

void pass_mousedraglistener(int x,int y){
    t_mousedragevent* me = makeMouseDragEvent(x,y);
    
    for(llnode* node = gl_mousedraglisteners.head;node!=NULL;node=node->next)
        ((mousedraglistener)(node->elem))(me);
    
    free(me);
}

/** END MOUSE DRAG EVENT **/

void initListeners(){
    glutKeyboardFunc(pass_keylistener);
    glutMouseFunc(pass_mouselistener);
    glutPassiveMotionFunc(pass_mousemotionlistener);
    glutMotionFunc(pass_mousedraglistener);
}

unsigned char getModifier(){return gl_modifier;}

#endif

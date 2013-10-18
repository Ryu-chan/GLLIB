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
}


/** END KEY EVENT **/

/*****TODO FINISH EVENT HANDLERS*****/

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






#endif

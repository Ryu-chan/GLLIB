//
//  glEvent.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLEVENT_H_
#define GLEVENT_H_

namespace gl{
    struct KeyEvent{
        unsigned char key;
        int x;
        int y;
        KeyEvent(unsigned char _key,int _x,int _y):
            key(_key),
            x(_x),
            y(_y)
        {}
    };
    
    struct MouseEvent{
        int button;
        int state;
        int x;
        int y;
        MouseEvent(int _button,int _state,int _x,int _y):
            button(_button),
            state(_state),
            x(_x),
            y(_y)
        {}
    };
    
    struct MouseMotionEvent{
        int x;
        int y;
        MouseMotionEvent(int _x,int _y):
            x(_x),
            y(_y)
        {}
    };
    
    struct MouseDragEvent{
        int x;
        int y;
        MouseDragEvent(int _x,int _y):
            x(_x),
            y(_y)
        {}
    };
    
    
    
    
}

#endif

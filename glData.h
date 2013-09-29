//
//  glData.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLDATA_H_
#define GLDATA_H_

namespace gl{
    
    template<class T>
    struct pair{
        T x,y;
        pair(T _x,T _y):
            x(_x),
            y(_y)
        {}
    };
    
    template<class K,class V>
    struct keyvalue{
        K key;
        V value;
        keyvalue(K _key,V _value):
            key(_key),
            value(_value)
        {}
    };

}

#endif

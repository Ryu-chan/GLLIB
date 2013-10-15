//
//  glView.h
//  opengl
//
//  Created by Chris on 10/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLVIEW_H_
#define GLVIEW_H_

#include "glMat.h"
#include "glModifiers.h"

namespace gl{
    
    typedef struct s_view{
        
        mat4 t = mat4(1);
        mat4 r = mat4(1);
        mat4 s = mat4(1);
        
        void modT(mat4 _t){
            /*t[0][3]+=_t[0][3];
            t[1][3]+=_t[1][3];
            t[2][3]+=_t[2][3];*/
            t*=_t;
        }
        void modR(mat4 _r){
            r*=_r;
        }
        void modS(mat4 _s){
            s*=_s;
        }
        
        //Conversion
        operator const mat4 () const
        {return static_cast<const mat4>( t*r*s );}
        
        operator mat4 ()
        {return static_cast<mat4>( t*r*s );}
        
        mat4 operator * //multiplication (by view)
        (const s_view& v) const
        {
            mat4 m = mat4(1);
            m*=(s*v.s);
            m*=(r*v.r);
            m*=(t*v.t);
            //m[0][3] = t[0][3]+v.t[0][3];
            //m[1][3] = t[1][3]+v.t[1][3];
            //m[2][3] = t[2][3]+v.t[2][3];
            print(m);
            return m;
        }
        
    } view;
    
    view worldview;
    
    
    void rotateWorld(mat4 rotation){
        worldview.modR(rotation);
    }
    void scaleWorld(mat4 scale){
        worldview.modS(scale);
    }
    void translateWorld(mat4 translation){
        worldview.modT(translation);
    }
    
    
    
}

#endif

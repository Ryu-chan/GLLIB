//
//  glVec.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLVEC_H_
#define GLVEC_H_

//THIS NEEDS TO BE RE-WRITTEN
namespace gl{
    struct vec4{
        GLfloat x,y,z,w;
        
        vec4(GLfloat l = GLfloat(0.0)):
        x(l), y(l), z(l), w(l)
        {}
        
        vec4(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w):
        x(_x), y(_y), z(_z), w(_w)
        {}
        
        vec4(const vec4& v):
        x(v.x), y(v.y), z(v.z), w(v.w)
        {}
        
        /// Operators
        
        // Indexing
        GLfloat& operator [] ( int i ) { return *(&x + i); }
        const GLfloat operator [] ( int i ) const { return *(&x + i); }
        
        // Arithmatic
        
        vec4 operator - //negation
        () const
        { return vec4(-x,-y,-z,-w); }
        
        vec4 operator + //addition
        (const vec4& v) const
        { return vec4(x+v.x,y+v.y,z+v.z,w+v.w); }
        
        vec4 operator - //subtraction
        (const vec4& v) const
        { return vec4(x-v.x,y-v.y,z-v.z,w-v.w); }
        
        vec4 operator * //multiplication (by scalor)
        (const GLfloat s) const
        { return vec4(s*x,s*y,s*z,s*w); }
        
        vec4 operator * //multiplication (by vector)
        (const vec4& v) const
        { return vec4(x*v.x,y*v.y,z*v.z,w*v.w); }
        
        vec4& operator += //additive modifier
        (const vec4& v)
        {x+=v.x;y+=v.y;z+=v.z;w+=v.w;return *this;}
        
        vec4& operator -= //subtractive modifier
        (const vec4& v)
        {x-=v.x;y-=v.y;z-=v.z;w-=v.w;return *this;}
        
        vec4& operator *= //multiplicative modifier (by scalar)
        (const GLfloat s)
        {x*=s;y*=s;z*=s;w*=s;return *this;}
        
        vec4& operator *= //multiplicative modifier (by vector)
        (const vec4& v)
        {x*=v.x,y*=v.y,z*=v.z,w*=v.w;return *this;}
        
        //Conversion
        operator const GLfloat* () const
        {return static_cast<const GLfloat*>( &x );}
        
        operator GLfloat* ()
        {return static_cast<GLfloat*>( &x );}
        
        //Streams
        friend std::ostream& operator << ( std::ostream& os, const vec4& v ) {
            return os << "( " << v.x << ", " << v.y
            << ", " << v.z << ", " << v.w << " )";
        }
        
        friend std::istream& operator >> ( std::istream& is, vec4& v )
        { return is >> v.x >> v.y >> v.z >> v.w; }
    };
}

#endif

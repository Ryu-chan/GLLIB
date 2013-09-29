//
//  glMat.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLMAT_H_
#define GLMAT_H_

//THIS NEEDS TO BE RE-WRITTEN
namespace gl{
    
    struct mat4{
        
        vec4 _m[4];
        
        mat4(const GLfloat d = GLfloat(1.0))
        {_m[0].x = d;_m[1].y = d;_m[2].z = d;_m[3].w = d;}
        
        mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d )
        {_m[0] = a;_m[1] = b;_m[2] = c;_m[3] = d;}
        
        mat4( GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
             GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
             GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
             GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33
             ){
            _m[0] = vec4( m00, m01, m02, m03 );
            _m[1] = vec4( m10, m11, m12, m13 );
            _m[2] = vec4( m20, m21, m22, m23 );
            _m[3] = vec4( m30, m31, m32, m33 );
        }
        
        mat4(const mat4& m){
            if ( *this != m ) {
                _m[0] = m._m[0];
                _m[1] = m._m[1];
                _m[2] = m._m[2];
                _m[3] = m._m[3];
            }
        }
        
        /// Operators
        
        //Indexing
        vec4& operator [] ( int i ) { return _m[i]; }
        const vec4& operator [] ( int i ) const { return _m[i]; }
        
        // Arithmatic
        
        mat4 operator + //addition
        (const mat4& m) const
        {return mat4(_m[0]+m[0], _m[1]+m[1], _m[2]+m[2], _m[3]+m[3]);}
        
        mat4 operator - // subtraction
        (const mat4& m) const
        {return mat4(_m[0]-m[0], _m[1]-m[1], _m[2]-m[2], _m[3]-m[3] );}
        
        mat4 operator * // multiplication (by scalar)
        (const GLfloat s) const
        {return mat4(_m[0]*s, _m[1]*s, _m[2]*s, _m[3]*s );}
        
        mat4 operator * // multiplication (by matrix)
        (const mat4& m) const
        {
            mat4  a( 0.0 );
            
            int i,j,k;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    for ( k = 0; k < 4; k++ ) {
                        a[i][j] += _m[i][k] * m[k][j];
                    }
                }
            }
            
            return a;
        }
        
        mat4& operator += // additive modifier
        (const mat4& m){
            _m[0] += m[0];  _m[1] += m[1];  _m[2] += m[2];  _m[3] += m[3];
            return *this;
        }
        
        mat4& operator -= // subtractive modifier
        (const mat4& m){
            _m[0] -= m[0];  _m[1] -= m[1];  _m[2] -= m[2];  _m[3] -= m[3];
            return *this;
        }
        
        mat4& operator *= // multiplicative modifier (by scalar)
        (const GLfloat s){
            _m[0] *= s;  _m[1] *= s;  _m[2] *= s;  _m[3] *= s;
            return *this;
        }
        
        mat4& operator *= // multiplicative modifier (by matrix)
        (const mat4& m){
            mat4  a( 0.0 );
            
            for ( int i = 0; i < 4; ++i ) {
                for ( int j = 0; j < 4; ++j ) {
                    for ( int k = 0; k < 4; ++k ) {
                        a[i][j] += _m[i][k] * m[k][j];
                    }
                }
            }
            
            return (*this = a);
        }
        
        
        // Vector operators
        
        vec4 operator *
        (const vec4& v ) const {
            return vec4( _m[0][0]*v.x + _m[0][1]*v.y + _m[0][2]*v.z + _m[0][3]*v.w,
                        _m[1][0]*v.x + _m[1][1]*v.y + _m[1][2]*v.z + _m[1][3]*v.w,
                        _m[2][0]*v.x + _m[2][1]*v.y + _m[2][2]*v.z + _m[2][3]*v.w,
                        _m[3][0]*v.x + _m[3][1]*v.y + _m[3][2]*v.z + _m[3][3]*v.w
                        );
        }
        
        operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &_m[0].x ); }
        
        operator GLfloat* ()
        { return static_cast<GLfloat*>( &_m[0].x ); }
        
    };
}



#endif

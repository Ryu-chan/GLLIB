//
//  glGraphics.h
//  opengl
//
//  Created by Chris on 9/4/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLGRAPHICS_H_
#define GLGRAPHICS_H_

#include <map>
#include <vector>

#include "glColor.h"
#include "glVec.h"
#include "glMat.h"
#include "glView.h"
#include "glShaders.h"

#define STATIC_BUFFER 0
#define MUTABLE_BUFFER 1

namespace gl{
    
    typedef vec4 point;
    
    struct gl_buf{
        GLenum      target;
        GLenum      usage;
        GLenum      mode;
        
        GLuint      loc;
        
        bool        render = true;
        bool        update = false;
        glColor     color = glColor::BLACK;
        view        mview;
        
        char        type = -1;
        
        std::vector<point>* data;
    };
    
    typedef std::map<const char*,GLuint>  glintmap;
    typedef std::pair<const char*,GLuint> glintpair;
    
    typedef std::map<const char*,gl_buf*> glbufmap;
    typedef std::pair<const char*,gl_buf*>glbufpair;
    
    typedef vec4 point;
    
    glintmap attribs;
    
    void addAttrib(const char* name){
        attribs.insert(glintpair(name,0));
    }
    
    void sendAttrib(const char* name){
        glVertexAttribPointer(attribs.at(name),4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    }
    
    glintmap uniforms;
    
    void addUniform(const char* name){
        uniforms.insert(std::pair<const char*,GLuint>(name,0));
    }
    void sendUniformV(const char* name,vec4 val){
        glUniform4fv(uniforms.at(name),1,val);
    }
    void sendUniformM(const char* name,mat4 mat){
        glUniformMatrix4fv(uniforms.at(name), 1, GL_TRUE, mat);
    }
    
    
    glintmap programs;
    
    void createProgram(const char* name,const char* vshader,const char* fshader){
        GLuint program = initShaders(vshader,fshader);
        
        programs.insert(std::pair<const char*,GLuint>(name,program));
    }
    
    static void useProgram(const char* name){
        GLuint program = programs.at(name);
        
        glUseProgram(program);
        
        glintmap::iterator it;
        
        for(it=attribs.begin();it!=attribs.end();it++){
            it->second = glGetAttribLocation(program,it->first);
            glEnableVertexAttribArray(it->second);
        }
        for(it=uniforms.begin();it!=uniforms.end();it++){
            
            it->second = glGetUniformLocation(program,it->first);
        }
        
        /*
        vPosition = glGetAttribLocation(program,"vPosition");
        glEnableVertexAttribArray( vPosition );
        
        LOC_color = glGetUniformLocation(program, "color");
        LOC_model = glGetUniformLocation(program, "modelview");*/
        
        //setViewScale();
    }
    
    //sendUniformV("color",getColor(color))
    
    vec4 getColor(glColor color){
        return vec4(
                    color.getRed()  /255.0,
                    color.getGreen()/255.0,
                    color.getBlue() /255.0,
                    color.getAlpha()/255.0
                    );
    }
    
    void setBackground(glColor c){
        vec4 color = getColor(c);
        glClearColor(color.x,color.y,color.z,color.w);
    }
    
    
    glbufmap gl_buffers;
    
    void updateData(gl_buf* b){
        glBindBuffer(
                     b->target,
                     b->loc
                     );
        glBufferData(
                     b->target,
                     ((int)(b->data->size()))*sizeof(point),
                     b->data->data(),
                     b->usage
                     );
    }
    
    
    void markUpdate(const char* ref){
        gl_buffers.at(ref)->update = true;
    }
    
    void setView(const char* ref,view v){
        gl_buffers.at(ref)->mview = v;
    }
    
    void rotateView(const char* ref,mat4 rotation){
        gl_buffers.at(ref)->mview.modR(rotation);
    }
    void translateView(const char* ref,mat4 translation){
        gl_buffers.at(ref)->mview.modT(translation);
    }
    void scaleView(const char* ref,mat4 scale){
        gl_buffers.at(ref)->mview.modS(scale);
    }
    
    void changeColor(const char* ref,glColor color){
        gl_buffers.at(ref)->color = color;
    }
    
    void addBuffer(const char* ref, GLuint loc, gl_buf* buf){
        buf -> loc = loc;
        gl_buffers.insert(glbufpair(ref,buf));
        updateData(buf);
    }
    
    gl_buf* getBuffer(const char* ref){
        return gl_buffers.at(ref);
    }
    
    GLuint* genBuffers(unsigned int n){
        GLuint* bufs = new GLuint[n];
        glGenBuffers(n,&bufs[0]);
        return bufs;
    }
    
    void renderBuffers(){
        for(glbufmap::iterator it=gl_buffers.begin();it!=gl_buffers.end();it++){
            gl_buf* b = it->second;
            if(b->render){
                glBindBuffer(b->target,b->loc);
                
                if(b->type == MUTABLE_BUFFER)
                    if(b->update){
                        updateData(b);
                        b->update = false;
                    }
                
                sendUniformV("color",getColor(b->color));
                sendUniformM("modelview",worldview*b->mview);
                sendAttrib("vPosition");
                
                glDrawArrays(b->mode,0,(int)(b->data->size()));
                
            }
        }
    }
    
    gl_buf* makeArrayBuffer(unsigned int type,GLenum mode,std::vector<point>* data){
        gl_buf* b = new gl_buf;
        
        b->type = type;
        
        b->data = data;
        
        b->mode = mode;
        
        b->target = GL_ARRAY_BUFFER;
        
        b->usage =
            /*(type == STATIC_BUFFER)?
            GL_STATIC_DRAW:*/
            (type == MUTABLE_BUFFER)?
            GL_STREAM_DRAW:
        GL_STATIC_DRAW;
        
        
        return b;
    }
    gl_buf* makeStaticArrayBuffer(GLenum mode,std::vector<point>* data){
        return makeArrayBuffer(STATIC_BUFFER,mode,data);
    }
    gl_buf* makeStaticArrayBuffer(GLenum mode,point* data,unsigned int n){
        std::vector<point>* vec = new std::vector<point>;
        for(int i=0;i<n;i++)
            vec->push_back(data[i]);
        return makeStaticArrayBuffer(mode, vec);
    }
    gl_buf* makeMutableArrayBuffer(GLenum mode,std::vector<point>* data){
        return makeArrayBuffer(MUTABLE_BUFFER,mode,data);
    }
    
    
    
    
    
    void setTimeout(unsigned int ms,void(*_timefunc)(int i),int i){
        glutTimerFunc(ms, _timefunc, i);
    }
    
}

#endif
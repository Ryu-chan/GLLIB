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

#define STATIC_BUFFER 0
#define MUTABLE_BUFFER 1

namespace gl{
    
    struct gl_buf{
        GLenum      target;
        GLenum      usage;
        GLenum      mode;
        
        GLuint      loc;
        
        bool        render = true;
        bool        update = false;
        glColor     color = glColor::BLACK;
        mat4        mview = mat4(1);
        
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
    
    
    mat4 camera = mat4(1);
    
    void modifyCamera(mat4 view){
        camera *= view;
    }
    void setCamera(mat4 view){
        camera = view;
    }
    void resetCamera(mat4 view){
        camera = mat4(1);
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
    
    void resetView(const char* ref){
        gl_buffers.at(ref)->mview = mat4(1);
    }
    void setView(const char* ref,mat4 view){
        gl_buffers.at(ref)->mview = view;
    }
    void modifyView(const char* ref,mat4 view){
        gl_buffers.at(ref)->mview *= view;
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
                sendUniformM("modelview",camera*b->mview);
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
    /*
    
    void animationLoop(int ms,void(*_animate)()){
        
    }
    
    static void setAnimation(unsigned int timeout,void(*_animate)(),unsigned int delay = 1000){
        setTimeout(delay,[]()->void(int i){
            setTimeout(delay,[]()->void(int j){
                
            },i);
        },timeout);
        
        animate=_animate;
        animation(timeout);
    }
    
    */
    /*struct buffer{
        GLenum          target;
        GLenum          usage;
        GLenum          mode;
        
        GLuint          loc;
        
        bool            render = true;
        glColor         color = glColor::BLACK;
        
        char            type = -1;
    };
    
    const char STATIC_BUFFER = 0;
    struct static_buffer:public buffer{
        GLvoid*         data;
        int             n;
    };
    
    const char MUTABLE_BUFFER = 1;
    struct mutable_buffer:public buffer{
        std::vector<point>* vec;
    };*/
    
    /*typedef std::map<unsigned int,buffer*> bmap;
    typedef std::map<unsigned int,GLuint> pmap;*/
 /*
    class glGraphics{
    private:
        static bmap buffers;
        static pmap programs;
        static void (*animate)();
        
        static void animation(int i){
            animate();
            glutTimerFunc(i,animation,i);
        }
    public:
        
        //Takes a name and shaders to make a program and store it
        /static void createProgram(unsigned int name,const char* vshader,const char* fshader){
            GLuint program = initShaders(vshader,fshader);
            
            programs.insert(std::pair<unsigned int,GLuint>(name,program));
        }*/
        
        //Gets a program from the store and uses it
        /*static void useProgram(unsigned int name){
            GLuint program = programs.at(name);
            
            glUseProgram(program);
            
            vPosition = glGetAttribLocation(program,"vPosition");
            glEnableVertexAttribArray( vPosition );
            
            LOC_color = glGetUniformLocation(program, "color");
            LOC_model = glGetUniformLocation(program, "modelview");
            
            setViewScale();
        }*/
        
        //Sets the clear color
        /*static void setBackground(glColor c){
            vec4 color = getColor(c);
            glClearColor(color.x,color.y,color.z,color.w);
        }
        
        //Sets the drawing color
        static void setColor(glColor color){
            glUniform4fv(LOC_color,1,getColor(color));
        }*/
        
        //Sets the view to some scale of 1 x 1 x 1
        /*static void setViewScale(GLfloat x=1.0,GLfloat y=1.0,GLfloat z=1.0){
            mat4 scale;
                scale[0][0] = x;
                scale[1][1] = y;
                scale[2][2] = z;
            glUniformMatrix4fv(LOC_model, 1, GL_TRUE, mat4(1.0)*scale);
        }
        */
        //Adds a buffer to the store with the given location from gen buffer
        /*static void addBuffer(unsigned int ref, GLuint loc, buffer* buf){
            buf -> loc = loc;
            buffers.insert(std::pair<unsigned int,buffer*>(ref,buf));
            updateData(buf);
        }
        
        //Gets a buffer from the store with the given reference
        static buffer* getBuffer(unsigned int ref){
            return buffers.at(ref);
        }
        
        //Generates the number of buffers and passes back their values
        static GLuint* genBuffers(unsigned int n){
            GLuint* buffers = new GLuint[n];
            glGenBuffers(n,&buffers[0]);
            return buffers;
        }*/
        
        //Rebinds data to the specified buffer
        /*static void updateData(buffer* b){
            if(b->type == STATIC_BUFFER){
                static_buffer* buf = (static_buffer*)b;
                glBindBuffer(buf -> target, buf -> loc);
                glBufferData(buf -> target, buf -> n, buf -> data, buf -> usage);
            }else if(b->type == MUTABLE_BUFFER){
                mutable_buffer* buf = (mutable_buffer*)b;
                glBindBuffer(buf -> target, buf -> loc);
                glBufferData(buf -> target, ((int)(buf -> vec -> size())) * sizeof(point),buf->vec->data(), buf -> usage);
            }
        }*/
        
        //Renders all of the buffers in the map
        /*static void renderBuffers(){
            for(bmap::iterator it=buffers.begin();it!=buffers.end();it++){
                if(it->second->type == STATIC_BUFFER){
                    static_buffer* b = (static_buffer*)it->second;
                    if(b->render){
                        setColor(b->color);
                        glBindBuffer(b->target,b->loc);
                        glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
                        glDrawArrays(b->mode,0,b->n);
                    }
                }else if(it->second->type == MUTABLE_BUFFER){
                    mutable_buffer* b = (mutable_buffer*)it->second;
                    if(b->render){
                        updateData(b);
                        setColor(b->color);
                        glBindBuffer(b->target,b->loc);
                        glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
                        glDrawArrays(b->mode,0,((int)b->vec->size()));
                    }
                }
            }
        }*/
        /*
        static void setTimeout(unsigned int ms,void(*_timefunc)(int i)){
            glutTimerFunc(ms, _timefunc, 0);
        }
        
        static void setAnimation(unsigned int timeout,void(*_animate)(),unsigned int delay = 1000){
            animate=_animate;
            animation(timeout);
        }*/
        
        /** MAKE ARRAYS **/
        /*
        static static_buffer* makeEmptyStaticArrayBuffer(GLenum mode){
            return makeStaticArrayBuffer(mode,NULL,0);
        }
        
        static static_buffer* makeStaticArrayBuffer(GLenum mode,GLvoid* data,unsigned int dataSize){
            static_buffer* ret = new static_buffer;
            
            ret -> type = STATIC_BUFFER;
            
            ret -> data = data;
            ret -> n = dataSize;
            ret -> mode = mode;
            
            ret -> target = GL_ARRAY_BUFFER;
            ret -> usage = GL_STATIC_DRAW;
            
            return ret;
        }
        
        
        static static_buffer* makeStaticRectBuffer(point* rect,unsigned int n){
            return makeStaticArrayBuffer(GL_QUADS,rect,n*sizeof(point));
        }
        static static_buffer* makeStaticLineBuffer(point* lines,unsigned int n){
            return makeStaticArrayBuffer(GL_LINES,lines,n*sizeof(point));
        }
        static static_buffer* makeStaticLineStripBuffer(point* lines,unsigned int n){
            return makeStaticArrayBuffer(GL_LINE_STRIP,lines,n*sizeof(point));
        }
        
        static mutable_buffer* makeMutableArrayBuffer(GLenum mode,std::vector<point>* vec){
            mutable_buffer* ret = new mutable_buffer;
            
            ret -> type = MUTABLE_BUFFER;
            
            ret -> vec = vec;
            ret -> mode = mode;
            
            ret -> target = GL_ARRAY_BUFFER;
            ret -> usage = GL_STREAM_DRAW;
            
            return ret;
        }
        
        static mutable_buffer* makeMutableRectBuffer(std::vector<point>* rects){
            return makeMutableArrayBuffer(GL_QUADS,rects);
        }
        
        static mutable_buffer* makeMutableLineBuffer(std::vector<point>* lines){
            return makeMutableArrayBuffer(GL_LINES,lines);
        }
        
        static mutable_buffer* makeMutableLineStripBuffer(std::vector<point>* lines){
            return makeMutableArrayBuffer(GL_LINE_STRIP,lines);
        }
        
        ** MAKE SHAPES **
        
        static vec4* makeBox(GLfloat x, GLfloat y, GLfloat n){
            return new point[4]{
                point(x,y,0,1),
                point(x+n,y,0,1),
                point(x+n,y+n,0,1),
                point(x,y+n,0,1)
            };
        }

    };
    
    bmap glGraphics::buffers;
    pmap glGraphics::programs;
    void (*glGraphics::animate)();
     */
    
}

#endif
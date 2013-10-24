//
//  gl_shaders.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_SHADERS_H_
#define _GL_SHADERS_H_

#include <map>

#include "l_util.h"
#include "l_io.h"

#include "gl_vec.h"
#include "gl_mat.h"

typedef std::map<const char*,GLuint>  glintmap;
typedef std::pair<const char*,GLuint> glintpair;


GLuint initShaders(const char*,const char*);

glintmap attribs;

void addAttrib(const char* name){
    attribs.insert(glintpair(name,0));
}

void sendAttrib(const char* name){
    glVertexAttribPointer(attribs.at(name),4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
}

glintmap uniforms;

void addUniform(const char* name){
    uniforms.insert(std::pair<const char*,GLuint>(name,0));
}
void sendUniformV(const char* name,vec4 val){
    glUniform4fv(uniforms.at(name),1,&val[X]);
}
void sendUniformM(const char* name,mat4 mat){
    glUniformMatrix4fv(uniforms.at(name), 1, GL_TRUE, &mat[0][X]);
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
    
}


GLuint loadShader(const char* file, GLenum type){
    //Read in the shader file
    GLchar* source = readFile(file);
    
    //Check if the file was successfully read
    if(source==NULL){
        #ifdef DEBUG
        xstrerr("Failed to read shader: ");
        xstrerr(file);
        #endif
        exit(EXIT_FAILURE);
    }
    
    //Make the new shader
    GLuint shader = glCreateShader(type);
    //Set the shader source code
    glShaderSource( shader,1,(const GLchar**)&source,NULL);
    //Compile the shader source
    glCompileShader(shader);
    
    //Check if the shader was properly compiled
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled){
        #ifdef DEBUG
        xstrerr("Failed to compile");
        xstrerr(file);
        GLint logSize;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
        char* logMsg = new char[logSize];
        glGetShaderInfoLog( shader, logSize, NULL, logMsg );
        xstrerr(logMsg);
        delete [] logMsg;
        #endif
        exit( EXIT_FAILURE );
    }
    
    //Get rid of the source file
    delete [] source;
    
    return shader;
}


GLuint initShaders(const char* vertexFile, const char* fragmentFile){
    
    //Create the program for the shaders
    GLuint program = glCreateProgram();
    
    //Attach the shaders after loading to the program
    glAttachShader(program,loadShader(vertexFile,  GL_VERTEX_SHADER));
    //glPrintError("VERTEXSHADER");
    glAttachShader(program,loadShader(fragmentFile,GL_FRAGMENT_SHADER));
    //glPrintError("FRAGMENTSHADER");
    
    //Link the program and check for errors
    glLinkProgram(program);
    //glPrintError("LINKPROGRAM");
    
    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    
    if ( !linked ) {
        #ifdef DEBUG
        xstrerr("Shader program failed to link");
        GLint logSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        xstrerr(logMsg);
        delete [] logMsg;
        #endif
        exit( EXIT_FAILURE );
    }
    
    return program;
    
}


#endif

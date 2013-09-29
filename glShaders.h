//
//  glShaders.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLSHADERS_H_
#define GLSHADERS_H_

#include "glFileio.h"

namespace gl{
    
    GLuint loadShader(const char* file, GLenum type){
        //Read in the shader file
        GLchar* source = readSource(file);
        
        //Check if the file was successfully read
        if(source==NULL){
#ifdef DEBUG
            std::cerr << "Failed to read shader: " << file << std::endl;
#endif
            exit(EXIT_FAILURE);
        }
        
        //Make the new shader
        GLuint shader = glCreateShader(type);
        //glPrintError("CREATESHADER");
        //Set the shader source code
        glShaderSource( shader,1,(const GLchar**)&source,NULL);
        //glPrintError("SHADERSOURCE");
        //Compile the shader source
        glCompileShader(shader);
        //glPrintError("COMPILE SHADER");
        
        //Check if the shader was properly compiled
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled){
#ifdef DEBUG
            std::cerr << "Failed to compile: " << file << std::endl;
            GLint logSize;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
            char* logMsg = new char[logSize];
            glGetShaderInfoLog( shader, logSize, NULL, logMsg );
            std::cerr << logMsg << std::endl;
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
            std::cerr << "Shader program failed to link" << std::endl;
            GLint logSize;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
            char* logMsg = new char[logSize];
            glGetProgramInfoLog( program, logSize, NULL, logMsg );
            std::cerr << logMsg << std::endl;
            delete [] logMsg;
#endif
            exit( EXIT_FAILURE );
        }
        
        return program;
        
    }

}

#endif

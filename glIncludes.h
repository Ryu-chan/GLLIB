//
//  glIncludes.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLINCLUDES_H_
#define GLINCLUDES_H_

#include <iostream>
#include <cmath>
#include <vector>

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

#ifdef __APPLE__
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif

#define print(x) do{ std::cout<<x<<std::endl; } while(0);

#define INT *sizeof(int)
#define CHAR *sizeof(char)

namespace gl{
    //Globals
    
    inline
    void glPrintError(const char* loc){
#ifdef DEBUG
        std::cout<<loc<<": "<<gluErrorString(glGetError())<<std::endl;
#endif
    }
}

#include "glMath.h"

#include "glFileio.h"

#include "glVec.h"
#include "glMat.h"

#include "glMesh.h"
#include "glModifiers.h"
#include "glPhysics.h"

#include "glShaders.h"
#include "glColor.h"
#include "glGraphics.h"

#include "glEvents.h"
#include "glFrame.h"

using namespace gl;

#endif

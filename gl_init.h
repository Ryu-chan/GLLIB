//
//  gl_init.h
//  opengl
//
//  Created by Chris on 10/17/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_INIT_H_
#define _GL_INIT_H_

#ifdef __APPLE__
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif

#include "l_util.h"

void glPrintError(const char* loc = "Undefined Location"){
    xstr(loc);
    xstr(": ");
    xstr((char*)gluErrorString(glGetError()));
    xstr("\n");
}

#endif

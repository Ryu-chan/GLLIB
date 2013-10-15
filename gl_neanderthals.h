//
//  gl_neanderthals.h
//  opengl
//
//  Created by Chris on 10/14/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_NEANDERTHALS_H_
#define _GL_NEANDERTHALS_H_

#include "gl_scene.h"
#include "gl_primitives.h"


Node* makeUnitCylinder(){
    
    mesh poly = polygon("internal_circle_faces",30);
    
    lace("internal_circle_sides",poly,vec4(0,0,-1,0));
    
    Node* nodes = new Node[4];
    
    mat4 m = mat4(1.0);
    
    nodes[0] = Node(m,NULL,NULL,&nodes[1]);
    
    nodes[1] = Node(m,[]()->void{
        fillPolygon("internal_circle_faces",30);
    },&nodes[2],NULL);
    
    nodes[3] = Node(m,[]()->void{
        draw(GL_QUAD_STRIP,"internal_circle_sides",60);
    },NULL,NULL);
    
    m = translate(0,0,-1.0);
    nodes[2] = Node(m,[]()->void{
        fillPolygon("internal_circle_faces",30);
    },&nodes[3],NULL);

    return &nodes[0];
    
}


#endif

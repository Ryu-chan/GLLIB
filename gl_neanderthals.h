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
#include "gl_modifiers.h"

#define TOP 1
#define WAL 2
#define BOT 3

Node* makeUnitPolygonCustom(const char* pref,int n,
            void(*top)(const char*,int),
            void(*bot)(const char*,int),
            void(*wal)(const char*,int),
            mesh& poly
){
    
    static char* faces = xstrconcat(pref,"_faces");
    static char* sides = xstrconcat(pref,"_sides");
    static unsigned int size = n;
    
    static void(*t)(const char*,int) = top;
    static void(*b)(const char*,int) = bot;
    static void(*w)(const char*,int) = wal;
    
    
    poly = polygon(faces,n);
    mesh lac  = lace(sides,poly,vec_4(0,0,-1,0));
    
    
    Node* nodes = (Node*)xmalloc(4*sizeof(Node));//new Node[4];
    
    mat4 m = mat_4(1.0);
    
    nodes[0] = Node(m,NULL,NULL,&nodes[TOP]);
    
    nodes[TOP] = Node(m,[]()->void{
        t(faces,size);
    },&nodes[BOT],NULL);
    
    nodes[WAL] = Node(m,[]()->void{
        w(sides,size*2+2);
    },NULL,NULL);
    
    m = translate(0,0,-1.0);
    nodes[BOT] = Node(m,[]()->void{
        b(faces,size);
    },&nodes[WAL],NULL);
    
    return &nodes[0];
}
Node* makeUnitPolygonSolid(const char* pref,unsigned int n,mesh& poly){
    return makeUnitPolygonCustom(pref,n,
         [](const char* ref,int n)->void{
             fillPolygon(ref,n);
         },
         [](const char* ref,int n)->void{
             fillPolygon(ref,n);
         },
         [](const char* ref,int n)->void{
             draw(GL_QUAD_STRIP,ref,n);
         },
        poly
    );
}
Node* makeUnitPolygonWire(const char* pref,int n,mesh& poly){
    return makeUnitPolygonCustom(pref,n,
         [](const char* ref,int n)->void{
             drawPolygon(ref,n);
         },
         [](const char* ref,int n)->void{
             drawPolygon(ref,n);
         },
         [](const char* ref,int n)->void{
             draw(GL_LINES,ref,n);
         },
        poly
    );
}


#endif

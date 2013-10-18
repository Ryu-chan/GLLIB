//
//  gl_scene.h
//  opengl
//
//  Created by Chris on 10/8/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_SCENE_H_
#define _GL_SCENE_H_

#include "glMat.h"
#include "l_data.h"

// NODE

typedef struct  s_node{
    
    mat4        transform;
    void        (*render)( void );
    s_node*     sibling;
    s_node*     child;
    
    s_node():
        render  (NULL),
        sibling (NULL),
        child   (NULL)
    {}
    
    s_node(mat4& _transform, void(*_render)(void), s_node* _sibling, s_node* _child):
        transform   (_transform),
        render      (_render),
        sibling     (_sibling),
        child       (_child)
    {}
    
}               Node;


// TRAVERSE NODES

mat4* model_view;
Stack mstack;

void traverseRecurse(Node* node){
    if(NULL!=node){
        mat4* new_view = (mat4*)xmalloc(sizeof(mat4));//new mat4(1);
        *new_view = mat4(1.0);
        
        *new_view *= *model_view;
        mstack.push(new_view);
        
        *model_view *= node->transform;
        
        if(node->render)
            node->render();
        
        if(node->child)
            traverseRecurse(node->child);
        
        model_view = (mat4*)mstack.pop();
        
        if(node->sibling)
            traverseRecurse(node->sibling);
        
    }
}
void traverse(Node* node,mat4 worldview){
    model_view = new mat4(1);
    *model_view *= worldview;
    traverseRecurse(node);
}

#endif

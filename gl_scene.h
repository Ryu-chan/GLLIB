//
//  gl_scene.h
//  opengl
//
//  Created by Chris on 10/8/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_SCENE_H_
#define _GL_SCENE_H_

#include "l_util.h"
#include "l_data.h"

#include "gl_mat.h"

// NODE

typedef struct  s_node{
    
    mat4        transform           = NULL;
    void        (*render)( void )   = NULL;
    s_node*     sibling             = NULL;
    s_node*     child               = NULL;
    
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

mat4 model_view;
Stack mstack;

void traverseRecurse(Node* node){
    if(NULL!=node){
        mat4 new_view = mat_4(1.0);
        mat_mul_eq(&new_view,model_view);
        
        mstack.push((void*)new_view);
        
        if(node->transform)
            mat_mul_eq(&model_view,node->transform);
        
        if(node->render)
            node->render();
        
        if(node->child)
            traverseRecurse(node->child);
        
        free(model_view);
        model_view = (mat4)mstack.pop();
        
        
        if(node->sibling)
            traverseRecurse(node->sibling);
        
    }
}
void traverse(Node* node){
    free(model_view);
    model_view = mat_4(1.0);
    traverseRecurse(node);
}

#endif

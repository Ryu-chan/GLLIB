//
//  data.h
//  opengl
//
//  Created by Chris on 10/17/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _L_DATA_H_
#define _L_DATA_H_

#include "l_util.h"

typedef struct  s_llnode{
    void*       elem;
    s_llnode*   next;
}               llnode;

typedef struct  s_linkedlist{
    llnode*     head;
    
    void add(void* elem){
        llnode* last = head;
        head = (llnode*)xmalloc(sizeof(llnode));
        head -> elem = elem;
        head -> next = last;
    }
    void* remove(){
        llnode* oh = head;
        void* e = oh->elem;
        
        head = head->next;
        
        free(oh);
        return e;
    }
}               LinkedList;

typedef struct  s_stack{
    
    LinkedList  stack;
    
    void push(void* elem){
        stack.add(elem);
    }
    void* pop(){
        return stack.remove();
    }
    void* peek(){
        return stack.head->elem;
    }
}               Stack;

#endif

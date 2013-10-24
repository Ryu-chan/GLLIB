//
//  l_io.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _L_IO_H_
#define _L_IO_H_

#include "l_util.h"

char* readFile(const char* file){
    FILE* fr = fopen(file,"r");
    if(fr == NULL) return NULL;
    
    char* buffer;
    int length;
    
    fseek(fr,0L,SEEK_END);
    length = (int)ftell(fr);
    fseek(fr,0L,SEEK_SET);
    
    buffer = (char*) xmalloc((length+1)*sizeof(char));
    fread(buffer,1,length,fr);
    
    buffer[length] = '\0';
    fclose(fr);
    
#ifdef DEBUG
    xstr(buffer);
#endif
    
    return buffer;
}


#endif

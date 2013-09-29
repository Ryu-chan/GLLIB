//
//  glFileio.h
//  opengl
//
//  Created by Chris on 9/4/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLFILEIO_H_
#define GLFILEIO_H_

namespace gl{
    
    char* readSource(const char* file){
        FILE* fr = fopen(file,"r");
        if(fr == NULL) return NULL;
        
        char* buffer;
        long length;
        
        fseek(fr,0L,SEEK_END);
        length = ftell(fr);
        fseek(fr,0L,SEEK_SET);
        
        buffer = (char*) malloc((length+1)*sizeof(char));
        fread(buffer,1,length,fr);
        
        buffer[length] = '\0';
        fclose(fr);
        
#ifdef DEBUG
        std::cout << buffer << std::endl;
#endif
        
        return buffer;
    }
    
}

#endif

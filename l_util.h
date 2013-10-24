//
//  l_util.h
//  opengl
//
//  Created by Chris on 10/17/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _L_UTIL_H_
#define _L_UTIL_H_

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#include <stdlib.h>
#include <unistd.h>

/* CHAR */
void        xchar(
    char    c
){
    
	write(1,&c,1);
	
}
void        xendl(){
    xchar('\n');
}
void        xcharfd(
    char    c,
    int     fd
){
    
	write(fd,&c,1);
	
}

/* STR */
void            xstr(
    const char* str
){
	if (str != NULL)
		while(*str != '\0')
			xchar( *(str++) );
}
void            xstrfd(
    const char* str,
    int         fd
){
    if (str != NULL)
        while(*str != '\0')
            xcharfd( *(str++), fd);
}
void            xstrerr(
    const char* str
){
    xstrfd(str,2);
}

/* INT */
void 			xint(
    int 		n
){
	unsigned int 	i;
    
	i = (n < 0) ? -n : n;
	
	if (n < 0)
		xchar('-');
	
	for (n = 1; n <= (i / 10); n *= 10)
		;
	
	for (; n; i %= n, n /= 10)
		xchar('0' + (i / n));
}

/* MALLOC */
void* 		xmalloc(
    int 	n
){
	void* 	p;
    
	p = malloc(n);
	
	if (p == 0){
		xstr("Virtual Memory Exhausted\n");
		exit(1);
	}
	
	return p;
}

/* STR METHODS */

int                 xstrlen(
    const char* 	str
){
	int 	i;
	
	i = 0;
    
	if (str != NULL)
		while ( *(str++) != '\0')
			i++;
	return i;
}

char*               xstrconcat(
    const char* 	s1,
    const char* 	s2
){
	char* 	str;
	int 	loc;
	
	str = (char*) xmalloc(xstrlen(s1) + xstrlen(s2) + 1);
	loc = 0;
	
	if (s1 != NULL)
		while (*s1 != '\0')
			str[loc++] = *(s1++);
	
	if (s2 != NULL)
		while (*s2 != '\0')
			str[loc++] = *(s2++);
	
	str[loc] = '\0';
	
	return ( (void*)s1 == NULL && (void*)s2 == NULL) ? (char*)NULL : str;
}

#endif

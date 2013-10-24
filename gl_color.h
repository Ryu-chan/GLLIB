//
//  gl_color.h
//  opengl
//
//  Created by Chris on 10/19/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef _GL_COLOR_H_
#define _GL_COLOR_H_

typedef vec4 color;


color makeRGBA(GLuint r,GLuint g,GLuint b,GLfloat a){
    return vec_4(
         r/255.0,
         g/255.0,
         b/255.0,
         a
    );
}

color makeRGB(GLuint r,GLuint g,GLuint b){
    return makeRGBA(r,g,b,1.0);
}

color makeHSB(float hue,float saturation,float brightness){
    GLuint r=0,g=0,b=0;
    if(saturation==0){
        r=g=b=(GLuint)(brightness*255.0+0.5);
    }else{
        GLfloat
        h = (hue - (GLfloat)floor(hue)) * 6.0,
        f = h - (GLfloat)floor(h),
        p = brightness * (1.0 - saturation),
        q = brightness * (1.0 - saturation * f),
        t = brightness * (1.0 - (saturation * (1.0 - f)))
        ;
        switch((GLuint)h){
            case 0:
                r = (GLuint)(brightness * 255.0 + 0.5);
                g = (GLuint)(t * 255.0 + 0.5);
                b = (GLuint)(p * 255.0 + 0.5);
                break;
            case 1:
                r = (GLuint)(q * 255.0 + 0.5);
                g = (GLuint)(brightness * 255.0 + 0.5);
                b = (GLuint)(p * 255.0 + 0.5);
                break;
            case 2:
                r = (GLuint)(t * 255.0 + 0.5);
                g = (GLuint)(p * 255.0 + 0.5);
                b = (GLuint)(brightness * 255.0 + 0.5);
                break;
            case 3:
                r = (GLuint)(p * 255.0 + 0.5);
                g = (GLuint)(q * 255.0 + 0.5);
                b = (GLuint)(brightness * 255.0 + 0.5);
                break;
            case 4:
                r = (GLuint)(t * 255.0 + 0.5);
                g = (GLuint)(p * 255.0 + 0.5);
                b = (GLuint)(brightness * 255.0 + 0.5);
                break;
            case 5:
                r = (GLuint)(brightness * 255.0 + 0.5);
                g = (GLuint)(p * 255.0 + 0.5);
                b = (GLuint)(q * 255.0 + 0.5);
                break;
        }
    }
    
    return makeRGB(r,g,b);
}

color opacify(GLfloat percent,color a){
    a[W] *= percent;
    return a;
}

#define COLOR_FLAT_RED            makeRGB(231, 76, 60)
#define COLOR_FLAT_DARKRED        makeRGB(192, 57, 43)
#define COLOR_FLAT_ORANGE         makeRGB(230,126, 34)
#define COLOR_FLAT_DARKORANGE     makeRGB(211, 84,  0)
#define COLOR_FLAT_YELLOW         makeRGB(241,196, 15)
#define COLOR_FLAT_DARKYELLOW     makeRGB(243,156, 18)
#define COLOR_FLAT_GREEN          makeRGB( 46,204,113)
#define COLOR_FLAT_DARKGREEN      makeRGB( 39,174, 96)
#define COLOR_FLAT_TURQOISE       makeRGB( 26,188,156)
#define COLOR_FLAT_DARKTURQOSE    makeRGB( 22,160,133)
#define COLOR_FLAT_BLUE           makeRGB( 52,152,219)
#define COLOR_FLAT_DARKBLUE       makeRGB( 41,128,185)
#define COLOR_FLAT_PURPLE         makeRGB(155, 89,182)
#define COLOR_FLAT_DARKPURPLE     makeRGB(142, 68,173)
#define COLOR_FLAT_BLACK          makeRGB( 52, 73, 94)
#define COLOR_FLAT_DARKBLACK      makeRGB( 44, 62, 80)
#define COLOR_FLAT_GREY           makeRGB(149,165,166)
#define COLOR_FLAT_DARKGREY       makeRGB(149,165,166)
#define COLOR_FLAT_WHITE          makeRGB(236,240,241)
#define COLOR_FLAT_DARKWHITE      makeRGB(189,195,199)

void color_print(color c){
    xstr("Color:");
    vec_print(c);
}

void setBackground(color c){
    glClearColor(c[X],c[Y],c[Z],c[W]);
}
void setColor(color c){
    sendUniformV("color",c);
}

#endif

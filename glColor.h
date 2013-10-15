//
//  glColor.h
//  opengl
//
//  Created by Chris on 9/3/13.
//  Copyright (c) 2013 Ryuichi. All rights reserved.
//

#ifndef GLCOLOR_H_
#define GLCOLOR_H_

namespace gl{
    
    class glColor{
    private:
        GLuint value;
    public:
        glColor(GLuint r,GLuint g,GLuint b)
            :glColor(r,g,b,255)
        {}
        glColor(GLuint r,GLuint g,GLuint b,GLuint a)
            :glColor(((a & 0xFF) << 24) |
                     ((r & 0xFF) << 16) |
                     ((g & 0xFF) << 8)  |
                     ((b & 0xFF) << 0))
        {}
        glColor(GLfloat r,GLfloat g,GLfloat b)
            :glColor((GLuint)(r*255+0.5),(GLuint)(g*255+0.5),(GLuint)(b*255+0.5),255)
        {}
        glColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
            :glColor((GLuint)(r*255+0.5),(GLuint)(g*255+0.5),(GLuint)(b*255+0.5),(GLuint)(a*255+0.5))
        {}
        glColor(GLuint val)
            :value(val)
        {}
        
        
        GLuint getRGBA(){
            return value;
        }
        GLuint getRed(){
            return (value>>16) & 0xFF;
        }
        GLuint getGreen(){
            return (value>>8) & 0xFF;
        }
        GLuint getBlue(){
            return (value>>0) & 0xFF;
        }
        GLuint getAlpha(){
            return (value>>24) & 0xFF;
        }
        
    
        glColor brighter(){
            return brighter((GLfloat)0.1);
        }
        glColor brighter(GLfloat percent){
            return brighter(255*percent);
        }
        glColor brighter(GLuint amt){
            return glColor(
                getRed()+amt,
                getGreen()+amt,
                getBlue()+amt,
                getAlpha()
            );
        }
        
        glColor darker(){
            return darker((GLfloat)0.1);
        }
        glColor darker(GLfloat percent){
            return darker(255*percent);
        }
        glColor darker(GLuint amt){
            return glColor(
                getRed()-amt,
                getGreen()-amt,
                getBlue()-amt,
                getAlpha()
            );
        }
        
        glColor greyscale(){
            GLuint scale = ((getRed()+getGreen()+getBlue()) / 3.0);
            return glColor(scale,scale,scale,getAlpha());
        }
        
        glColor opacify(GLuint a){
            return glColor(getRed(),getGreen(),getBlue(),a);
        }
        glColor opacify(GLfloat a){
            return glColor(getRed(),getGreen(),getBlue(),a*255+0.5);
        }
        
        
        static GLuint HSBtoRGB(float hue,float saturation,float brightness){
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
            
            return 0xff000000 | (r << 16) | (g << 8) | (b << 0);
        }
        
        static glColor makeRGB(GLuint r,GLuint g,GLuint b){
            return glColor(r,g,b);
        }
        static glColor makeRGBA(GLuint r,GLuint g,GLuint b,GLuint a){
            return glColor(r,g,b,a);
        }
        static glColor makeHSB(GLfloat h,GLfloat s,GLfloat b){
            return glColor(HSBtoRGB(h,s,b));
        }
        
        friend std::ostream& operator << ( std::ostream& os, glColor& c ) {
            return os << "glColor( " << c.getRed() << ", " << c.getGreen()
            << ", " << c.getBlue() << ", " << c.getAlpha() << " )";
        }
        
        
        
        /** CONSTANTS **/
        static glColor
            RED,
            DARKRED,
            ORANGE,
            DARKORANGE,
            YELLOW,
            DARKYELLOW,
            GREEN,
            DARKGREEN,
            TURQOISE,
            DARKTURQOISE,
            BLUE,
            DARKBLUE,
            PURPLE,
            DARKPURPLE,
            BLACK,
            DARKBLACK,
            GREY,
            DARKGREY,
            WHITE,
            DARKWHITE;

    };
    
    glColor
        glColor::RED             = glColor( (GLuint) 231,  76,  60),
        glColor::DARKRED         = glColor( (GLuint) 192,  57,  43),
        glColor::ORANGE          = glColor( (GLuint) 230, 126,  34),
        glColor::DARKORANGE      = glColor( (GLuint) 211,  84,   0),
        glColor::YELLOW          = glColor( (GLuint) 241, 196,  15),
        glColor::DARKYELLOW      = glColor( (GLuint) 243, 156,  18),
        glColor::GREEN           = glColor( (GLuint)  46, 204, 113),
        glColor::DARKGREEN       = glColor( (GLuint)  39, 174,  96),
        glColor::TURQOISE        = glColor( (GLuint)  26, 188, 156),
        glColor::DARKTURQOISE    = glColor( (GLuint)  22, 160, 133),
        glColor::BLUE            = glColor( (GLuint)  52, 152, 219),
        glColor::DARKBLUE        = glColor( (GLuint)  41, 128, 185),
        glColor::PURPLE          = glColor( (GLuint) 155,  89, 182),
        glColor::DARKPURPLE      = glColor( (GLuint) 142,  68, 173),
        glColor::BLACK           = glColor( (GLuint)  52,  73,  94),
        glColor::DARKBLACK       = glColor( (GLuint)  44,  62,  80),
        glColor::GREY            = glColor( (GLuint) 149, 165, 166),
        glColor::DARKGREY        = glColor( (GLuint) 127, 140, 141),
        glColor::WHITE           = glColor( (GLuint) 236, 240, 241),
        glColor::DARKWHITE       = glColor( (GLuint) 189, 195, 199);
    
}

#endif

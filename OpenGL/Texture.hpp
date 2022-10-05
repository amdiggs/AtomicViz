//
//  Texture.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/2/22.
//

#ifndef Texture_hpp
#define Texture_hpp
#define IW 64
#include <stdio.h>
#include "Render.hpp"
#include "My_Types.hpp"

class Atom;

class Texture{
private:
    unsigned int m_ID;
    unsigned int m_TBO;
    unsigned int m_TEX_ID;
    GLenum m_type = GL_TEXTURE_2D;
    GLubyte RGB_Data[IW][IW][3];
    GLubyte RGBA_Data[IW][IW][4];
    GLfloat TBData[500][3];
    
    
public:
    Texture();
    Texture(Atom* ats);
    ~Texture();
    
    void bind(int layer);
    void Checker_Board();
    void Noise();
    void Off_set(Atom* ats);
    
    
    
};




class Rand{
public:
    Rand(const Rand&) = delete;
    
    static Rand& Get();
    double r_u_d(double, double);
    int r_uni_int(int, int);
    int rand_color();
    double rand_normal_color();
    double return_rate();
    double escape_rate();
    double get_time(double);
    
    void set_temp(float temp);
private:
    Rand() {}
    float m_temp;
    

};



#endif /* Texture_hpp */

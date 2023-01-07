//
//  Texture.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/2/22.
//

#ifndef Texture_hpp
#define Texture_hpp
#define IW 128



#include <stdio.h>
#include "Render.hpp"
#include "My_Types.hpp"

class Atom;
class Shader;
const std::string SRCS =  "/Users/diggs/Desktop/OpenGL/OTHER/";
class Texture{
private:
    enum Tex_Type{Noise = 1, Gaussian, Image};
    unsigned int m_ID[10];
    GLenum m_type = GL_TEXTURE_2D;
    void Gen_Tex_2D(int layer, void* dat, int rows, int cols);
    int m_count = 0;
    
    
public:
    Texture();
    
    ~Texture();
    
    void Bind(int layer);
    void UnBind();
    void Gen_Noise(int layer);
    void Gen_Gauss(int layer);
    void Image_Texture(int layer,std::string image);
    void Image_Texture_RGB(int layer,std::string image);
    
    
    int Get_ID(int layer);
    
    
    
    
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

float Letter_Check(int i, int j, char let);
void X_hat(GLubyte (*dat)[128][4]);
void Y_hat(GLubyte (*dat)[128][4]);
void Z_hat(GLubyte (*dat)[128][4]);
#endif /* Texture_hpp */


//void bind_multi(int layer);
//void axis_texture(int layer,const Shader& sh);
//void Off_set(Atom* ats,const Shader& sh);
//void Gen_Gaussian(int layer,const Shader& sh);


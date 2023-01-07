//
//  Texture.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/2/22.
//

#include "Texture.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include "Atomic.hpp"
#include "shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern int num_atoms;

static unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
std::minstd_rand0 gen (seed);
std::uniform_int_distribution<> color(0,255);


Texture::Texture(){}

Texture::~Texture() {
    for (int i = 0; i<m_count; i++){
    glDeleteTextures(1, &m_ID[i]);
    }
    //glDeleteTextures(1, &m_ID[1]);
    //glDeleteBuffers(1, &m_TBO);
    //glDeleteTextures(1, &m_TEX_ID);
}

void Texture::Bind(int layer) {
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, m_ID[layer]);
}




void Texture::Gen_Noise(int layer){
    GLubyte RGBA_Data[IW][IW][4];
    int value= 100;
    for (int i = 0; i< IW; i++){
        for (int j= 0; j<IW; j++){
            value = Rand::Get().r_uni_int(150, 255);
            
            RGBA_Data[i][j][0] = value;
            RGBA_Data[i][j][1] = value;
            RGBA_Data[i][j][2] = value;
            RGBA_Data[i][j][3] = value;
            
        }
    }
    Gen_Tex_2D(layer,(void*)RGBA_Data, IW, IW);
}

void Texture::Gen_Gauss(int layer) {
    GLubyte RGBA_Data[IW][IW][4];
    int value;
    float x,y, rs;
    float sigma = 0.35;
    for (int i = 0; i< IW; i++){
        y = float(i)/float(IW);
        for (int j= 0; j<IW; j++){
            x = float(j)/float(IW);
            rs = (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5);
            value = (int)(sin(5*x)*exp((-rs)/sigma)*255.0);
            
            RGBA_Data[i][j][0] = value;
            RGBA_Data[i][j][1] = value;
            RGBA_Data[i][j][2] = value;
            if (value > 25){
                RGBA_Data[i][j][3] = value;
            }
            else{RGBA_Data[i][j][3] = 0;}
            
        }
    }
    Gen_Tex_2D(layer,(void*)RGBA_Data, IW, IW);
    
}




void Texture::Gen_Tex_2D(int layer, void* dat, int rows, int cols){
    
    glGenTextures(1, &m_ID[layer]);
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, m_ID[layer]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, rows, cols, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_count++;
    
}

void Texture::Image_Texture(int layer, std::string image) {
    int w, h, bpp;
    std::string _file = SRCS + image;
    unsigned char* image_data = stbi_load(_file.c_str(), &w, &h, &bpp, 0);
    
    if(!image_data){
        std::cout << "COULD NOT LOAD IMAGE " << _file << std::endl;
        exit(2);
    }
    
    Gen_Tex_2D(layer, (void*)image_data, w, h);
}



void Texture::Image_Texture_RGB(int layer, std::string image) {
    int w, h, bpp;
    stbi_set_flip_vertically_on_load(true);
    std::string _file = SRCS + image;
    unsigned char* image_data = stbi_load(_file.c_str(), &w, &h, &bpp, 0);
    
    if(!image_data){
        std::cout << "COULD NOT LOAD IMAGE " << _file << std::endl;
        exit(2);
    }
    
    glGenTextures(1, &m_ID[layer]);
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, m_ID[layer]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_count++;
}

int Texture::Get_ID(int layer){
    return m_ID[layer];
}

void Texture::UnBind() { 
    glBindTexture(GL_TEXTURE_2D, 0);
}



/*
 void Texture::bind_multi(int layer) {
     glActiveTexture(GL_TEXTURE0 + layer);
     glBindTexture(GL_TEXTURE_2D, m_ID[layer]);
     glActiveTexture(GL_TEXTURE0 + layer + 1);
     glBindTexture(GL_TEXTURE_2D, m_ID[layer +1]);
     glActiveTexture(GL_TEXTURE0 + layer + 2);
     glBindTexture(GL_TEXTURE_2D, m_ID[layer +2]);
     glUniform1iv(multi_loc,3, samplers);
 }
 
 
 void Texture::Off_set(Atom* ats, const Shader& sh){
     GLfloat TBData[500][4];
     u_locs[0] = sh.UniformLoc("off_set");
     AMD::Vec3 temp;
     for (int i = 0; i< num_atoms; i++){
         temp = ats[i].get_coords();
         TBData[i][0] =temp.x;
         TBData[i][1] = temp.y;
         TBData[i][2] = temp.z;
         TBData[i][3] = float(ats[i].get_type());
             
         
     }
     
     glGenBuffers(1,&m_TBO);
     glBindBuffer(GL_TEXTURE_BUFFER, m_TBO);
     glBufferData(GL_TEXTURE_BUFFER, sizeof(TBData), TBData, GL_STATIC_DRAW);
     
     glGenTextures(1, &m_TEX_ID);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_BUFFER, m_TEX_ID);
     glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA32F, m_TBO);
     
     glBindBuffer(GL_TEXTURE_BUFFER, 0);
     glUniform1i(u_locs[0], 0);
     
 }
 
 void Texture::axis_texture(int layer, const Shader& sh) {
     int row = 128; int col = 128;
     GLubyte RGBA_Data[128][128][4];
     //u_locs[layer] = sh.UniformLoc("Axis_Texture");
     multi_loc = sh.UniformLoc("Axis_Texture");
     X_hat(RGBA_Data);
     Gen_Tex_2D(layer,(void*)RGBA_Data, row, col);
     Y_hat(RGBA_Data);
     Gen_Tex_2D(layer+1,(void*)RGBA_Data, row, col);
     Z_hat(RGBA_Data);
     Gen_Tex_2D(layer+2,(void*)RGBA_Data, row, col);
     glUniform1iv(multi_loc,3, samplers);
 }
 
 void Texture::Gen_Gaussian(int layer, const Shader &sh) {
     GLubyte RGBA_Data[IW][IW][4];
     int value;
     float x,y, rs;
     float sigma = 0.1;
     for (int i = 0; i< IW; i++){
         y = float(i)/float(IW);
         for (int j= 0; j<IW; j++){
             x = float(j)/float(IW);
             rs = (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5);
             value = (int)(exp((-rs)/sigma)*255.0);
             
             RGBA_Data[i][j][0] = value;
             RGBA_Data[i][j][1] = value;
             RGBA_Data[i][j][2] = value;
             if (value > 25){
                 RGBA_Data[i][j][3] = value;
             }
             else{RGBA_Data[i][j][3] = 0;}
             
         }
     }
     Gen_Tex_2D(layer,(void*)RGBA_Data, IW, IW);
     
 }


 */

Rand& Rand::Get(){
    static Rand inst;
    return inst;
}

double Rand::r_u_d(double lb, double ub){
    std::uniform_real_distribution<double> test_dist(lb, ub);
    return test_dist(gen);
    
}


double Rand::rand_normal_color(){
    std::normal_distribution<double> trap(2.0, 0.2);
    double val =  trap(gen);
    if (val > 4.0){
        val = 4.0;
    }
    
    else if (val < 0.0){
        val = 0.0;
    }
    
    return val/4.0;
}

double Rand::return_rate(){
    std::exponential_distribution<double> ret(0.4);
    return ret(gen);
}

double Rand::escape_rate(){
    std::normal_distribution<double> esc(0.6, 0.2);
    return esc(gen);
}

double Rand::get_time(double rt){
    double tau = Rand::Get().r_u_d(0.0, 1.0);
    return (1.0/rt)*log(1.0/tau);
    
}


int Rand::r_uni_int(int lb, int ub){
    std::uniform_int_distribution<> l_int(lb,ub);
    return l_int(gen);
}



int Rand::rand_color(){return color(gen);}


float Letter_Check(int i, int j, char lett){
    float x = float(j);
    float y = float(abs(64 - i));
    float w,z;
    switch (lett) {
        case 'x':
            if (j<1 || j > 64) {
                return 0.0;
            }
            w = abs((2.0*x)-y)/10.0;
            z = abs(((2.0*x)-64) + y)/10.0;
            if (z >1.0){
                z = 1.0;
            }
            if(w>1.0){
                w= 1.0;
            }
            return (2.0 - (z + w));

            break;
            
        default:
            return 0.0;
            break;
    }
    
    
    
}



void X_hat(GLubyte (*dat)[128][4]){
    int row = 128; int col = 128;
    int value = 255;
    for (int i = 0; i< row; i++){
        for (int j= 0; j<col; j++){
            if (i<=64){
                if(i>36){
                    if(j>24 && j<106){
                        if((abs(2*i - (j+10)) <= 2) || (abs(2*(i-64) + (j-10)) <= 2)){value = 0;}
                        else{value=255;}
                    }
                    else{value=255;}
                }
            }
            else if(i== 65 || i ==66 || i == 67 || i == 68 || i>122){
                if((j>26&& j<44) || (j > 82 && j<100)){
                    value = 0;
                }
                    else{value=255;}
                }
            else if(abs(i - (j+32)) <=2 || abs((i-128) + (j-32)) <=2){
                value = 0;
            }
            else{value = 255;}
            dat[i][j][0] = 255 - value;
            dat[i][j][1] = 255 - value;
            dat[i][j][2] = 255 - value;
            dat[i][j][3] = 255 - value;
            
        }
        
        
        

    }
}


void Y_hat(GLubyte (*dat)[128][4]){
    int row = 128; int col = 128;
    int value = 255;
    for (int i = 0; i< row; i++){
        for (int j= 0; j<col; j++){
            if (i<=64){
                if(i>36){
                    if(j>24 && j<106){
                        if((abs(2*i - (j+10)) <= 2) || (abs(2*(i-64) + (j-10)) <= 2)){value = 0;}
                        else{value=255;}
                    }
                    else{value=255;}
                }
            }
            else if (i>96){
                if (j>61 && j<67) {value = 0;}
                else{value=255;}
            }
            else if(i== 65 || i ==66 || i == 67 || i == 68){
                if((j>26&& j<44) || (j > 82 && j<100)){
                    value = 0;
                }
                    else{value=255;}
                }
            else if(abs(i - (j+32)) <=2 || abs((i-128) + (j-32)) <=2){
                value = 0;
            }
            else{value = 255;}
            dat[i][j][0] = 255 - value;
            dat[i][j][1] = 255 - value;
            dat[i][j][2] = 255 - value;
            dat[i][j][3] = 255 - value;
            
        }
        
        
        

    }
}



void Z_hat(GLubyte (*dat)[128][4]){
    int row = 128; int col = 128;
    int value = 255;
    for (int i = 0; i< row; i++){
        for (int j= 0; j<col; j++){
            if (i<=64){
                if(i>36){
                    if(j>30 && j<106){
                        if((abs(2*i - (j+10)) <= 2) || (abs(2*(i-64) + (j-10)) <= 2)){value = 0;}
                        else{value=255;}
                    }
                    else{value=255;}
                }
            }
            else if((i>64 && i<69) || (i>118 && i<123)){
                if(j>26 && j<96){value = 0;}
                else{value=255;}
                }
            else if(abs(i - (j+32)) <=2 && i<119){value = 0;}
            else{value = 255;}
            dat[i][j][0] = 255 - value;
            dat[i][j][1] = 255 - value;
            dat[i][j][2] = 255 - value;
            dat[i][j][3] = 255 - value;
            
        }
        
        
        

    }
}

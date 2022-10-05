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

extern int num_atoms;

static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::minstd_rand0 gen (seed);
std::uniform_int_distribution<> color(0,255);


Texture::Texture(Atom* ats) {
    
    Off_set(ats);
    Noise();
    

}

Texture::~Texture() { 
    glDeleteTextures(1, &m_ID);
}

void Texture::bind(int layer) { 
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Checker_Board() { 
    int value;
    bool r= true;
    bool c  = true;
    for (int i = 0; i< IW; i++){
        if(!(i%8)){
            r = (r == false);
        }
        for (int j= 0; j<IW; j++){
            if (!(j%8)) {
                c = (c == false);
            }
            value = int(c==r) * 255;
            RGBA_Data[i][j][0] = value;
            RGBA_Data[i][j][1] = value;
            RGBA_Data[i][j][2] = value;
            RGBA_Data[i][j][3] = value;
            
        }
    }
}


void Texture::Noise(){
    
    int value;
    for (int i = 0; i< IW; i++){
        for (int j= 0; j<IW; j++){
            value = (int)(Rand::Get().rand_normal_color()*255.0);
            //RGBA_Data[i][j][0] = Rand::Get().rand_color();
            //RGBA_Data[i][j][1] = Rand::Get().rand_color();
            //RGBA_Data[i][j][2] = Rand::Get().rand_color();
            //RGBA_Data[i][j][3] = Rand::Get().rand_color();
            
            RGBA_Data[i][j][0] = value;
            RGBA_Data[i][j][1] = value;
            RGBA_Data[i][j][2] = value;
            RGBA_Data[i][j][3] = value;
            
        }
    }
    
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, IW, IW, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA_Data);
    glBindTexture(GL_TEXTURE_2D, 0);

    
}


void Texture::Off_set(Atom* ats){
    AMD::Vec3 temp;
    for (int i = 0; i< num_atoms; i++){
        temp = ats[i].get_coords();
        TBData[i][0] =temp.x;
        TBData[i][1] = temp.y;
        TBData[i][2] = temp.z;
            
        
    }
    
    glGenBuffers(1,&m_TBO);
    glBindBuffer(GL_TEXTURE_BUFFER, m_TBO);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(TBData), TBData, GL_STATIC_DRAW);
    
    glGenTextures(1, &m_TEX_ID);
    glBindTexture(GL_TEXTURE_BUFFER, m_TEX_ID);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGB32F, m_TBO);
    
    glBindBuffer(GL_TEXTURE_BUFFER, 0);
    
}


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







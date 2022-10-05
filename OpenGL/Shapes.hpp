//
//  Shapes.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/14/22.
//

#ifndef Shapes_hpp
#define Shapes_hpp

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "My_Types.hpp"


#define _2pi 6.283185307

#define PI_2 1.5707963







class SHAPE{
private:
    static const unsigned int max_verts = 10000;
    static const unsigned int max_indices = 50000;
protected:
    int m_num_idx;
    int m_num_verts;
public:
    SHAPE();
    ~SHAPE();
    AMD::Vertex verts[max_verts];
    unsigned int indices[max_indices];
    int num_idx();
    int num_verts();
    
    
};



class Circle{
private:
    size_t m_i_size;
    size_t m_p_size;
    
public:
    unsigned int num_points;
    float rad;
    AMD::Vec3* points;
    unsigned int* indices;
    Circle(float ex_rad, unsigned int num);
    ~Circle();
    
    void Gen_points();
    void Gen_indices();
    size_t get_size(char typ);
    
};



class Cube{
private:
    unsigned int num_points = 8;
    int m_num_idx = 36;
    int m_num_verts = 8;

    void set_verts();
    
    
    
public:
    Cube();
    ~Cube();
    AMD::Vertex verts[8];
    unsigned int indices[36] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
    };
    
    int num_idx();
    int num_verts();
    
    
    
    
};

class Triangle{
private:
    void gen_verts();
    int m_num_verts = 3;
    int m_num_idx = 3;
public:
    Triangle();
    AMD::Vertex verts[3];
    unsigned int indices[3] = {0,1,2};
    int num_idx();
    int num_verts();
};




class Sphere{
private:
    static const unsigned int max_verts = 10000;
    static const unsigned int max_indices = 50000;
    float rad;
    unsigned int num_p;
    int m_num_idx;
    int m_num_verts;
    void gen_points();
    void gen_indices();
    
public:
    Sphere(float e_rad, unsigned int e_num_p);
    ~Sphere();
    AMD::Vertex verts[max_verts];
    unsigned int indices[max_indices];
    int num_idx();
    int num_verts();
    
    AMD::Vec4 m_clr;
    
    
    
};



class Grid{
    
private:
    static const unsigned int max_verts = 50000;
    static const unsigned int max_indices = 250000;
    float m_spacing;
    int m_num_points;
    int m_num_line_idx;
    int m_num_tri_idx;
    int m_num_verts;
    void gen_points();
    void gen_line_indices();
    void gen_tri_indices();
    void add_norm();
    
public:
    Grid(float e_spaceing);
    Grid(std::string file_name);
    ~Grid();
    AMD::Vertex verts[max_verts];
    unsigned int L_indices[max_indices];
    unsigned int T_indices[max_indices];
    int num_idx(char type);
    int num_verts();
    
};





class Cylinder{
private:
    static const unsigned int max_verts = 10000;
    static const unsigned int max_indices = 50000;
    const int m_num_theta = 20;
    float m_dz = 0.1;
    float m_dth = 0.314159;
    float m_rad;
    int m_num_idx;
    int m_num_verts;
    void gen_points();
    void gen_indices();
    
    float m_len;
    
public:
    Cylinder(float e_len, int e_num_th, int e_num_h);
    Cylinder();
    ~Cylinder();
    AMD::Vertex verts[max_verts];
    unsigned int indices[max_indices];
    int num_idx();
    int num_verts();
    
};


class Cone{
private:
    static const unsigned int max_verts = 10000;
    static const unsigned int max_indices = 50000;
    const int m_num_theta = 20;
    int m_num_idx;
    int m_num_verts;
    void gen_points();
    void gen_indices();
    
    
public:
    Cone();
    ~Cone();
    AMD::Vertex verts[max_verts];
    unsigned int indices[max_indices];
    int num_idx();
    int num_verts();
    
    
    
};



class Arrow {
    
private:
    static const unsigned int max_verts = 10000;
    static const unsigned int max_indices = 50000;
    const int m_num_theta = 20;
    int m_num_idx;
    int m_num_verts;
    void gen_points();
    void gen_indices();
    AMD::Vec4 m_color;
    AMD::Mat4 r_mat;
    void Coordinate_Transform();
    void Rotation();
    
    
public:
    Arrow(char color);
    Arrow(char color, char dir);
    ~Arrow();
    AMD::Vertex verts[max_verts];
    unsigned int indices[max_indices];
    int num_idx();
    int num_verts();
    
    
};


void ReadXYZ(std::string in_file, AMD::Vertex* verts, int& num_verts);
AMD::Vec3 Normed_average(AMD::Vec3 Va, AMD::Vec3 Vb);


#endif /* Shapes_hpp */

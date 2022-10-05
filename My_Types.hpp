//
//  My_Types.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 9/18/22.
//

#ifndef My_Types_hpp
#define My_Types_hpp

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

namespace AMD {

struct Vec2{
    float x,y;
    Vec2(float x, float y);
    Vec2();
    ~Vec2();
    
    
    Vec2 add(const Vec2& other) const;
    float& operator[](const int index);
    float* get();
    
    float dot(const Vec2& other) const;
    float len() const;
    
    
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2& operator=(const Vec2& other);
    Vec2 operator*(float scale);
    Vec2 operator/(float div);
    Vec2 operator+=(const Vec2& other);
    Vec2 operator*=(float scale);
    void print();
    
    
    
    
};


struct Vec3{
    float x,y,z;
    Vec3();
    Vec3(float e_x, float e_y, float e_z);
    
    Vec3 add(const Vec3& other) const;
    float& operator[](const int index);
    float* get();
    
    float dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    float len() const;
    
    
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3& operator=(const Vec3& other);
    Vec3 operator*(float scale);
    Vec3 operator/(float div);
    Vec3 operator+=(const Vec3& other);
    Vec3 operator*=(float scale);
    void print();
    
    
};


struct Vec4{
    float r,g,b,a;
    Vec4();
    Vec4(float e_r, float e_g, float e_b, float e_a);
    Vec4(float* e_vec);
    
    
    float* get();
    float& operator[](const int& index);
    //Vec4 operator*(float scale);
    //const float operator[](const int& index);
    
};



struct Vertex{
    Vec3 pos;
    Vec4 clr;
    Vec3 norm;
    Vec2 texture;
    int index;
    
};

struct Mat4{
    float m[4][4];
    Mat4();
    
    
    float* operator[](const int& index);
    Mat4& operator=(const Mat4& other);
    Mat4 add(const Mat4& other) const;
    Mat4 operator+(const Mat4& other) const;
    
    Mat4 multiply(const Mat4& other) const;
    Mat4 operator*(const Mat4& other) const;
    Vec4 multiply(Vec4& other) const;
    Vec4 operator*(Vec4& other) const;
    Vec3 operator*(Vec3& other) const;
    
    void assign_col(int col_idx, Vec4 col);
    void assign_row(int row_idx, Vec4 row);
    
    void Rotate(Vec3 ang);
    
    void print();
};

Mat4 ID();

Mat4 ROTATION_MATRIX(Vec3 ang);

float Get_angle(const Vec3& A, const Vec3& B);

void Compute_norms(Vertex* verts,unsigned int* ints, int num);

void Map_Texture_Coords(Vertex* verts, int num_verts);

}




#endif /* My_Types_hpp */

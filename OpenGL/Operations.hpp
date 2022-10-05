//
//  Operations.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/3/22.
//

#ifndef Operations_hpp
#define Operations_hpp

#include <stdio.h>
#include <cmath>
#include "shader.hpp"
#include "My_Types.hpp"

class Shader;
struct color;

class Operator{
private:
    void Reset(AMD::Mat4& mat);
    //Model Matrix
    AMD::Mat4 M_mat;
    const float* M_ptr = &M_mat.m[0][0];
    int M_loc;
    
    AMD::Mat4 rot_mat;
    const float* rot_ptr = &rot_mat.m[0][0];
    int rot_loc;
    
    AMD::Mat4 prev_rot;
    

    AMD::Mat4 Ob_mat;
    const float* Ob_ptr =&Ob_mat.m[0][0];
    int Ob_loc;
    // View Matrix
        
    AMD::Mat4 V_mat;
    const float* V_ptr = &V_mat.m[0][0];
    int V_loc;
    
    
    //Projection Matrix
    AMD::Mat4 Proj_mat;
    const float* Proj_ptr = &Proj_mat.m[0][0];
    int Proj_loc;
    
    //MISC.
    AMD::Vec3 light_src_dir;
    int src_loc;
    
    AMD::Vec4 Ob_Color;
    int color_loc;
    
    
    
    float sat =1.0;
    int sat_loc;
    
public:
    Operator(const Shader& sh);
    ~Operator();
    
    void translate(float dx, float dy, float dz, AMD::Mat4& mat);
    void translate(AMD::Vec3 trans, AMD::Mat4& mat);
    
    void rotation(float a, float b, float c, AMD::Mat4& mat);
    void rotation(AMD::Vec3 ang, AMD::Mat4& mat);
    
    void scale(float sx, float sy, float sz, float sw, AMD::Mat4& mat);
    void scale(AMD::Vec4 vec, AMD::Mat4& mat);
    
    
    void Ob_set_rotation(AMD::Vec3 ang);
    void Ob_set_translation(AMD::Vec3 trans);
    void Ob_set_scale(float sc);
    void Ob_set_scale(AMD::Vec3 sc);
    void set_Object();
    
    
    void M_set_rotation(float ax, float ay, float az);
    void M_set_rotation();
    void M_set_scale(float sx, float sy, float sz, float sw);
    void M_set_rotation(AMD::Vec3 vec);
    void M_set_scale(AMD::Vec4 vec);
    void M_set_translation(AMD::Vec3 vec);
    void object_translate(AMD::Vec3 trans);
    void set_Model();
    
    
    
    void V_set_rotation(float ax, float ay, float az);
    void V_set_rotation();
    void V_set_translation(AMD::Vec3 tr);
    void V_set_translation();
    void V_set_scale(AMD::Vec4);
    void set_View();
    
    void Projection(float near, float far, float xlim, float ylim);
    void set_projection(float near, float far, float dx, float dy);
    void set_projection(float pj[4]);
    
    void set_light(AMD::Vec3 src);
    void set_light(float src[3]);
    void set_light_dir(float theta, float phi);
    AMD::Vec3 get_Light_src();
    
    void set_ob_clr();
    void set_ob_clr(AMD::Vec4 clr);
    
    void set_sat(float);
    
    AMD::Vec4& get_ob_clr();
    
    
    AMD::Vec3 V_translation;
    AMD::Vec3 V_rotation;
    AMD::Vec3 M_origin;
    AMD::Vec3 M_rotation;
};


class Projection{
private:
    float m_near;
    float m_far;
    float m_xlim;
    float m_ylim;
    void reset();
    
public:
    Projection();
    ~Projection();
    float Proj_mat[4][4];
    const float* Proj_ptr = &Proj_mat[0][0];
    
    void set_FOV(float near, float far, float xlim, float ylim);
    
    
    
    
};



#endif /* Operations_hpp */

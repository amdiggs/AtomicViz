//
//  shader.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/28/22.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "Render.hpp"
#include "My_Types.hpp"
#include "Shapes.hpp"
#include "Operations.hpp"
class Texture;

class Shader{
private:
    const std::string V_shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Vertex.vs";
    const std::string F_shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Fragment.fs";
    
    unsigned int m_ID; unsigned int m_num_tex = 0;
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void CreateShader(const std::string& vertexShader,const std::string& geometryShader, const std::string& fragmentShader);
    std::string get_sh_str(std::string sh_file);
    std::string get_sh_str(std::string sh_type, std::string sh_file);
    
    int displace_loc, MV_loc, MVP_loc, N_loc;
    
     int src_loc, light_clr_loc, sat_loc;
    
    int tex_locs[15]; int other_locs[15];

    
public:
    Shader(std::string v_type, std::string f_type);
    Shader(std::string file_name);
    ~Shader();
    
    void bind();
    void unbind();
    int UniformLoc(const char* name) const;
    void Get_Uniforms(int texc, const char* texv[]);
    
    void Set_Uniforms(Operator& op, Light_Src src);
    void Set_Value(char type, const float* mat_ptr) const;
    void Set_Value(char type, const AMD::Vec3& vec) const;
    void Set_Value(char type, const AMD::Vec4& vec) const;
    void Set_Value(char type, const AMD::Vec2& vec) const;
    void Set_Value(char type, const float& f) const;
    void Set_Value(char type, const int& a) const;
    
    
    
    void set_texture(Texture& tx);
    
    
    
};

bool comment(std::string str, std::string reg_ex);
#endif /* shader_hpp */

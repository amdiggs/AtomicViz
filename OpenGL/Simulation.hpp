//
//  Simulation.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/21/22.
//

#ifndef Simulation_hpp
#define Simulation_hpp

#include <stdio.h>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "My_Types.hpp"
#include "vertexbuffer.hpp"
#include "vertexarray.hpp"
#include "shader.hpp"
#include "Shapes.hpp"
#include "Atomic.hpp"
#include "Texture.hpp"
#include "Operations.hpp"

// This will contain the objects that will be a complete simulation:
// It will have a simbox, atoms and bonds:
// The simbox will be 12 lines:
// The atoms will need a sphere mesh, a VAO, a VBO, an IBO and a shader


class Ensamble_Of_Atoms{
private:
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    static AMD::Vec3 BB;
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/Atom.vs";
    unsigned int num_draws;
    const unsigned int m_num_tex = 3; const char* uniform_text_names[10] = {"u_Texture", "u_Texture2", "u_map"};
    
public:
    
    Ensamble_Of_Atoms(std::string atomfile, Texture& tx);
    ~Ensamble_Of_Atoms();
    void Add_Instance_Layout();
    void Bind();
    void UnBind();
    void DrawBind();
    void Bind_Texture(Texture& tx, int layer);
    unsigned int num_idx();
    void Set_Op(Operator& op, Light_Src& l);
    std::string file_name;
    void Set_texture(Texture& tx);
    void Compute_Neighbors();
    int neb_IDs[150000][2];
    int num_bonds =0;
    Atom* m_ats;
    AMD::Vec3 Get_Box();
    Shader m_sh;
    
    
    
    
};


class Bonds{
    
private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/Bond.vs";
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    Shader m_sh;
    const unsigned int m_num_tex = 1; const char* uniform_text_names[10] = {"u_Tex"};
public:
    Bonds(Ensamble_Of_Atoms& ats, Texture& tx);
    ~Bonds();
   
        
    void Add_Instance_Layout(std::string atom_file);
    void Add_Instance_Layout(Ensamble_Of_Atoms& ats);
    void Bind();
    void UnBind();
    void DrawBind();
    unsigned int num_idx();
    void Set_Op(Operator& op, Light_Src& l);
    int num_bonds =0;
    void Bind_Texture(Texture& tx, int layer);
};


class Grid_Mesh{
private:
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    Shader m_sh;
    
public:
    Grid_Mesh(Texture& tx);
    ~Grid_Mesh();
    void DrawBind();
    unsigned int num_idx();
    void Set_Op(Operator& op, Light_Src& l);
    void Bind();
    void UnBind();
    void Bind_Texture(Texture& tx);
};



class Box_Bounds{
private:
    const char* Uni[8] = {"hello","hello","hello","hello","hello","hello","hello","hello"};
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    
public:
    Box_Bounds(Texture& tx, AMD::Vec3 BB);
    ~Box_Bounds();
    void DrawBind();
    unsigned int num_idx();
    void Set_Op(Operator& op, Light_Src& l);
    void Bind();
    void UnBind();
    void Bind_Texture(Texture& tx);
    Shader m_sh;
};


class Quad_Mesh{
private:
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    AMD::Vec3 points[4];
    
    
public:
    Quad_Mesh(Texture& tx, AMD::Vec3 bb, const char face);
    ~Quad_Mesh();
    void DrawBind();
    unsigned int num_idx();
    void Set_Op(Operator& op, Light_Src& l);
    void Bind();
    void UnBind();
    void Bind_Texture(Texture& tx);
    void Get_Face(AMD::Vec3 BB,const char choice);
    std::string m_cw;
    Shader m_sh;
};

class Test_Object{
private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/Sphere.vs";
    const unsigned int m_num_obj;
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    Shader m_sh;
    const unsigned int m_num_tex = 2; const char* uniform_text_names[10] = {"u_Tex_Test1","u_Tex_Test2"};
    
public:
    Test_Object(Texture& tx);
    ~Test_Object();
    void DrawBind();
    void Add_Instance_Layout();
    unsigned int num_idx();
    unsigned int num_obj();
    void Set_Op(Operator& op, Light_Src& l);
    void Bind();
    void UnBind();
    void Bind_Texture(Texture& tx);
    
};


#endif /* Simulation_hpp */

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
    int m_num_atoms;
    int neb_IDs[150000][2];
    int num_bonds =0;
    std::string file_name;
    friend class Bonds;
public:
    
    Ensamble_Of_Atoms(std::string atomfile);
    ~Ensamble_Of_Atoms();
    void Add_Instance_Layout();
    void Bind();
    void UnBind();
    void Draw(int num);
    void Bind_Texture(Texture& tx, int layer);

    void Set_Op(Operator& op, Light_Src& l);
    void Set_texture(Texture& tx);
    void Compute_Neighbors();
    Atom* m_ats;
    AMD::Vec3 Get_Box();
    Shader m_sh;
    unsigned int num_idx();
    
    
    
    
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

class Floor{
    private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/floor.vs";
    VertexArray m_VAO;
    IndexBuffer m_IBO;

    const char* Uniform_names = "u_VP";
    
public:
    
    Shader m_sh;
    AMD::Mat4 m_VP;
    Floor(float y);
    ~Floor();
    unsigned int num_idx();
    void Bind();
    void UnBind();
    void Draw(Operator& op);
};

class Quad_Mesh{
private:
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    AMD::Vec3 points[4];
    
    
public:
    Quad_Mesh();
    Quad_Mesh(AMD::Vec3 LL, AMD::Vec3 LR, AMD::Vec3 UR, AMD::Vec3 UL);
    ~Quad_Mesh();
    unsigned int num_idx();
    void Bind();
    void UnBind();
};

class Test_Object{
private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/test.fs";
    const char* m_sampler = "Env_Tex";
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    Shader m_sh;
    
    
    
public:
    Test_Object();
    ~Test_Object();
    void Draw();
    void Set_Shader(Operator& op, Light_Src& light);
    void Bind();
    void UnBind();
    void Bind_Texture(Texture& tx);
    
};

class Environment{
private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/environment.vs";
    const char* m_sampler = "Env_Tex";
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    
    
public:
    Shader m_sh;
    
    Environment();
    ~Environment();
    
    void Bind();
    void UnBind();
    void Set_Shader(Operator& op, Light_Src& light);
    void Draw();
    void Attach_Texture(Texture& tx);
    void Attach_Texture(Texture3D& tx);
    void Attach_Shadow_Map_Texture(const ShadowMap& sm);
};


#endif /* Simulation_hpp */

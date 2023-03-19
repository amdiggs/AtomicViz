//
//  main.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 6/30/22.
//
#include <iostream>
#include "Render.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "vertexbuffer.hpp"
#include "vertexarray.hpp"
#include "Shapes.hpp"
#include "shader.hpp"
#include "Operations.hpp"
#include "Atomic.hpp"
#include "Texture.hpp"
#include "Simulation.hpp"
#include "FrameBuffer.hpp"
extern int num_atoms;


AMD::Mat4 CT = ROTATION_MATRIX(AMD::Vec3(0.0, 0.0, 0.78539));


class Voxelize{
private:
    const std::string shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/voxel.fs";
    const char* m_sampler = "Vol_Tex";
    VertexArray m_VAO;
    IndexBuffer m_IBO;
    
    
public:
    Shader m_sh;
    
    Voxelize()
    :m_sh(shader_file)
    {
        Volume_XY vox(4.0, 4.0, 4.0, 100);
        //Voxel_Grid vox(2.0, 2.0, 2.0, 20, 20);
        VertexBuffer vb(vox.verts, vox.num_verts()*sizeof(AMD::Vertex));
        m_VAO.Add_Vertex_Buffer(vb);
        m_IBO.Gen_Buffer(vox.indices,vox.num_idx());
        
    }
    
    ~Voxelize(){}
    
    void Bind(){
        this->m_sh.bind();
        this->m_VAO.bind();
        this->m_IBO.bind();
    }
    
    
    void UnBind(){
        this->m_sh.unbind();
        this->m_VAO.unbind();
        this->m_IBO.unbind();
    }
    
    void Set_Shader(Operator& op, Light_Src& light){
        this->m_sh.bind();
        this->m_sh.Set_Uniform_MVP(op);
        this->m_sh.Set_Uinform_LightSource(light);
    }
    
    void Draw(){
        this->m_VAO.bind();
        this->m_IBO.bind();
        glDrawElements(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0);
        this->m_VAO.unbind();
        this->m_IBO.unbind();
    }
    
    void Attach_Texture(Texture3D& tx){
        m_sh.Set_Texture(m_sampler, tx);
    }
    
};

/*
void Run_Shadow(){
    
    std::string atom_file = "/Users/diggs/Desktop/OpenGL/OTHER/ring.atom";
    
    Renderer my_rend(1000, 900, "Hello World", NULL, NULL, false);
    UI_Window ui(0.0,0.0,my_rend.Get_Window());
    
    //Init Darwable stuff
    Environment env;
    Floor floor(-2.01);
    Quad_Mesh qd;
    
    //init Operator and Light Source
    Operator op;
    Light_Src l_src;
    
    //#Init and Load Textures
    Texture tx(0);
    tx.Load("dicetext.png");
    env.Attach_Texture(tx);
    AMD::Mat4 test;
    //init FBO
    ShadowMap sm(6000, 6000);
    
    int loc;
    while (!my_rend.is_open())
    {
        //General stuff
        op.Set();
        
        //UI Sstuff
        ui.NewFrame();
        ui.Simple_window(op, l_src, my_rend.m_w, my_rend.m_h);
        ui.log_window(op.Get_Model(), false);
        ui.log_window(test, true);
        
        //Framebuffer/Shadowmap pass
        sm.Set_MLP(op, l_src);
        sm.Pass();
        env.Draw();
        
        //Draw Pass
        my_rend.Draw_Pass();
        
        // I need to bind the shadow map texture
        //env.Attach_Shadow_Map_Texture(sm);
        // and other textures
        
        //Get the MLP matrix
        test = op.Get_MLP(l_src);
        env.m_sh.Set_Uniform_Mat4("u_LightMVP", &test[0][0]);
        
        // then set the uniform sampler in the object shader.
        
        env.Set_Shader(op, l_src);
        //env.m_sh.Set_U_Mat4("u_MVP", &test[0][0]);
        env.Draw();
        
        
        loc = floor.m_sh.UniformLoc("ShadowMap");
        floor.m_sh.bind();
        //sm.ReadBind(0);
        glUniform1i(loc,sm.Get_Layer());
        floor.m_sh.Set_Uniform_Mat4("u_LightMVP", &test[0][0]);
        floor.m_sh.Set_Uniform_Mat4("u_VP", op.MVP_ptr);
        //floor.m_sh.Set_U_Mat4("u_VP", &test[0][0]);
        floor.Draw(op);
}

}
*/

int main(void)
{
    
    Renderer my_rend(1000, 900, "Hello World", NULL, NULL, false);
    UI_Window ui(0.0,0.0,my_rend.Get_Window());
    
    //Init Darwable stuff
    Voxelize vox;
    //Floor floor(-2.01);
    Quad_Mesh qd;
    
    //init Operator and Light Source
    Operator op;
    Light_Src l_src;
    
    Texture3D tx(0);
    AMD::Vec3 vecs[5] = {AMD::Vec3(-1.5,-1.5,-1.5), AMD::Vec3(0.0,0.0,0.0),AMD::Vec3(1.5,1.5,1.5),AMD::Vec3(-1.5,1.5,1.5), AMD::Vec3(-1.5,-1.5,1.5)};
    AMD::Vec3 bb(4.0,4.0,4.0);
    tx.Cavity(vecs,5,bb);
    vox.Attach_Texture(tx);
    
    
    while (!my_rend.is_open())
    {
        //General stuff
        op.Set();
        
        //UI stuff
        ui.NewFrame();
        ui.Simple_window(op, l_src, my_rend.m_w, my_rend.m_h);
        ui.log_window(op.Get_Model(), false);
        
        
        //Draw Pass
        my_rend.Draw_Pass();
        
        // I need to bind the shadow map texture
        //env.Attach_Shadow_Map_Texture(sm);
        // and other textures
        
        
        vox.Set_Shader(op, l_src);
        vox.Draw();
        
        //UI render
        ui.render();
        my_rend.poll();
        
    }
    

    
    
    return 0;
}

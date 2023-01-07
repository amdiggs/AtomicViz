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

extern int num_atoms;
extern const std::string SRCS;

AMD::Mat4 CT = ROTATION_MATRIX(AMD::Vec3(0.0, 0.0, 0.78539));

void TEST(){
    std::string Basic_shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/Sphere.vs";
    Sphere sp(1.0);
    VertexArray VAO;
    VertexBuffer vb(sp.verts, sp.num_verts()*sizeof(AMD::Vertex));
    VAO.Add_Vertex_Buffer(vb);
    IndexBuffer IBO;
    IBO.Gen_Buffer(sp.indices,sp.num_idx());
    Shader sh(Basic_shader_file);
    

    
    Texture tx;
    tx.Image_Texture_RGB(0, "spring2.jpg");
    tx.Image_Texture(1, "moon.png");
    tx.Image_Texture_RGB(2, "MoonNormal.jpg");
    sh.bind();
    sh.unbind();
    
}



int main(void)
{
    
    std::string fname = SRCS+"PEsurface_norm.xyz";
    std::string atom_file = "/Users/diggs/Desktop/OpenGL/OTHER/atom_test.atom";
    std::string Basic_shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/Shaders/Basic.vs";
        


    

    
    
    
    
    Renderer my_rend(100, 900, "Hello World", NULL, NULL, false);
    UI_Window ui(0.0,0.0,my_rend.draw_window());
    

    
    
    Texture tx;
    //tx.Gen_Noise(0);
    tx.Image_Texture_RGB(0, "MoonNormal.jpg");
    tx.Image_Texture(2, "water.png");
    tx.Image_Texture(1, "moon.png");
    
    

    Test_Object tst(tx);
    
    //Ensamble_Of_Atoms ats(atom_file, tx);
    //ats.Compute_Neighbors();
    
   //Bonds bds(ats,tx);
   //Grid_Mesh gr(tx);
   //Quad_Mesh qd(tx,AMD::Vec3(3.0,1.0,1.0),'F');
   //Box_Bounds BB(tx, ats.Get_Box());
    
    
    Operator op;
    Light_Src l_src;
    

    
    float dx = 0.0;
    AMD::Vec3 m_vec(0.0, 0.0, 0.0);
    int counter = 0;
    
    while (!my_rend.is_open())
    {
        /* Render here */
        my_rend.clear(ui);
        ui.Simple_window(op, l_src, my_rend.m_w, my_rend.m_h);
        ui.log_window(op.Get_MV());
        ui.log_window(op.Get_MVP());
    
        
        tst.Set_Op(op, l_src);
        my_rend.Draw(tst);
        //ats.m_sh.bind();
        //ats.Set_Op(op, l_src);
        //my_rend.Draw_Instanced(ats, GL_TRIANGLES,num_atoms);
        //
        //bds.Set_Op(op, l_src);
        //my_rend.Draw_Instanced(bds, GL_TRIANGLES, bds.num_bonds);
        //BB.m_sh.bind();
        //BB.Set_Op(op, l_src);
        //my_rend.Draw(BB);
        
        //qd.m_sh.bind();
        //qd.Set_Op(op, l_src);
        //glUniform3f(tr_loc2, 0.5*cos(dx),0.0,0.0);
        //my_rend.Draw(qd, GL_TRIANGLES);
    
        
   
  
        if(!(counter%5)){
            dx+=0.314;
        }
        counter++;
        ui.render();
        my_rend.poll();
        
    }
    

    
    return 0;
}

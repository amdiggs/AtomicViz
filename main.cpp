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

extern int num_atoms;


 GLubyte off_set[10][3];

    
void LoadTexture(){
 int value;
 for (int i = 0; i< 10; i++){
     value = (int)(Rand::Get().rand_normal_color()*255.0);
     
     off_set[i][0] = value;
     off_set[i][1] = value;
     off_set[i][2] = value;
         
     
 }
    
    
}

int main(void)
{
    
    std::string fname = "/Users/diggs/Desktop/OpenGL/PEsurface_norm.xyz";
    std::string atom_file = "/Users/diggs/Desktop/OpenGL/atom_test.atom";
        


    
    //Cube cb;
    Sphere sp(1.0,50);
    Triangle tr;
    //Grid gr(fname);
    
    //Atom at("1 1 0.0  0.0 -1.5");
    //Atom at2("2 1 0.0 0.0 1.5");
    //Bond bd(at, at2);
    //Cone cn;
    Cylinder cy;
    Atom* my_atoms = atoms(atom_file);
    Arrow ar1('r', 'x');
    Arrow ar2('g','y');
    Arrow ar3('b', 'z');
    
    Renderer my_rend(1600, 900, "Hello World", NULL, NULL, false);
    UI_Window ui(0.0,0.0,my_rend.draw_window());
 
    VertexArray VAO;
    VertexBuffer vb(sp.verts, sp.num_verts()*sizeof(AMD::Vertex), 5);
    VAO.AddBuffer2(vb);
    
    IndexBuffer id(sp.indices, sp.num_idx());
    /*
    VertexArray VAO2;
    VertexBuffer vb2(ar2.verts, ar2.num_verts()*sizeof(AMD::Vertex), 3);
    VAO2.AddBuffer2(vb2);
    
    IndexBuffer id2(ar2.indices,ar2.num_idx());
    
    
    VertexArray VAO3;
    VertexBuffer vb3(ar3.verts, ar3.num_verts()*sizeof(AMD::Vertex), 3);
    VAO3.AddBuffer2(vb3);
    
    IndexBuffer id3(ar3.indices,ar3.num_idx());
    */
    /*
    GLfloat texDataf [9] =
        {
            2.5, 0.3, 1.0, //Red
            0.3,0.0,0.3, //Green
            0.3,0.3,0.0 //Blue
        };
    
    unsigned char texData [12] =
        {
            255, 255, 0, 255, //Red
            0, 255, 0, 255, //Green
            0, 0, 255, 255 //Blue
        };
    unsigned int texture_ID;
    unsigned int tbo;
    glGenBuffers(1,&tbo);
    glBindBuffer(GL_TEXTURE_BUFFER, tbo);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(texDataf), texDataf, GL_STATIC_DRAW);
    
    glGenTextures(1, &texture_ID);
    glBindTexture(GL_TEXTURE_BUFFER, texture_ID);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGB32F, tbo);
    


    
    glBindBuffer(GL_TEXTURE_BUFFER, 0);
    
    



    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, texture_ID);
     */
    Texture tx(my_atoms);
    Shader sh;
    sh.bind();
    Operator op(sh);
    
    tx.bind(1);
    
    int tex_loc = sh.UniformLoc("off_set");
    glUniform1i(tex_loc, 0);
    
    int tex_loc2 = sh.UniformLoc("u_Texture");
    glUniform1i(tex_loc2, 1);
    

    
    AMD::Mat4 CT = ROTATION_MATRIX(AMD::Vec3(0.0, 0.0, 0.78539));


    float dx = 16.3;
    float r = 0.0f;
    float step = 0.005;
    float c = 0.0;
    //int cnt = 0;
    op.set_Object();
    op.M_set_translation(AMD::Vec3(0.0,0.0,0.0));
    op.M_set_rotation();
    op.M_set_scale(1.0/dx,1.0/dx,1.0/dx,1.0);
    op.set_Model();

    while (!my_rend.open())
    {
        /* Render here */
       
        my_rend.clear(ui);
        ui.Simple_window(op);
        ui.log_window(cy.verts, cy.num_verts());
        //ui.log_window(ar.verts,ar.indices, ar.num_idx());
        
        
        
        //op.Ob_set_rotation(AMD::Vec3());
        op.set_Object();
        op.set_Model();
        my_rend.Draw(id, VAO, sh, GL_TRIANGLES, num_atoms);
        //my_rend.Draw(id2, VAO2, sh, GL_TRIANGLES);
        //my_rend.Draw(id3, VAO3, sh, GL_TRIANGLES);
        
        /*
        op.Ob_set_translation(at2.get_coords());
        op.set_Object();
        op.set_Model();
        my_rend.Draw(id2, VAO2, sh, GL_TRIANGLES);
        
        op.Ob_set_scale(AMD::Vec3(0.25, bd.m_len, 0.25));
        op.Ob_set_rotation(bd.angle);
        op.Ob_set_translation(bd.m_start + (bd.m_vec/2.0));
        op.set_Object();
        op.set_Model();
        my_rend.Draw(id, VAO, sh, GL_TRIANGLES);
        */


        //op.set_light_dir(c, 0.0);
        //my_rend.Draw(id, VAO, sh,GL_TRIANGLES);
        //my_rend.Draw(id3, VAO2, sh, GL_TRIANGLES);
        //my_rend.Draw(id2, VAO2, sh, GL_LINES);
        /*
        for (int i = 0; i<num_atoms; i++){
            
            op.object_translate(my_atoms[i].get_coords());
            op.set_Model();
            my_rend.Draw(id2, VAO2, sh, GL_TRIANGLES);
        }

         */
        if (r<1.0) {
            r+=step;
        }
        
        else{r=0.0f;}
        
        
        c+=step;
        ui.render();
        my_rend.Draw_Ui();
        my_rend.poll();
        //Write_Buffer("testff.ppm", my_rend);
    }
    

    //glDeleteTextures(1, &my_tex_ID);
    return 0;
}

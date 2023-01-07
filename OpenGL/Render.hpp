//
//  Render.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/14/22.
//

#ifndef Render_hpp
#define Render_hpp

#include <stdio.h>
#include <iostream>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "My_Types.hpp"




class VertexArray;
class Shader;
class Operator;
class Light_Src;
class IndexBuffer;
class UI_Window;
class Atom;
class Bond;
class Ensamble_Of_Atoms;
class Bonds;
class Grid_Mesh;
class Quad_Mesh;
class Box_Bounds;
class Test_Object;

class Renderer{
private:
    GLFWwindow* m_primary_window;
    GLFWwindow* m_second_window;
    void check(GLFWwindow* window);
    AMD::Vec4 m_cc;
    int m_res_loc;
    
    
    
public:
    Renderer(int w, int l, const char* name, GLFWmonitor* monitor, GLFWwindow* share, bool Multi_Window);
    ~Renderer();
    GLFWwindow* draw_window();
    GLFWwindow* ui_window();
    void set_context();
    void set_color(float clr[4]);
    void set_color(AMD::Vec4 clr);
    void Draw_Instanced(IndexBuffer& ib, VertexArray& va, Shader& sh, GLenum draw_type, int num);
    void Draw_Instanced(Ensamble_Of_Atoms& ats, GLenum draw_type, int num);
    void Draw_Instanced(Bonds& bds, GLenum draw_type, int num);
    void Draw(IndexBuffer& ib, VertexArray& va, Shader& sh, GLenum draw_type);
    void Draw(Grid_Mesh& gr, GLenum draw_type);
    void Draw(Quad_Mesh& qd, GLenum draw_type);
    void Draw(Box_Bounds& BB);
    void Draw(Test_Object& tst);
    void Simple_window(Operator& op);
    int is_open();
    void poll();
    void clear(UI_Window& ui);
    void Write_Buffer(std::string file_name);
    int Write_Curr_Buffer(std::string file_name);
    void Get_res_loc(const Shader& sh);
    int m_w, m_h;
    
    
    
};

ImGuiIO& init_io();

class UI_Window{
private:
    GLFWwindow* m_window;
    ImGuiIO& m_io;
    AMD::Vec4 m_cc;
    AMD::Vec4 Ob_clr;
 
    float view_x, view_y, view_z;
    float m_x, m_y;
    int display_w, display_h;
    float  ui_x, ui_y;
    const char* m_version = "#version 150";
 
    float projection[4] = {1.0, -3.0, 3.0, 3.0};
    
public:
    UI_Window(float pos_x, float pos_y,GLFWwindow* window);
    ~UI_Window();
    
    
    void Simple_window(Operator& op, Light_Src& l, int w, int h);
    void render() const;
    void NewFrame() const;
    
    AMD::Vec4& get_color();
    
    
    void mouse_drag(AMD::Vec3& vec);
    
    void log_window(Ensamble_Of_Atoms& ats);
    void log_window( Bond* bd, int num);
    void log_window( AMD::Vertex* verts, int num);
    void log_window( AMD::Vertex* verts, unsigned int* idx, int num);
    void log_window( AMD::Mat4 mat);
    void log_window(int neb[][2], int num);
    void Write_Buffer(std::string file_name);
    
    
};

static void glfw_error_callback(int error, const char* description);

#endif /* Render_hpp */

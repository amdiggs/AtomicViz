//
//  my_UI.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 9/16/22.
//

#ifndef my_UI_hpp
#define my_UI_hpp

#include <stdio.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class UI_Window{
private:
    float view_x, view_y;
    
    float m_x, m_y;
    int display_w, display_h;
    const char* m_version = "#version 150";
    bool show_window;
    ImGuiIO& m_io;
    GLFWwindow* m_window;
    
public:
    UI_Window(float pos_x, float pos_y,GLFWwindow* window, ImGuiIO& io);
    ~UI_Window();
    
    void simple_wiondow();
    void render();
    void clear();
    void draw();
    
    
};




#endif /* my_UI_hpp */

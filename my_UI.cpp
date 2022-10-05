//
//  my_UI.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 9/16/22.
//

#include "my_UI.hpp"



UI_Window::UI_Window(float pos_x, float pos_y, GLFWwindow* window, ImGuiIO& io)
: m_x(pos_x), m_y(pos_y), m_window(window), m_io(io)
{
    (void)m_io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(m_version);
    
    
    ImFont* font = m_io.Fonts -> AddFontFromFileTTF("/System/Library/Fonts/Helvetica.ttc", 16.0);
    IM_ASSERT(font != NULL);
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    view_x = 0.95;
    view_y = 0.85;
    
}

UI_Window::~UI_Window() { 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



void UI_Window::simple_wiondow(){
    
    ImGui::SetNextWindowPos(ImVec2(m_io.DisplaySize.x*0.0, m_io.DisplaySize.y*0.0));
    ImGui::SetNextWindowSize(ImVec2(m_io.DisplaySize.x*view_x,m_io.DisplaySize.y*view_y));
    //ImGui::SetNextWindowPos(ImVec2(0.5, 0.5), ImGuiCond_Always, ImVec2(0.5,0.5));

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &m_x, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        display_w+=10;
    ImGui::SameLine();
    ImGui::Text("counter = %d", display_w);
    
    ImGui::InputFloat("Pos X", &m_x, 0.01f, 1.0f, "%.3f");
    ImGui::InputFloat("Pos Y", &m_y, 0.01f, 1.0f, "%.3f");
    ImGui::InputFloat("Width", &view_x, 0.01f, 1.0f, "%.3f");
    ImGui::InputFloat("Height", &view_y, 0.01f, 1.0f, "%.3f");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}




void UI_Window::render(){
    ImGui::Render();
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glfwMakeContextCurrent(m_window);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



void UI_Window::clear(){
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}




void UI_Window::draw(){
    clear();
    simple_wiondow();
}





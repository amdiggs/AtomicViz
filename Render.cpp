//
//  Render.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/14/22.
//

#include "Render.hpp"
#include "vertexbuffer.hpp"
#include "vertexarray.hpp"
#include "shader.hpp"
#include "Atomic.hpp"
#define PI 3.14159


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

ImGuiIO& init_io(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    return io;
}

Renderer::Renderer(int w, int l, const char* name, GLFWmonitor* monitor, GLFWwindow* share, bool Multi_Window)
:ui_x(0.2), ui_y(0.9), view_x(0.0), view_y(0.0), view_z(-2.0)
{   glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHintString(GLFW_COCOA_FRAME_NAME, "testframe");
    this -> m_primary_window = glfwCreateWindow(w, l, name, monitor, NULL);
    check(m_primary_window);
    if(Multi_Window){
        this-> m_second_window = glfwCreateWindow(200, 900, "UI_window", monitor, m_primary_window);
        check(m_second_window);
    }
    else{this-> m_second_window = NULL;}
    set_context();

    
}


Renderer::~Renderer(){
    glfwTerminate();
}



void Renderer::check(GLFWwindow* window){
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
}


void Renderer::set_context(){
    glfwMakeContextCurrent(m_primary_window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();
}

void Renderer::set_color(float clr[4]) {
    m_cc[0] = clr[0]; m_cc[1] = clr[1];
    m_cc[2] = clr[2]; m_cc[3] = clr[3];
}

void Renderer::set_color(AMD::Vec4 clr){
    m_cc[0] = clr[0]; m_cc[1] = clr[1];
    m_cc[2] = clr[2]; m_cc[3] = clr[3];
}

void Renderer::clear(UI_Window& ui){
    set_color(ui.get_color());
    glClearColor(m_cc[0], m_cc[1], m_cc[2], 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ui.NewFrame();
}

void Renderer::Draw(IndexBuffer& ib, VertexArray& va, Shader& sh, GLenum draw_type, int num){
    int width, height;
    glfwGetFramebufferSize(m_primary_window, &width, &height);
    glViewport(0, 0, width, height);
    sh.bind();
    va.bind();
    ib.bind();
    //glDrawElements(draw_type,ib.get_num(), GL_UNSIGNED_INT, 0);
    glDrawElementsInstanced(draw_type,ib.get_num(), GL_UNSIGNED_INT,0, num);
    
}

void Renderer::Draw_Ui(){
}

int Renderer::open(){
    return glfwWindowShouldClose(m_primary_window);
}

void Renderer::poll(){
    glfwSwapBuffers(m_primary_window);
    if (m_second_window) {
        glfwSwapBuffers(m_second_window);
    }
    
    glfwPollEvents();
}






void Renderer::Write_Buffer(std::string file_name){
    int count = 0;
    int width, height;
    glfwGetFramebufferSize(m_primary_window, &width, &height);
    const int num_pix = 3 * width * height;
    unsigned char pixels[num_pix];
    
    std::fstream outfile;
    outfile.open(file_name, std::ios::out);
    
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    if(outfile.is_open()){
        outfile << "P3\n" << width << " " << height << "\n255" << std::endl;
        for (int i = 0; i < width*height; i++){
            outfile << int(pixels[count]) << " "
            << int(pixels[count + 1]) << " "
            << int(pixels[count + 2]) << " " << std::endl;
            count+=3;
        }
    }
    
    outfile.close();
    exit(0);
    return;
    
}



GLFWwindow* Renderer::draw_window(){
    return m_primary_window;
}

GLFWwindow* Renderer::ui_window(){
    return m_second_window;
}









//THIS IS MY UI CLASS!!!!!!!!!!!

UI_Window::UI_Window(float pos_x, float pos_y, GLFWwindow* window)
: m_x(pos_x), m_y(pos_y), m_window(window), m_io(init_io())
{
    (void)m_io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(m_version);
    
    
    ImFont* font = m_io.Fonts -> AddFontFromFileTTF("/System/Library/Fonts/Helvetica.ttc", 16.0);
    IM_ASSERT(font != NULL);
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    view_x = 0.0;
    view_y = 0.0;
    
}

UI_Window::~UI_Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


 void UI_Window::Simple_window(Operator& op){
     static float rot[3] = {0.0, 0.0,0.0};
     static float theta = 0.0;
     static float phi = 0.0;
     static float sat = 1.0;
     static float dance = 0.0;
     static bool check;
     static float v_scale = 1.0;
     
     ImGui::SetNextWindowPos(ImVec2(0.0, 0.0));
     ImGui::SetNextWindowSize(ImVec2(m_io.DisplaySize.x*ui_x,m_io.DisplaySize.y*ui_y));
     

     ImGui::Begin("UI prarmeters");                          // Create a window called "Hello, world!" and append
     ImGui::SliderFloat("float", &v_scale, 0.0f, 3.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


     //Projection operations
     ImGui::InputFloat("Near", &projection[0], 0.1f, 1.0f, "%.1f");
     ImGui::InputFloat("Far", &projection[1], 0.1f, 1.0f, "%.1f");
     ImGui::InputFloat("X Lim", &projection[2], 0.1f, 1.0f, "%.1f");
     ImGui::InputFloat("Y Lim", &projection[3], 0.1f, 1.0f, "%.1f");
     op.set_projection(projection);
     //
     ImGui::InputFloat("View X", &op.V_translation[0], 0.05f, 1.0f, "%.2f");
     ImGui::InputFloat("View Y", &op.V_translation[1], 0.05f, 1.0f, "%.2f");
     ImGui::InputFloat("View Z", &op.V_translation[2], 0.05f, 1.0f, "%.2f");
     op.V_set_translation();
     if(!m_io.WantCaptureMouse){
         if(ImGui::IsMouseDragging(0)){
             //op.V_rotation[1] -=0.01*m_io.MouseDelta.x; op.V_rotation[2] -= 0.01*m_io.MouseDelta.y;
             op.M_rotation[1] = -0.01*m_io.MouseDelta.x; op.M_rotation[2] = -0.01*m_io.MouseDelta.y;
             op.M_set_rotation();
             
         }
     }
     op.V_set_rotation();
     op.V_set_scale(AMD::Vec4((9.0/16.0)*v_scale,v_scale,v_scale,1.0));
     op.set_View();
     
     
     
     ImGui::Text("Clear Color:");
     float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.40f;
     ImGui::SetNextItemWidth(w);
     ImGui::ColorPicker3("##MyColor##2", (float*)&Ob_clr, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
     ImGui::SameLine();
     ImGui::SetNextItemWidth(w);
     //ImGui::ColorPicker3("##MyColor##3", (float*)(&m_cc), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
     ImGui::ColorPicker3("##MyColor##3", (float*)(&m_cc));
     Ob_clr.r = dance;
     op.set_ob_clr(Ob_clr);
     if(check){
     if (dance <1.0) {
         dance += 0.05;
     }
     else{
         dance = 0.0;
     }
     }
     ImGui::Checkbox("Dance?", &check);
     static int div1 = 0;
     static int div2 = 0;
     ImGui::VSliderInt("theta", ImVec2(30, 160), &div1, 0, 12);
     ImGui::SameLine();
     ImGui::VSliderInt("phi", ImVec2(30, 160), &div2, 0, 12);
     theta = PI*(div1/4.0);
     phi = PI*(div2/4.0);
     
     op.set_light_dir(theta, phi);
     AMD::Vec3 light = op.get_Light_src();
     ImGui::Text("x = %f, y = %f, z = %f", light[0],light[1],light[2]);
     
     ImGui::InputFloat("Color Saturation", &sat, 0.01f, 1.0f, "%.3f");
     op.set_sat(sat);
     
     ImGui::DragFloat3("angle", rot, 0.1f, -100.0f, 100.0f);
     ImGui::SliderFloat3("slider float3", rot, -12.0f, 12.0f);
     
     
     
     static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
     ImGui::PushID("set1");
     for (int i = 0; i < 7; i++)
     {
         if (i > 0) ImGui::SameLine();
         ImGui::PushID(i);
         ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
         ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
         ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
         ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
         ImGui::VSliderFloat("##v", ImVec2(30, 160), &values[i], 0.0f, 1.0f, "");
         if (ImGui::IsItemActive() || ImGui::IsItemHovered())
             ImGui::SetTooltip("%.3f", values[i]);
         ImGui::PopStyleColor(4);
         ImGui::PopID();
     }
     ImGui::PopID();
     
     
     if(!m_io.WantCaptureMouse){
         if(ImGui::IsMouseDragging(1)){
         view_x += 0.005*m_io.MouseDelta.x; view_y-=0.005*m_io.MouseDelta.y;
         }
     }
     
     //op.M_set_rotation(rot[0], rot[1], rot[2]);
     //op.M_set_rotation(0.0,0.0, c);
     //op.M_set_translation(AMD::Vec3(0.0, 0.0,0.0));
     //op.M_set_scale(1.0/dx, 1.0/dy, 1.0/dz, 1.0);
     //op.set_Model();
     
     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
     ImGui::End();
 }



void UI_Window::log_window(Atom* atoms, int num){
 
    ImGui::Begin("LOG STUFF");
    ImGui::Text("Number of Atoms = %d", num);
    for (int i = 0; i<num; i++){
        AMD::Vec3 coords = atoms[i].get_coords();
        ImGui::Text("Atoms[%d]: x= %.2f, y= %.2f, z=%.2f", i,coords.x, coords.y, coords.z );
        
    }
    ImGui::End();
}


void UI_Window::log_window(Bond bd){
 
    ImGui::Begin("LOG STUFF");
    ImGui::Text("Bond Vec: x= %.2f, y= %.2f, z=%.2f", bd.m_vec.x, bd.m_vec.y, bd.m_vec.z );
    ImGui::Text("Bond Angles Vec: x= %.2f, y= %.2f, z=%.2f", bd.angle.x, bd.angle.y, bd.angle.z );
    ImGui::End();
}

void UI_Window::log_window( AMD::Vertex* verts, int num){
    
    if (ImGui::BeginTable("table1", 4, ImGuiTableFlags_Hideable))
    {
        //ImGui::BeginTable("table1", 3, ImGuiTableFlags_Hideable);
        // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each column.
        // (Later we will show how TableSetupColumn() has other uses, optional flags, sizing weight etc.)
        ImGui::TableSetupColumn("Coords");
        ImGui::TableSetupColumn("Color");
        ImGui::TableSetupColumn("Normal");
        ImGui::TableSetupColumn("Text Coords");
        ImGui::TableHeadersRow();
        for (int row = 0; row < num; row++)
        {
            ImGui::TableNextRow();
            

            ImGui::TableNextColumn();
            ImGui::Text("%.2f,%.2f, %.2f",verts[row].pos.x,verts[row].pos.y,verts[row].pos.z);
            
            ImGui::TableNextColumn();
            ImGui::Text("%.2f,%.2f, %.2f",verts[row].clr.r,verts[row].clr.g,verts[row].clr.b);
            
            ImGui::TableNextColumn();
            ImGui::Text("%.2f,%.2f, %.2f",verts[row].norm.x,verts[row].norm.y,verts[row].norm.z);
            
            ImGui::TableNextColumn();
            ImGui::Text("%.2f %.2f", verts[row].texture.x,verts[row].texture.y );
        }
        ImGui::EndTable();
    }
}



void UI_Window::log_window( AMD::Vertex* verts, unsigned int* idx ,int num){
    int a, b, c;
    if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_Hideable))
    {
        //ImGui::BeginTable("table1", 3, ImGuiTableFlags_Hideable);
        // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each column.
        // (Later we will show how TableSetupColumn() has other uses, optional flags, sizing weight etc.)
        ImGui::TableSetupColumn("V1");
        ImGui::TableSetupColumn("V2");
        ImGui::TableSetupColumn("V3");
        ImGui::TableHeadersRow();
        for (int row = 0; row < num; row+=3)
        {
            ImGui::TableNextRow();
            a = idx[row]; b = idx[row + 1]; c = idx[row + 2];

            ImGui::TableNextColumn();
            ImGui::Text("%d: %.2f,%.2f, %.2f",a, verts[a].pos.x,verts[a].pos.y,verts[a].pos.z);
            
            ImGui::TableNextColumn();
            ImGui::Text("%d: %.2f,%.2f, %.2f",b, verts[b].pos.x,verts[b].pos.y,verts[b].pos.z);
            
            ImGui::TableNextColumn();
            ImGui::Text("%d: %.2f,%.2f, %.2f",c, verts[c].pos.x,verts[c].pos.y,verts[c].pos.z);

        }
        ImGui::EndTable();
    }
}


void UI_Window::log_window( AMD::Mat4 mat){
    if (ImGui::BeginTable("table1", 4, ImGuiTableFlags_Hideable))
    {
        ImGui::TableSetupColumn("1");
        ImGui::TableSetupColumn("2");
        ImGui::TableSetupColumn("3");
        ImGui::TableSetupColumn("4");
        ImGui::TableHeadersRow();
        for (int row = 0; row < 4; row++)
        {
            ImGui::TableNextRow();

            ImGui::TableNextRow();
            for (int column = 0; column < 4; column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%f", mat[row][column]);
            }

        }
        ImGui::EndTable();
    }
}




 void UI_Window::NewFrame() const{
     ImGui_ImplOpenGL3_NewFrame();
     ImGui_ImplGlfw_NewFrame();
     ImGui::NewFrame();
 }

 void UI_Window::render() const{
     ImGui::Render();
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 }

AMD::Vec4& UI_Window::get_color() {
    return m_cc;
}


void UI_Window::mouse_drag(AMD::Vec3& vec){
    return;
}
















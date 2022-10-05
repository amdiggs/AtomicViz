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
#include "Shapes.hpp"
#include "Operations.hpp"

class Shader{
private:
    const std::string m_shader_file = "/Users/diggs/Desktop/OpenGL/OpenGL/shaders.shader";
    unsigned int m_ID;
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    std::string get_sh_str(std::string sh_file);

    
public:
    Shader();
    ~Shader();
    
    void bind();
    void unbind();
    int UniformLoc(const char* name) const;
    
    
    
    
};

bool comment(std::string str, std::string reg_ex);
#endif /* shader_hpp */

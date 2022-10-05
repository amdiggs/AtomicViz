//
//  shader.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/28/22.
//

#include "shader.hpp"



Shader::Shader()
{
    std::string vertexShader = get_sh_str("vertex");
    std::string fragmentShader = get_sh_str("fragment");
    CreateShader(vertexShader, fragmentShader);

}

Shader::~Shader(){
    
}



void Shader::bind(){
    glUseProgram(m_ID);
}

void Shader::unbind(){
    glUseProgram(0);
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
    }
    
    return id;
    
    
}
void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    m_ID = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(m_ID, vs);
    glAttachShader(m_ID, fs);
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return;
    
    
}




int Shader::UniformLoc(const char* name) const{
    return glGetUniformLocation(m_ID, name);
}



bool comment(std::string str, std::string reg_ex){
    std::regex reg(reg_ex);
    std::smatch m;
    std::regex_search(str, m, reg);
    return !m.empty();
};


std::string Shader::get_sh_str(std::string sh_type){
    std::ifstream in_file;
    std::string shader_string;
    in_file.open(m_shader_file);
    if (!in_file.is_open()){
        std::cout << "ERROR!!" << std::endl;
    }
    std::string line;
    while (getline(in_file, line)) {
        if (comment(line, "#shader " + sh_type)){
            while (getline(in_file, line)){
                if (!line.empty()){
                    if (comment(line, "#shader")) {
                        break;
                    }
                    else{shader_string.append(line + "\n");}
                }
            }
        }
    }
    return shader_string;
}









//
//  vertexbufferlayout.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/27/22.
//

#ifndef vertexbufferlayout_hpp
#define vertexbufferlayout_hpp

#include <stdio.h>
#include <vector>
#include "Render.hpp"
struct Element{
    unsigned int count;
    unsigned int type;
    bool norm;
    
};


class VertexBufferLayout{
    std::vector<Element> m_elements;
    unsigned int m_stride;
    
public:
    VertexBufferLayout()
    : m_stride(0){}
    
    template<typename t>
    void Push(unsigned int count){
        
        //static_assert(false);
    }
    
    
    template<>
    void Push<float>(unsigned int count){
        m_elements.push_back({GL_FLOAT, count, false});
        m_stride += sizeof(GLfloat);
    }
    
    template<>
    void Push<unsigned int>(unsigned int count){
        m_elements.push_back({GL_UNSIGNED_INT, count, false});
        m_stride += sizeof(GLuint);

    }
    
    
    inline const std::vector<Element> GetElements() const& {return m_elements;}
    inline unsigned int GetStride() const { return m_stride;}
};
#endif /* vertexbufferlayout_hpp */

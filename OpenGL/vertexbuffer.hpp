//
//  vertexbuffer.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/14/22.
//

#ifndef vertexbuffer_hpp
#define vertexbuffer_hpp

#include <stdio.h>

class VertexBuffer{
private:
    unsigned int render_ID;
    int m_comp;
    
public:
    VertexBuffer(const void* data, unsigned int size, int comp);
    ~VertexBuffer();
    
    
    void bind();
    void unbind();
    unsigned int get_ID();
    int num_comp();
    
};


class IndexBuffer{
private:
    unsigned int render_ID;
    unsigned int m_count;
    
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    
    void bind();
    void unbind();
    unsigned int get_num();
    
};

#endif /* vertexbuffer_hpp */

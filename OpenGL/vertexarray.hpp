//
//  vertexarray.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/27/22.
//

#ifndef vertexarray_hpp
#define vertexarray_hpp

#include <stdio.h>
#include "My_Types.hpp"
#include "vertexbuffer.hpp"
#include "vertexbufferlayout.hpp"
class VertexArray{
private:
    unsigned int m_ID;
    unsigned int count = 0;
public:
    VertexArray();
    ~VertexArray();
    
    void bind();
    void unbind();
    void AddBuffer(const void* off_set, unsigned int size, int num);
    void AddBuffer(const void* off_set, int num);
    void Add_Vertex_Buffer(VertexBuffer& vb);
    
};
#endif /* vertexarray_hpp */

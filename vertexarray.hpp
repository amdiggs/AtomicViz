//
//  vertexarray.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/27/22.
//

#ifndef vertexarray_hpp
#define vertexarray_hpp

#include <stdio.h>
#include "Shapes.hpp"
#include "vertexbuffer.hpp"
#include "vertexbufferlayout.hpp"
class VertexArray{
private:
    unsigned int m_ID;
    unsigned int count;
public:
    VertexArray();
    ~VertexArray();
    
    void bind();
    void unbind();
    void AddBuffer(VertexBuffer& vb);
    void AddBuffer2(VertexBuffer& vb);
    
};
#endif /* vertexarray_hpp */

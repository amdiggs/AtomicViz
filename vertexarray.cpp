//
//  vertexarray.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/27/22.
//

#include "vertexarray.hpp"


VertexArray::VertexArray()
:count(0){
    
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray(){
    
    glDeleteVertexArrays(1, &m_ID);
}


void VertexArray::AddBuffer(VertexBuffer& vb){
    bind();
    vb.bind();
    glEnableVertexAttribArray(count);
    glVertexAttribPointer(count, vb.num_comp(), GL_FLOAT, GL_FALSE, 0, (void*)0);
    count++;
    
}



void VertexArray::AddBuffer2(VertexBuffer& vb){
    bind();
    vb.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AMD::Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(AMD::Vertex), (void*)offsetof(AMD::Vertex, clr));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(AMD::Vertex), (void*)offsetof(AMD::Vertex, norm));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(AMD::Vertex), (void*)offsetof(AMD::Vertex,texture));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(AMD::Vertex), (void*)offsetof(AMD::Vertex,index));
    glBindVertexArray(0);
    
}

void VertexArray::bind(){
    
    glBindVertexArray(m_ID);
    
}

void VertexArray::unbind(){
    glBindVertexArray(0);
}

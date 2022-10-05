//
//  Atomic.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/31/22.
//

#ifndef Atomic_hpp
#define Atomic_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "My_Types.hpp"

class Atom{
private:
    AMD::Vec3 m_coords;
    Atom** m_neighbors;
    int m_num_neighbors;
    int m_type;
    int m_num;
    float m_rad;
    float dx = 16.0;
    float dy = 16.0;
    float dz = 29.0;
    
public:
    Atom();
    Atom(std::string line);
    ~Atom();
    
    AMD::Vec3 get_coords();
    
    
    
};



class Bond{
private:

public:
    
    AMD::Vec3 m_start;
    AMD::Vec3 m_end;
    AMD::Vec3 m_vec;
    float m_len;
    AMD::Vec3 angle;
    Bond();
    Bond(Atom A, Atom B);
    ~Bond();
    
    
    
    void set_len();
    void set_angles();
    
    
};


Atom* atoms(std::string file);

#endif /* Atomic_hpp */

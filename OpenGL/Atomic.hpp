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
    int m_num_neighbors;
    int m_type;
    
    float m_rad;
    
public:
    Atom();
    Atom(std::string line);
    Atom(std::string line, AMD::Vec3 BB);
    ~Atom();
    
    AMD::Vec3 get_coords() const;
    int get_type() const;
    void Find_Neighbors(Atom* ats);
    int m_num;
    float dx;
    float dy;
    float dz;
    
    
};



class Bond{
private:

    AMD::Vec3 m_start;
    AMD::Vec3 m_end;
    AMD::Vec3 m_vec;
    AMD::Vec3 m_ang;
    float m_len;
    
    
public:
    Bond();
    Bond(const Atom& A,const Atom& B);
    ~Bond();
    void Set_Theta();
    void Set_Phi();
    void Set_Len();
    
    AMD::Vec3 get_off_set();
    AMD::Vec3& get_angles();
    AMD::Vec2& get_types();
    AMD::Vec2 m_types;
    float get_len();
    
};


Atom* atoms(std::string file);

#endif /* Atomic_hpp */

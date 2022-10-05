//
//  Atomic.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/31/22.
//

#include "Atomic.hpp"
#include "FileIO.hpp"
int num_atoms;

Atom::Atom()
: m_coords(AMD::Vec3()), m_neighbors(nullptr), m_type(0), m_rad(0.0), m_num_neighbors(0)
{}

Atom::Atom(std::string line)
:m_num_neighbors(0)
{
    // LAMMPS dump looks like At.num At.type x y z
    std::stringstream ss;
    float x, y, z;
    ss << line;
    ss >> m_num >> m_type >> x >> y >> z;
    m_coords = AMD::Vec3(x*dx - 0.5*dx ,y*dy - 0.5*dy,z*dz - 0.5*dz);
    
}

Atom::~Atom() { 
    //free(m_neighbors);
}


AMD::Vec3 Atom::get_coords(){
    return m_coords;
}


Bond::Bond()
:m_len(0.0)
{
    m_vec = m_end - m_start;
}

Bond::Bond(Atom A, Atom B)
{
    m_start = A.get_coords();
    m_end = B.get_coords();
    m_vec = m_end - m_start;
    set_len();
    set_angles();
}


Bond::~Bond() {}


void Bond::set_len(){
    
    m_len = m_vec.len();
    
}


void Bond::set_angles(){
    float Pi_2 = 1.5707963;
    angle.x = Pi_2 - AMD::Get_angle(m_vec, AMD::Vec3(1.0, 0.0, 0.0));
    angle.y = Pi_2 - AMD::Get_angle(m_vec, AMD::Vec3(0.0, 1.0, 0.0));
    angle.z = Pi_2 - AMD::Get_angle(m_vec, AMD::Vec3(0.0, 0.0, 1.0));
    
    return;
    
}


Atom* atoms(std::string file){
    std::ifstream infile (file);
    std::string line;
    std::string item_type;
    std::string item;
    std::stringstream ss, ss2;
    std::string temp;
    std::string temp2;
    num_atoms = 0;
    Atom* local_atoms = nullptr;
    if (infile.is_open()) {
        while (getline(infile,line)) {
            if (ITEM(line, "ITEM:")){
                ss << line;
                ss >> item >> item_type;
                if (ITEM(item_type, "NUMBER")){
                    getline(infile, line);
                    num_atoms = atoi(line.c_str());
                    local_atoms = (Atom*)malloc(num_atoms*sizeof(Atom));
                    continue;
                }
                else if (ITEM(item_type, "ATOMS")){
                    for (int i = 0; i<num_atoms; i++){
                        getline(infile,line);
                        local_atoms[i] = Atom(line);
                        
                    }
                }
                
                ss.str(std::string());
                ss.clear();
            }
        }
    }
    
    return local_atoms;
}
















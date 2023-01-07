//
//  Atomic.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/31/22.
//

#include "Atomic.hpp"
#include "FileIO.hpp"
#include "Shapes.hpp"
int num_atoms;
Atom::Atom()
: m_coords(AMD::Vec3()), m_type(0), m_rad(0.0), m_num_neighbors(0)
{}

Atom::Atom(std::string line)
:m_num_neighbors(0), dx(1.0), dy(1.0), dz(1.0)
{
    // LAMMPS dump looks like At.num At.type x y z
    std::stringstream ss;
    float x, y, z;
    ss << line;
    ss >> m_num >> m_type >> x >> y >> z;
    m_coords = AMD::Vec3(x*dx - 0.5*dx,y*dy -0.5*dy ,z*dz - 0.5*dz);
    
}


Atom::Atom(std::string line, AMD::Vec3 BB)
:m_num_neighbors(0), dx(BB.x), dy(BB.y), dz(BB.z)
{
    // LAMMPS dump looks like At.num At.type x y z
    std::stringstream ss;
    float x, y, z;
    ss << line;
    ss >> m_num >> m_type >> x >> y >> z;
    float testx = x*dx - 0.5*dx; float testy = y*dy -0.5*dy; float testz = z*dz - 0.5*dz;
    m_coords = AMD::Vec3(x*dx - 0.5*dx,y*dy -0.5*dy ,z*dz - 0.5*dz);
    
}


Atom::~Atom() { 
    //free(m_neighbors);
}


AMD::Vec3 Atom::get_coords() const{
    return m_coords;
}
int Atom::get_type()const{
    return m_type;
}



//Bond class#####################

Bond::Bond(){}

Bond::Bond(const Atom& A,const Atom& B)
{
    m_start = A.get_coords();
    m_end = B.get_coords();
    m_vec = m_end - m_start;
    m_types.x = A.get_type();
    m_types.y = B.get_type();
    Set_Len();
    Set_Theta();
    Set_Phi();
    
    
}


Bond::~Bond() {}




void Bond::Set_Theta(){
    AMD::Vec3 z_hat = AMD::Vec3(0.0, 0.0, 1.0);
    m_ang.z = AMD::Get_angle(m_vec, z_hat);
    
}

void Bond::Set_Phi(){
    AMD::Vec3 y_hat = AMD::Vec3(0.0, -1.0, 0.0);
    AMD::Vec3 xy = AMD::Vec3(this->m_vec.x, this->m_vec.y, 0.0);
    float phi = AMD::Get_angle(xy, y_hat);
    if(this->m_vec.x < 0){
        m_ang.x = 6.283185307 - phi;
    }
    else{m_ang.x = phi;}
    m_ang.y = 0.0;
    return;
}

AMD::Vec3 Bond::get_off_set() {
    AMD::Vec3 temp = m_vec*0.5;
    return m_start + temp;
}

AMD::Vec3 &Bond::get_angles() {
    return this->m_ang;
}

AMD::Vec2 &Bond::get_types() {
    return this->m_types;
}

float Bond::get_len() { 
    return m_len;
}

void Bond::Set_Len() { 
    if((int)m_types.x == 2 && (int)m_types.y == 2){
        m_len = m_vec.len() - 1.5;
    }
    else{m_len = m_vec.len() - 0.8;}
    
    
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
    AMD::Vec3 BB(1.0,1.0,1.0);
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
                    ss.str(std::string());
                    ss.clear();
                    continue;
                }
                else if (ITEM(item_type, "BOX")){
                    float low, high;
                    std::stringstream bbss;
                    for (int i = 0; i<3; i++){
                        getline(infile, line);
                        bbss << line;
                        bbss >> low >> high;
                        BB[i] = high;
                        bbss.str(std::string());
                        bbss.clear();
                        
                    }
                    ss.str(std::string());
                    ss.clear();
                    continue;
                }
                else if (ITEM(item_type, "ATOMS")){
                    for (int i = 0; i<num_atoms; i++){
                        getline(infile,line);
                        local_atoms[i] = Atom(line, BB);
                        
                    }
                    ss.str(std::string());
                    ss.clear();
                }
                
                ss.str(std::string());
                ss.clear();
            }
        }
    }
    
    return local_atoms;
}
















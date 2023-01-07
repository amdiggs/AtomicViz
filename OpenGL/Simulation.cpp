//
//  Simulation.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/21/22.
//

#include "Simulation.hpp"

extern int num_atoms;

Ensamble_Of_Atoms::Ensamble_Of_Atoms(std::string atomfile, Texture& tx)
:m_ats(atoms(atomfile)), m_sh(shader_file), file_name(atomfile)
{ 
    Sphere sp(1.0);
    VertexBuffer vb(sp.verts, sp.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(sp.indices,sp.num_idx());
    Add_Instance_Layout();
    m_sh.Get_Uniforms(m_num_tex, uniform_text_names);
    Bind();
    m_sh.set_texture(tx);
    UnBind();
}

Ensamble_Of_Atoms::~Ensamble_Of_Atoms() {
    free(m_ats);
}


void Ensamble_Of_Atoms::Add_Instance_Layout(){

    AMD::Vec3 off_set[num_atoms];
    float types[num_atoms];
    for (int i = 0; i<num_atoms; i++){
        off_set[i] = m_ats[i].get_coords();
        types[i] = m_ats[i].get_type();
    }
    
    m_VAO.AddBuffer(off_set,sizeof(AMD::Vec3), num_atoms);
    m_VAO.AddBuffer(types,sizeof(float), num_atoms);
}

void Ensamble_Of_Atoms::Bind(){
    this->m_sh.bind();
    
    
}

void Ensamble_Of_Atoms::UnBind(){
    this->m_sh.unbind();
}

void Ensamble_Of_Atoms::DrawBind(){
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
    
}


unsigned int Ensamble_Of_Atoms::num_idx(){
    return this->m_IBO.get_num();
}


void Ensamble_Of_Atoms::Set_Op(Operator& op, Light_Src& l){
    this->m_sh.Set_Uniforms(op, l);
    
}

void Ensamble_Of_Atoms::Bind_Texture(Texture& tx,int layer){
    this->m_sh.set_texture(tx);
}



void Ensamble_Of_Atoms::Compute_Neighbors(){
    float cut;
    int num_nebs;
    int count = 0;
    AMD::Vec3 diff;
    for (int i = 0; i< num_atoms; i++){
        num_nebs =0;
        for (int j = i+1; j< num_atoms; j++){
            diff = this->m_ats[i].get_coords() - this->m_ats[j].get_coords();
            if(this->m_ats[i].get_type() ==2 && this->m_ats[j].get_type() == 2 ){cut = 2.5;}
            else{cut = 1.7;}
            if(diff.len() <= cut){
                neb_IDs[count][0] = i; neb_IDs[count][1] = j;
                count++;
                num_nebs++;
            }
        
        }
    }
    num_bonds = count;
}

AMD::Vec3 Ensamble_Of_Atoms::Get_Box(){
    float x = m_ats[0].dx; float y = m_ats[0].dy; float z = m_ats[0].dz;
    return AMD::Vec3(x, y, z);
}



//============================================================================================
Bonds::Bonds(Ensamble_Of_Atoms &ats, Texture& tx)
:m_sh(shader_file)
{
    Cylinder cy;
    VertexBuffer vb(cy.verts, cy.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(cy.indices,cy.num_idx());
    Add_Instance_Layout(ats);
    m_sh.Get_Uniforms(m_num_tex, uniform_text_names);
    Bind();
    m_sh.set_texture(tx);
    UnBind();
    
}

Bonds::~Bonds() {}

void Bonds::Add_Instance_Layout(std::string atom_file) {
    Atom* my_atoms = atoms(atom_file);
    Bond bd[4];  //= (Bond*)malloc(4*sizeof(Bond));
    AMD::Vec3 bond_os[4];
    AMD::Vec3 bond_ang[4];
    AMD::Vec2 type_vec[4];
    for (int i = 0; i < 4; i++){
        bd[i] = Bond(my_atoms[0],my_atoms[i + 1]);
        bond_os[i] = bd[i].get_off_set();
        bond_ang[i] = bd[i].get_angles();
        type_vec[i] = bd[i].m_types;
        
    }
    
    m_VAO.AddBuffer(bond_os,sizeof(AMD::Vec3), 4);
    m_VAO.AddBuffer(bond_ang,sizeof(AMD::Vec3), 4);
    m_VAO.AddBuffer(type_vec,sizeof(AMD::Vec2), 4);
}


void Bonds::Add_Instance_Layout(Ensamble_Of_Atoms& ats) {
    int nb = ats.num_bonds;
    Bond bd[nb];  //= (Bond*)malloc(4*sizeof(Bond));
    AMD::Vec3 bond_os[nb];
    AMD::Vec3 bond_ang[nb];
    AMD::Vec2 type_vec[nb];
    float len[nb];
    for (int i = 0; i < nb; i++){
        int a1 = ats.neb_IDs[i][0]; int a2 = ats.neb_IDs[i][1];
        bd[i] = Bond(ats.m_ats[a1],ats.m_ats[a2]);
        bond_os[i] = bd[i].get_off_set();
        bond_ang[i] = bd[i].get_angles();
        type_vec[i] = bd[i].m_types;
        len[i] = bd[i].get_len();
        num_bonds++;
        
        
    }
    
    m_VAO.AddBuffer(bond_os,sizeof(AMD::Vec3), num_bonds);
    m_VAO.AddBuffer(bond_ang,sizeof(AMD::Vec3), num_bonds);
    m_VAO.AddBuffer(type_vec,sizeof(AMD::Vec2), num_bonds);
    m_VAO.AddBuffer(len,sizeof(float), num_bonds);
}

void Bonds::Bind() {
    this->m_sh.bind();
}

void Bonds::UnBind() { 
    this->m_sh.unbind();
}

void Bonds::DrawBind() { 
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}

void Bonds::Bind_Texture(Texture& tx, int layer) {
    m_sh.set_texture(tx);
}

unsigned int Bonds::num_idx() { 
    return this->m_IBO.get_num();
}

void Bonds::Set_Op(Operator &op, Light_Src &l) { 
    this->m_sh.Set_Uniforms(op, l);
}
    



// ####################################################3






Grid_Mesh::Grid_Mesh(Texture& tx)
    :m_sh("GRID", "GRID"){
        Grid gr(0.5);
        VertexBuffer vb(gr.verts, gr.num_verts()*sizeof(AMD::Vertex));
        m_VAO.Add_Vertex_Buffer(vb);
        m_IBO.Gen_Buffer(gr.L_indices,gr.num_idx('L'));
        m_sh.bind();
        m_sh.set_texture(tx);
        m_sh.unbind();
    }

Grid_Mesh::~Grid_Mesh() {}

void Grid_Mesh::Bind(){
    m_sh.bind();
}

void Grid_Mesh::UnBind(){
        m_sh.unbind();
    }

void Grid_Mesh::DrawBind() {
        this->m_sh.bind();
        this->m_VAO.bind();
        this->m_IBO.bind();
    }


unsigned int Grid_Mesh::num_idx() {
        return this->m_IBO.get_num();
    }

void Grid_Mesh::Set_Op(Operator &op, Light_Src &l) {
        this->m_sh.Set_Uniforms(op, l);
    }


Quad_Mesh::Quad_Mesh(Texture &tx, AMD::Vec3 vec, const char face)
:m_sh("QUAD", "QUAD")
{
    Get_Face(vec, face);
    Quad qd(points[0],points[1],points[2],points[3], m_cw.c_str());
    VertexBuffer vb(qd.verts, qd.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(qd.indices,qd.num_idx());
    Bind();
    m_sh.set_texture(tx);
    UnBind();
}

Quad_Mesh::~Quad_Mesh() {}

void Quad_Mesh::DrawBind() { 
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}

unsigned int Quad_Mesh::num_idx() { 
    return this->m_IBO.get_num();
}

void Quad_Mesh::Set_Op(Operator &op, Light_Src &l) { 
    this->m_sh.Set_Uniforms(op, l);
}

void Quad_Mesh::Bind() { 
    m_sh.bind();
}

void Quad_Mesh::UnBind() { 
    m_sh.unbind();
}

void Quad_Mesh::Bind_Texture(Texture &tx) { 
    m_sh.set_texture(tx);
}



void Quad_Mesh::Get_Face(AMD::Vec3 BB, const char choice){
    //float x = BB.x*0.33; float y = BB.y*0.29; float z = BB.z*0.25;
    float x = 1.0; float y = 0.0; float z = 0.25;
    switch (choice) {
        case 'F':
            points[0] = AMD::Vec3(-2.2,y, -z);
            points[1] = AMD::Vec3(-2.2,y, z);
            points[2] = AMD::Vec3(-0.25, y, z);
            points[3] = AMD::Vec3(-0.25, y, -z);
            m_cw = "cw";
            break;
            
        case 'B':
            points[0] = AMD::Vec3(-x,-y, -z);
            points[1] = AMD::Vec3(-x,-y, z);
            points[2] = AMD::Vec3(x, -y, z);
            points[3] = AMD::Vec3(x, -y, -z);
            m_cw = "ccw";
            break;
            
        case 'L':
            points[0] = AMD::Vec3(-x,-y, -z);
            points[1] = AMD::Vec3(-x,-y, z);
            points[2] = AMD::Vec3(-x, y, z);
            points[3] = AMD::Vec3(-x, y, -z);
            m_cw = "ccw";
            break;
        case 'R':
            points[0] = AMD::Vec3(x,-y, -z);
            points[1] = AMD::Vec3(x,-y, z);
            points[2] = AMD::Vec3(x, y, z);
            points[3] = AMD::Vec3(x, y, -z);
            m_cw = "cw";
            break;
            
        default:
            break;
    }
}


Box_Bounds::Box_Bounds(Texture &tx, AMD::Vec3 BB)
:m_sh("BOX", "BOX"){ 
    Cube cb(BB);
    VertexBuffer vb(cb.verts, cb.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(cb.indices,cb.num_idx());
    Bind();
    m_sh.set_texture(tx);
    UnBind();
}

Box_Bounds::~Box_Bounds() {}




void Box_Bounds::DrawBind() { 
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}

unsigned int Box_Bounds::num_idx() { 
    return this->m_IBO.get_num();
}

void Box_Bounds::Set_Op(Operator &op, Light_Src &l) { 
    this->m_sh.Set_Uniforms(op, l);
}

void Box_Bounds::Bind() { 
    this->m_sh.bind();
}

void Box_Bounds::UnBind() { 
    this->m_sh.unbind();
}

void Box_Bounds::Bind_Texture(Texture &tx) { 
    m_sh.set_texture(tx);
}










Test_Object::Test_Object(Texture& tx)
:m_sh(shader_file), m_num_obj(2){

    Sphere sp(1.0);
    VertexBuffer vb(sp.verts, sp.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    Add_Instance_Layout();
    m_IBO.Gen_Buffer(sp.indices,sp.num_idx());
    m_sh.Get_Uniforms(m_num_tex, uniform_text_names);
    Bind();
    m_sh.set_texture(tx);
    UnBind();
}

Test_Object::~Test_Object() {}

void Test_Object::DrawBind() { 
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}

unsigned int Test_Object::num_idx() { 
    return this->m_IBO.get_num();
}

void Test_Object::Set_Op(Operator &op, Light_Src &l) { 
    this->m_sh.Set_Uniforms(op, l);
}

void Test_Object::Bind() { 
    this->m_sh.bind();
}

void Test_Object::UnBind() { 
    this->m_sh.unbind();
}

void Test_Object::Bind_Texture(Texture &tx) { 
    this->m_sh.set_texture(tx);
}



void Test_Object::Add_Instance_Layout(){

    float dx = -2.0;
    AMD::Vec3 off_set[m_num_obj];
    float types[m_num_obj];
    for (int i = 0; i<m_num_obj; i++){
        off_set[i] = AMD::Vec3(dx, 0.0, 0.0);
        types[i] = 1.0;
        dx*= -1.0;
    }
    
    m_VAO.AddBuffer(off_set,sizeof(AMD::Vec3), m_num_obj);
    m_VAO.AddBuffer(types,sizeof(float), m_num_obj);
}

unsigned int Test_Object::num_obj() {
    return this->m_num_obj;
}

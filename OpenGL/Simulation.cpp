//
//  Simulation.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 10/21/22.
//

#include "Simulation.hpp"
#include "FrameBuffer.hpp"
extern int num_atoms;
extern AMD::Vec3 Sim_Box;


Ensamble_Of_Atoms::Ensamble_Of_Atoms(std::string atomfile)
:m_ats(atoms(atomfile)), m_sh(shader_file), file_name(atomfile)
{
    Sphere sp(1.0);
    VertexBuffer vb(sp.verts, sp.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(sp.indices,sp.num_idx());
    Add_Instance_Layout();
    //Bind();
    
    
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
    this->m_VAO.bind();
    this->m_IBO.bind();
    
    
}

void Ensamble_Of_Atoms::UnBind(){
    this->m_sh.unbind();
    this->m_VAO.unbind();
    this->m_IBO.unbind();
}

void Ensamble_Of_Atoms::Draw(int num_draws){
    this->m_VAO.bind();
    this->m_IBO.bind();
    if (num_draws == 1){
        glDrawElements(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0);
    }
    else{
        glDrawElementsInstanced(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0, num_atoms);
    }
    
}


unsigned int Ensamble_Of_Atoms::num_idx(){
    return this->m_IBO.get_num();
}


void Ensamble_Of_Atoms::Set_Op(Operator& op, Light_Src& light){
    this->m_sh.bind();
    this->m_sh.Set_Uniform_MVP(op);
    this->m_sh.Set_Uinform_LightSource(light);
    
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

unsigned int Bonds::num_idx() { 
    return this->m_IBO.get_num();
}

void Bonds::Set_Op(Operator &op, Light_Src &light) {
    this->m_sh.bind();
    this->m_sh.Set_Uniform_MVP(op);
    this->m_sh.Set_Uinform_LightSource(light);
}
    



// ####################################################3


Floor::Floor(float y)
:m_sh(shader_file)
{
    AMD::Vec3 LL(-10.5,y, -5.5);
    AMD::Vec3 LR(10.5,y, -5.5);
    AMD::Vec3 UR(10.5,y, 10.5);
    AMD::Vec3 UL(-10.5,y, 10.5);
    Quad qd(LL,LR,UR,UL, "cw");
    VertexBuffer vb(qd.verts, qd.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(qd.indices,qd.num_idx());
    
}

Floor::~Floor(){}

void Floor::Bind(){
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}


void Floor::UnBind(){
    this->m_sh.unbind();
    this->m_VAO.unbind();
    this->m_IBO.unbind();
}


void Floor::Draw(Operator& op){
    this->m_VAO.bind();
    this->m_IBO.bind();
    //m_VP = op.Get_VP();
    //m_sh.Set_U_Mat4(Uniform_names, op.MVP_ptr);
    glDrawElements(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0);
    this->m_VAO.unbind();
    this->m_IBO.unbind();
    //UnBind();
}





//##############################################################3
Quad_Mesh::Quad_Mesh()
{
    Quad qd(2.0);
    VertexBuffer vb(qd.verts, qd.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(qd.indices,qd.num_idx());
}

Quad_Mesh::Quad_Mesh(AMD::Vec3 LL, AMD::Vec3 LR, AMD::Vec3 UR, AMD::Vec3 UL)
{
    Quad qd(LL,LR,UR,UL, "cw");
    VertexBuffer vb(qd.verts, qd.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(qd.indices,qd.num_idx());
}

Quad_Mesh::~Quad_Mesh() {}


unsigned int Quad_Mesh::num_idx() { 
    return this->m_IBO.get_num();
}


void Quad_Mesh::Bind() { 
    this->m_VAO.bind();
    this->m_IBO.bind();
}

void Quad_Mesh::UnBind() { 
    this->m_VAO.unbind();
    this->m_IBO.unbind();
}





Test_Object::Test_Object()
:m_sh(shader_file)
{
    Axis ax;
    VertexBuffer vb(ax.verts, ax.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(ax.indices,ax.num_idx());
}


Test_Object::~Test_Object() {}

void Test_Object::Draw(){
    Bind();
    glDrawElements(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0);
    UnBind();
}

void Test_Object::Set_Shader(Operator& op, Light_Src& light){
    this->m_sh.bind();
    this->m_sh.Set_Uniform_MVP(op);
    this->m_sh.Set_Uinform_LightSource(light);
}

void Test_Object::Bind() {
    this->m_VAO.bind();
    this->m_IBO.bind();
}

void Test_Object::UnBind() {
    this->m_VAO.unbind();
    this->m_IBO.unbind();
}

void Test_Object::Bind_Texture(Texture& tx){
    m_sh.Set_Texture(m_sampler, tx);
}


Environment::Environment()
:m_sh(shader_file)
{
    Cube cb(1.0);
    VertexBuffer vb(cb.verts, cb.num_verts()*sizeof(AMD::Vertex));
    m_VAO.Add_Vertex_Buffer(vb);
    m_IBO.Gen_Buffer(cb.indices,cb.num_idx());
    
}

Environment::~Environment(){}

void Environment::Bind(){
    this->m_sh.bind();
    this->m_VAO.bind();
    this->m_IBO.bind();
}


void Environment::UnBind(){
    this->m_sh.unbind();
    this->m_VAO.unbind();
    this->m_IBO.unbind();
}

void Environment::Set_Shader(Operator& op, Light_Src& light){
    this->m_sh.bind();
    this->m_sh.Set_Uniform_MVP(op);
    this->m_sh.Set_Uinform_LightSource(light);
}

void Environment::Draw(){
    this->m_VAO.bind();
    this->m_IBO.bind();
    glDrawElements(GL_TRIANGLES,m_IBO.get_num(), GL_UNSIGNED_INT,0);
    UnBind();
}

void Environment::Attach_Texture(Texture& tx){
    m_sh.Set_Texture(m_sampler, tx);
}

void Environment::Attach_Texture(Texture3D& tx){
    m_sh.Set_Texture(m_sampler, tx);
}

void Environment::Attach_Shadow_Map_Texture(const ShadowMap& sm){
    int loc = m_sh.UniformLoc("ShadowMap");
    m_sh.bind();
    sm.ReadBind();
    glUniform1i(loc, sm.Get_Layer());
    
}











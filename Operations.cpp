//
//  Operations.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/3/22.
//

#include "Operations.hpp"




Operator::Operator(const Shader& sh)
{
    M_loc = sh.UniformLoc("u_Model");
    rot_loc =sh.UniformLoc("u_rot");
    V_loc = sh.UniformLoc("u_View");
    src_loc = sh.UniformLoc("l_src");
    Proj_loc = sh.UniformLoc("u_Proj");
    color_loc = sh.UniformLoc("u_color");
    sat_loc = sh.UniformLoc("u_sat");
    Ob_loc = sh.UniformLoc("u_Object");
    light_src_dir = AMD::Vec3(0.0, 1.0, 0.0);
    set_light(light_src_dir);
    set_sat(sat);
    V_translation[2] = -2.0;

    
    
}



Operator::~Operator(){

    
}


/*
 cos(a)*cos(b)  cos(a)*sin(b)*sin(c)-sin(a)*cos(c)  cos(a)*sin(b)*cos(c)+sin(a)*sin(c)
 sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c)-cos(a)*sin(c)
 -sin(b),        cos(b)*sin(c)                       cos(b)*cos(c)


*/
void Operator::rotation(float a, float b, float c, AMD::Mat4& mat){
    AMD::Mat4 rot;
    AMD::Vec4 r0 (cos(a)*cos(b),  cos(a)*sin(b)*sin(c) - sin(a)*cos(c),  cos(a)*sin(b)*cos(c)+sin(a)*sin(c), 0.0);
    AMD::Vec4 r1(sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c)-cos(a)*sin(c), 0.0);
    AMD::Vec4 r2(-sin(b), cos(b)*sin(c), cos(b)*cos(c), 0.0);
    AMD::Vec4 r3(0.0, 0.0, 0.0, 1.0);
    
    rot.assign_row(0, r0);
    rot.assign_row(1, r1);
    rot.assign_row(2, r2);
    rot.assign_row(3, r3);
    mat = rot*mat;
    
    return;
}




void Operator::rotation(AMD::Vec3 ang, AMD::Mat4& mat){
    float a = ang.x; float b = ang.y; float c = ang.z;
    AMD::Mat4 rot;
    AMD::Vec4 r0 (cos(a)*cos(b),  cos(a)*sin(b)*sin(c) - sin(a)*cos(c),  cos(a)*sin(b)*cos(c)+sin(a)*sin(c), 0.0);
    AMD::Vec4 r1(sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c)-cos(a)*sin(c), 0.0);
    AMD::Vec4 r2(-sin(b), cos(b)*sin(c), cos(b)*cos(c), 0.0);
    AMD::Vec4 r3(0.0, 0.0, 0.0, 1.0);
    
    rot.assign_row(0, r0);
    rot.assign_row(1, r1);
    rot.assign_row(2, r2);
    rot.assign_row(3, r3);
    mat = rot*mat;
    
    return;
}



void Operator::translate(float dx, float dy, float dz, AMD::Mat4& mat){
    AMD::Mat4 T;
    T[3][0] = dx;
    T[3][1] = dy;
    T[3][2] = dz;
    mat = T*mat;
    return;
}



void Operator::translate(AMD::Vec3 trans, AMD::Mat4& mat){
    AMD::Mat4 T;
    T[3][0] = trans.x;
    T[3][1] = trans.y;
    T[3][2] = trans.z;
    mat = T*mat;
    return;
}


void Operator::scale(float sx, float sy, float sz, float sw, AMD::Mat4& mat) {
    AMD::Mat4 sc;
    sc[0][0] = sx;
    sc[1][1] = sy;
    sc[2][2] = sz;
    sc[3][3] = sw;
    mat = sc*mat;
    return;
}

void Operator::scale(AMD::Vec4 vec, AMD::Mat4& mat){
    AMD::Mat4 sc;
    sc[0][0] = vec[0];
    sc[1][1] = vec[1];
    sc[2][2] = vec[2];
    sc[3][3] = vec[3];
    mat = sc*mat;
    return;
}

void Operator::Reset(AMD::Mat4& mat){
    
    for (int i = 0; i< 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j){
                mat[i][j] = 1.0;
            }
            else{mat[i][j] = 0.0;}
        }
    }
    
}

void Operator::Projection(float near, float far, float xlim, float ylim){
    float dz = abs(far - near);
    float yalpha = ylim / (2.0 * dz);
    float xalpha = xlim/(2.0 * dz);
    
    Proj_mat.m[0][0] = 1.0 / xalpha;
    Proj_mat.m[1][1] = 1.0 / yalpha;
    Proj_mat.m[2][2] = -1.0*(far + near) / (far - near);
    Proj_mat.m[2][3] = -1.0;
    Proj_mat.m[3][2] = (-2.0*far*near) / (far - near);
    
}



// SET OBJECT MATRIX
void Operator::Ob_set_rotation(AMD::Vec3 ang){
    rotation(ang, Ob_mat);
    //rotation(ang, rot_mat);
}
void Operator::Ob_set_translation(AMD::Vec3 trans){
    translate(trans, Ob_mat);
    
}

void Operator::Ob_set_scale(float sc){
    scale(sc, sc, sc, 1.0, Ob_mat);
    
}

void Operator::Ob_set_scale(AMD::Vec3 sc){
    scale(sc.x, sc.y, sc.z, 1.0, Ob_mat);
    
}
void Operator::set_Object(){
    glUniformMatrix4fv(Ob_loc,1,GL_FALSE, Ob_ptr);
    Reset(Ob_mat);
}



void Operator::M_set_rotation(float ax, float ay, float az) { 
    rotation(ax, ay, az, M_mat);
    rotation(ax, ay, az, rot_mat);
    glUniformMatrix4fv(rot_loc,1,GL_FALSE, rot_ptr);
    Reset(rot_mat);
}

void Operator::M_set_rotation() {
    rotation(M_rotation.x,M_rotation.y,M_rotation.z, M_mat);
    rotation(M_rotation.x, M_rotation.y,M_rotation.z, rot_mat);

}

void Operator::M_set_translation(AMD::Vec3 tr) {
    translate(tr.x, tr.y, tr.z, M_mat);
}

void Operator::M_set_scale(float sx, float sy, float sz, float sw) {
    scale(sx, sy, sz, sw, M_mat);
}

void Operator::set_Model(){
    glUniformMatrix4fv(M_loc, 1, GL_FALSE, M_ptr);
    glUniformMatrix4fv(rot_loc,1,GL_FALSE, rot_ptr);
    //Reset(rot_mat);
    //Reset(M_mat);
}



//#############################################################
void Operator::V_set_rotation(float ax, float ay, float az){
    rotation(ax, ay, az, V_mat);
}

void Operator::V_set_rotation(){
    translate(-V_translation[0], -V_translation[1], -V_translation[2], V_mat);
    rotation(V_rotation[0], V_rotation[1], V_rotation[2], V_mat);
    translate(V_translation[0], V_translation[1], V_translation[2], V_mat);
}

void Operator::V_set_translation(AMD::Vec3 tr){
    translate(tr.x, tr.y, tr.z, V_mat);
}

void Operator::V_set_translation(){
    translate(V_translation.x, V_translation.y, V_translation.z, V_mat);
}

void Operator::V_set_scale(AMD::Vec4 vec){
    scale(vec, V_mat);
}

void Operator::set_View(){
    glUniformMatrix4fv(V_loc, 1, GL_FALSE, V_ptr);
    Reset(V_mat);
}




void Operator::set_projection(float near, float far, float dx, float dy) { 
    Projection(near, far, dx, dy);
    glUniformMatrix4fv(Proj_loc, 1, GL_FALSE, Proj_ptr);
}

void Operator::set_projection(float pj[4]){
    Projection(pj[0],pj[1],pj[2],pj[3]);
    glUniformMatrix4fv(Proj_loc, 1, GL_FALSE, Proj_ptr);
}

void Operator::set_light(AMD::Vec3 src) {
    light_src_dir.x = src.x; light_src_dir.y = src.y; light_src_dir.z = src.z;
    glUniform3f(src_loc, light_src_dir.x, light_src_dir.y,light_src_dir.z);
}


void Operator::set_light(float src[3]) {
    light_src_dir.x = src[0]; light_src_dir.y = src[1]; light_src_dir.z = src[2];
    glUniform3f(src_loc, light_src_dir.x, light_src_dir.y,light_src_dir.z);
}

void Operator::set_light_dir(float theta, float phi){
    light_src_dir.x = cos(phi)*sin(theta);
    light_src_dir.z = sin(phi)*sin(theta);
    light_src_dir.y = cos(theta);
    glUniform3f(src_loc, light_src_dir.x, light_src_dir.y,light_src_dir.z);
}

AMD::Vec3 Operator::get_Light_src(){
    return light_src_dir;
}


void Operator::set_ob_clr(){
    //glUniform4f(color_loc,Ob_Color.r,Ob_Color.g,Ob_Color.b,Ob_Color.a);
}

void Operator::set_ob_clr(AMD::Vec4 clr){
    glUniform4f(color_loc,clr[0],clr[1],clr[2],clr[3]);
}

void Operator::set_sat(float s){
    sat = s;
    glUniform1f(sat_loc,sat);
}

AMD::Vec4& Operator::get_ob_clr(){
    return this ->Ob_Color;
}










/*
 v1 + v' = v2; v' points v1->v2
 v' = v2 - v1; v' points v1->v2
 => v2 - v1 points v1->v2
 */





Projection::Projection() { 
    
}

Projection::~Projection() { 

}

void Projection::set_FOV(float near, float far, float xlim, float ylim) {
    float dz = abs(far - near);
    float yalpha = ylim/(2.0 * dz);
    float xalpha = xlim/(2.0* dz);
    
    Proj_mat[0][0] = 1/xalpha;
    Proj_mat[1][1] = 1/yalpha;
    Proj_mat[2][2] = (far + near) / dz;
    Proj_mat[3][2] = (2*far*near) / dz;
    Proj_mat[2][3] = -1.0;
    

    
}


void Projection::reset(){
    for (int i = 0; i< 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j){
                Proj_mat[i][j] = 1.0;
            }
            else{Proj_mat[i][j] = 0.0;}
        }
    }
}


//
//  My_Types.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 9/18/22.
//

#include "My_Types.hpp"

using namespace AMD;



Vec2::Vec2()
:x(0.0), y(0.0)
{}

Vec2::Vec2(float x, float y)
:x(x), y(y)
{}
Vec2::~Vec2() {}

AMD::Vec2 Vec2::add(const AMD::Vec2 &other) const {
    return Vec2(x + other.x, y+other.y);
}

float *Vec2::get() {
    return &x;;
}

float &Vec2::operator[](const int index) {
    return get()[index];
}


float Vec2::dot(const AMD::Vec2 &other) const {
    return x*other.x + y*other.y;
}

float Vec2::len() const {
    return sqrt(this->dot(*this));
}

AMD::Vec2 Vec2::operator*(float scale) {
    float _x = this->x*scale;
    float _y = this->y*scale;
    
    return Vec2(_x,_y);
}

AMD::Vec2 Vec2::operator+(const AMD::Vec2 &other) const {
    return add(other);
}

AMD::Vec2 Vec2::operator-(const AMD::Vec2 &other) const {
    float _x = this->x - other.x;
    float _y = this->y - other.y;
    
    return Vec2(_x,_y);
}

AMD::Vec2 &Vec2::operator=(const AMD::Vec2 &other) {
    if (this == &other) {
        return *this;
    }
    
    this->x = other.x;
    this->y = other.y;
    return *this;
}


AMD::Vec2 Vec2::operator/(float div) {
    return Vec2(this->x/div, this->y/div);
}

AMD::Vec2 Vec2::operator+=(const AMD::Vec2 &other) {
        this->x = this->x+ other.x;
        this->y = this->y + other.y;
        
        return *this;
}

AMD::Vec2 Vec2::operator*=(float scale) {
        this->x = this->x*scale;
        this->y = this->y*scale;
        
        return *this;
}

void Vec2::print() {
    std::cout << this->x << " " << this->y << std::endl;
}


Vec3::Vec3()
:x(0.0), y(0.0), z(0.0)
{}

Vec3::Vec3(float e_x, float e_y, float e_z)
:x(e_x), y(e_y),z(e_z)
{}


float* Vec3::get(){
    return &x;
}


float& Vec3::operator[](const int index){
    return get()[index];
}

float Vec3::dot(const AMD::Vec3 &other) const { 
    return x*other.x + y*other.y + z*other.z;
}

AMD::Vec3 Vec3::cross(const AMD::Vec3 &other) const { 
    float _x = y*other.z - z*other.y;
    float _y = z*other.x - x*other.z;
    float _z = x*other.y - y*other.x;
    return Vec3(_x, _y, _z);
}

float Vec3::len() const{
    return sqrt(this->dot(*(this)));
}

AMD::Vec3 &Vec3::operator=(const AMD::Vec3 &other) { 
    if (&other == this){
        return  *this;
    }
    else {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }
    return *this;
}

AMD::Vec3 Vec3::operator*(float scale) { 
    return Vec3(x*scale,y*scale, z*scale);
}

AMD::Vec3 Vec3::operator/(float div) { 
    return Vec3(x/div,y/div,z/div);
}


AMD::Vec3 Vec3::operator-(const Vec3& other) const{
    float _x = this->x - other.x;
    float _y = this->y - other.y;
    float _z = this->z - other.z;
    return Vec3(_x,_y,_z);
    
}




AMD::Vec3 Vec3::operator+(const Vec3& other) const{
    float _x = this->x + other.x;
    float _y = this->y + other.y;
    float _z = this->z + other.z;
    return Vec3(_x,_y,_z);
    
}




AMD::Vec3 Vec3::operator+=(const Vec3& other){
    this->x = this->x + other.x;
    this->y = this->y + other.y;
    this->z = this->z + other.z;
    
    return *this;
}

AMD::Vec3 Vec3::operator*=(float scale){
    *this = *this * scale;
    return *this;
    
}

void AMD::Vec3::print(){
    std::cout << x << " " << y << " " << z << std::endl;
}


Vec4::Vec4()
:r(0.0) , g(0.0) , b(0.0) , a(0.0)
{}

Vec4::Vec4(float e_r, float e_g, float e_b, float e_a)
:r(e_r) , g(e_g) , b(e_b) , a(e_a)
{}

Vec4::Vec4(float* e_vec)
:r(e_vec[0]), g(e_vec[1]), b(e_vec[2]), a(e_vec[3]){}

float* Vec4::get(){
    return &r;
}


float& Vec4::operator[](const int& index){
    return get()[index];
}





Mat4::Mat4(){
    for (int i = 0; i< 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j){
                m[i][j] = 1.0;
            }
            else{m[i][j] = 0.0;}
        }
    }
}

AMD::Mat4 Mat4::add(const AMD::Mat4 &other) const {
    Mat4 temp;
    for (int i =0; i<4; i++){
        for (int j = 0; j < 4; j++) {
            temp.m[i][j] = m[i][j] + other.m[i][j];
        }
    }
    return temp;
}

AMD::Mat4 Mat4::operator+(const AMD::Mat4 &other) const {
    return add(other);
}

AMD::Mat4 Mat4::multiply(const AMD::Mat4 &other) const {
    Mat4 temp;
    float el;
    for (int col = 0; col<4; col++){
        for (int i =0; i<4; i++){
            el =0.0;
            for (int j = 0; j < 4; j++) {
                el += other.m[i][j] * m[j][col];
            }
            temp.m[i][col] = el;
        }
    }
    return temp;
}


AMD::Vec4 Mat4::multiply(AMD::Vec4 &other) const {
    Vec4 temp;
    for (int col = 0; col<4; col++){
        for (int i = 0; i<4;i++){
            temp[col] += m[col][i]*other[i];
        }
    }
    return temp;
}

AMD::Mat4 Mat4::operator*(const AMD::Mat4 &other) const{
    return multiply(other);
}


AMD::Vec4 Mat4::operator*(AMD::Vec4& other) const {
    
    return multiply(other);
    
}


AMD::Vec3 Mat4::operator*(Vec3& other) const{
    Vec4 temp(other.x, other.y, other.z, 1.0);
    temp = multiply(temp);
    return Vec3(temp.r, temp.g, temp.b);
    
    
    
}

float* Mat4::operator[](const int &index){
    
    return m[index];
}

void Mat4::print(){
    std::cout <<  std::endl;
    for (int i =0; i<4; i++){
        for (int j = 0; j < 4; j++) {
        std::cout << m[i][j] << ", ";
        }
       std::cout <<  std::endl;
    
    }
    std::cout <<  std::endl;
}

AMD::Mat4& Mat4::operator=(const AMD::Mat4 &other) {
    if (&other == this){
        return  *this;
    }
    
    else{
        for (int i =0; i<4; i++){
            for (int j = 0; j < 4; j++) {
                 this->m[i][j] = other.m[i][j];
            }
        }
        return *this;
    }
}

void Mat4::assign_col(int col_idx, Vec4 col){
    
    for (int i = 0; i<4; i++){
        m[i][col_idx] = col[i];
    }
    
}

void Mat4::assign_row(int row_idx, Vec4 row){
    
    for (int i = 0; i<4; i++){
        m[row_idx][i] = row[i];
    }
    
}


void Mat4::Rotate(Vec3 ang){
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
    *this = rot * (*this);
    
    return;
}


AMD::Mat4 ID(){
    return Mat4();
}


AMD::Mat4 AMD::ROTATION_MATRIX(Vec3 ang){
    
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
    
    
    return rot;
}

float AMD::Get_angle(const Vec3& A, const Vec3& B){
    float c_th= A.dot(B)/(A.len()*B.len());
    return acos(c_th);
}





void AMD::Compute_norms(Vertex* verts,unsigned int* ints, int num){
    Vec3 A, B, _norm;
    int a,b,c;
    for (int i = 0; i< num; i+=3){
        a = ints[i]; b = ints[i+1]; c = ints[i+2];
        A = verts[b].pos - verts[a].pos;
        B = verts[c].pos - verts[a].pos;
        _norm = A.cross(B);
        
        verts[a].norm+=_norm;
        verts[b].norm+=_norm;
        verts[c].norm+=_norm;
        
        verts[a].norm *= 1.0 / verts[a].norm.len();
        verts[b].norm *= 1.0 / verts[b].norm.len();
        verts[c].norm *= 1.0 / verts[c].norm.len();
        
        
    }
}



void AMD::Map_Texture_Coords(Vertex* verts, int num_verts){
    float MAX_X = 0.0; float MAX_Y = 0.0;
    for (int i = 0; i< num_verts; i++){
        if (verts[i].texture.x > MAX_X) {
            MAX_X = verts[i].texture.x;
            }
        
        if (verts[i].texture.y > MAX_Y) {
            MAX_Y = verts[i].texture.y;
            }
    }
    
    for (int j = 0; j<num_verts; j++){
        verts[j].texture.x*= 1.0/MAX_X;
        verts[j].texture.y*= 1.0/MAX_Y;
    }
    
    
}

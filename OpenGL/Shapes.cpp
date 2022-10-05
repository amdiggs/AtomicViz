//
//  Shapes.cpp
//  OpenGL
//
//  Created by Andrew Diggs on 7/14/22.
//

#include "Shapes.hpp"

using namespace AMD;


const Mat4 CT = ROTATION_MATRIX(Vec3(0.0, 0.0, -PI_2));


Circle::Circle(float ex_rad, unsigned int num)
:rad(ex_rad) , num_points(num) {}

Circle::~Circle(){
    free(points);
    free(indices);
}

void Circle::Gen_points(){
    double dth = _2pi / num_points;
    double curr = 0.0;
    this -> points = (Vec3*) malloc((num_points + 1) * sizeof(Vec3));
    this -> points[0].x = 0.0;
    this -> points[0].y = 0.0;
    this -> points[2].z = 0.0;
    for (int i =1; i< (num_points + 1); i++){
        this -> points[i].x = rad*cos(curr);
        this -> points[i].y = rad*sin(curr);
        this -> points[i].z = 0.0;
        curr+=dth;
    }
    return;
}

void Circle::Gen_indices(){
    int count = 0;
    this -> indices = (unsigned int*) malloc(3 * num_points * sizeof(unsigned int));
    for (int i = 1; i<num_points + 1; i++) {
        if (i < num_points) {
            this -> indices[count] = 0;
            this -> indices[count + 1] = i;
            this -> indices[count + 2] = i + 1;
            count+=3;
        }
        else{
            this -> indices[count] = 0;
            this -> indices[count + 1] = num_points;
            this -> indices[count + 2] = 1;
        }
        
    }
    
    return;
}






Cube::Cube()
    {
    set_verts();
    AMD::Compute_norms(verts, indices, m_num_idx);
    }


Cube::~Cube(){}


void Cube::set_verts(){
    float dx = 1.0/2.0; float dy = 1.0/2.0; float dz = 1.0/2.0;
    verts[0].pos = Vec3(-1.0 * dx ,-1.0 * dy, 1.0 * dz);
    verts[1].pos = Vec3(1.0 * dx ,-1.0 * dy, 1.0 * dz);
    verts[2].pos = Vec3(1.0 * dx ,1.0 * dy, 1.0 * dz);
    verts[3].pos = Vec3(-1.0 * dx , 1.0 * dy, 1.0 * dz);
    
    verts[0].texture[0] = 0.0; verts[0].texture[1] = 0.0;
    verts[1].texture[0] = 1.0; verts[1].texture[1] = 0.0;
    verts[2].texture[0] = 1.0; verts[2].texture[1] = 1.0;
    verts[3].texture[0] = 0.0; verts[3].texture[1] = 1.0;
    //
    verts[4].pos = Vec3(-1.0 * dx ,-1.0 * dy, -1.0 * dz);
    verts[5].pos = Vec3(1.0 * dx ,-1.0 * dy, -1.0 * dz);
    verts[6].pos = Vec3(1.0 * dx ,1.0 * dy, -1.0 * dz);
    verts[7].pos = Vec3(-1.0 * dx , 1.0 * dy, -1.0 * dz);
    
    
    verts[4].texture[0] = 0.0; verts[4].texture[1] = 1.0;
    verts[5].texture[0] = 1.0; verts[5].texture[1] = 1.0;
    verts[6].texture[0] = 1.0; verts[6].texture[1] = 0.0;
    verts[7].texture[0] = 0.0; verts[7].texture[1] = 0.0;
    
    for (int i = 0; i<8; i++){
        verts[i].clr = Vec4(0.6, 0.2, 0.4, 1.0);
        
    }
    
}
/*
 
 glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
 glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
 glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
 glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
      7-------6
     /|       /
    / |      /
   3--|-----2
   |  4------5
   |       |
   0-------1
 
 
    {0,1,2}, {0,2,3}, {0,1,4}, {1,4,5},
    {2,3,7}, {2,6,7}, {1,2,5}, {1,5,6},
    {0,3,4}, {3,4,7}, {4,5,6}, {4,6,7}
 */
int Cube::num_idx(){
    return m_num_idx;
}

int Cube::num_verts(){
    return m_num_verts;
}





Triangle::Triangle(){
    gen_verts();
}



void Triangle::gen_verts(){
    
    verts[0].pos = Vec3(-0.3,-0.3, 0.0);
    verts[1].pos = Vec3(0,0.3, 0.0);
    verts[2].pos = Vec3(0.3,-0.3, 0.0);
    
    
    verts[0].clr = Vec4(1.0,0.0,0.0,0.5);
    verts[1].clr = Vec4(1.0,0.0,0.0,0.5);
    verts[2].clr = Vec4(1.0,0.0,0.0,0.5);
    
    verts[0].norm = Vec3(0.0,0.0, 1.0);
    verts[1].norm = Vec3(0,0.0, 1.0);
    verts[2].norm = Vec3(0.0,0.0, 1.0);
    
    
    verts[0].texture = Vec2(0.0,0.0);
    verts[1].texture = Vec2(1.0,0.0);
    verts[2].texture = Vec2(1.0,1.0);
 
    verts[0].index = 0;
    verts[1].index = 1;
    verts[2].index = 2;
}


int Triangle::num_idx(){
    return m_num_idx;
}


int Triangle::num_verts(){
    return m_num_verts;
}

Sphere::Sphere(float e_rad, unsigned int e_num_p)
:rad(e_rad), num_p(e_num_p), m_clr(0.3,0.0,0.8,1.0){
    m_num_verts = (num_p*num_p) +2;
    gen_points();
    gen_indices();
}


Sphere::~Sphere(){
    
}

void Sphere::gen_points(){
    float dtheta = _2pi/(2*(float)num_p);
    float dphi = _2pi/ (float)num_p;
    float theta = dtheta;
    float phi;
    float x, y, z;
    int count = 1;
    verts[0].pos = Vec3(0.0, rad , 0.0);
    verts[0].clr = m_clr;
    verts[0].norm = Vec3(0.0,rad,0.0);
    verts[m_num_verts -1].clr = m_clr;
    verts[m_num_verts- 1].norm = Vec3(0.0,-1.0*rad,0.0);
    verts[m_num_verts -1].pos = Vec3(0.0, -1.0*rad, 0.0);
    for ( int i = 0; i<num_p; i++){
        for (int j = 0; j<num_p; j++){
            phi = j*dphi;
            x = rad*cos(phi)*sin(theta);
            y = rad*sin(phi)*sin(theta);
            z = rad*cos(theta);
            verts[count].pos = Vec3(x,z,-1.0*y);
            verts[count].clr = m_clr;
            verts[count].norm = Vec3(x,z,-1.0*y);
            verts[count].texture[0] = theta; verts[count].texture[1] = phi;
            count ++;
            
            
            
            
        }
        theta+=dtheta;
    }
    return;
}


void Sphere::gen_indices(){
    int last_idx = m_num_verts -1;
    int idx_temp[40000][3];
    int count = 0;
    for (int w = 0; w<num_p; w++){
        if (w+2 < num_p + 1){
            idx_temp[count][0] = 0;
            idx_temp[count][1] = w+1;
            idx_temp[count][2] = w+2;
        }
        else{
            idx_temp[count][0] = 0;
            idx_temp[count][1] = w+1;
            idx_temp[count][2] = w + 2 - num_p;
        }
        count++;
    }
    
    int end = (num_p*num_p) - num_p + 1;
    for (int i = 1; i<end; i++) {
        if(i % num_p){
            idx_temp[count][0] = i;
            idx_temp[count][1] = i + 1;
            idx_temp[count][2] = i + 1 + num_p;
            count ++;
            idx_temp[count][0] = i + 1 + num_p;
            idx_temp[count][1] = i + num_p;
            idx_temp[count][2] = i;
            count ++;
            
            
            
        }
        
        
        else{
            idx_temp[count][0] = i;
            idx_temp[count][1] = i + 1 - num_p;
            idx_temp[count][2] = i + 1;
            count ++;
            idx_temp[count][0] = i + 1;
            idx_temp[count][1] = i + num_p;
            idx_temp[count][2] = i;
            count ++;
        }
        
    }
    
    for (int w = end - 1; w<last_idx - 1; w++){
        if (w+2 < last_idx){
            idx_temp[count][0] = last_idx;
            idx_temp[count][1] = w+1;
            idx_temp[count][2] = w+2;
        }
        else{
            idx_temp[count][0] = last_idx;
            idx_temp[count][1] = w+1;
            idx_temp[count][2] = w + 2 - num_p;
        }
        count++;
    }
    
    int c2 =0;
    for (int p = 0; p<count; p++){
        indices[c2] = idx_temp[p][0];
        indices[c2 + 1] = idx_temp[p][1];
        indices[c2 + 2] = idx_temp[p][2];
        c2+=3;
    }
    m_num_idx = c2;
    
    
}


int Sphere::num_idx(){
    return m_num_idx;
}

int Sphere::num_verts() {
    return m_num_verts;
}






Grid::Grid(float e_spaceing)
:m_spacing(e_spaceing){
    m_num_points = (int)(2.0/m_spacing);
    gen_points();
    gen_line_indices();
    gen_tri_indices();
}


Grid::Grid(std::string file_name)
:m_spacing(0.0), m_num_points(163)
{
    ReadXYZ(file_name, verts, m_num_verts);
    gen_line_indices();
    gen_tri_indices();
}

Grid::~Grid()
{
    
}
int Grid::num_idx(char type) {
    switch (type) {
        case 'L':
            return m_num_line_idx;
            break;
        case 'T':
            return m_num_tri_idx;
            break;
            
        default:
            return  0;
            break;
    }
    
    

}

int Grid::num_verts() { 
    return  m_num_verts;;
}

void Grid::gen_points() { 
    float dx = m_spacing +  (1.99 - m_num_points*m_spacing)/m_num_points;
    int count = 0;
    float x = -0.99;
    float y = -.9;
    float z = -0.99;
    float cmap;
    float r;
    for (int i = 0; i< m_num_points; i++){
        z= -0.99;
        for (int j = 0; j<m_num_points; j++){
            r = (x*x) + (z*z);
            y = 1.8*exp(-1.0*(r/0.25));
            cmap = 0.8 - y;
            verts[count].pos = Vec3(x,y,z);
            verts[count].clr = Vec4(1.0 - cmap,1.0,cmap,1.0);
            //verts[count].norm = Vec3(0.0,1.0,0.0);
            count++;
            z+=dx;

        }
        x+=dx;
    }
    m_num_verts = count;
}

void Grid::gen_line_indices() {
    int count = 0;
    for (int i = 0; i<m_num_verts -1; i++) {
        if ((i+1) % m_num_points && i<m_num_verts - m_num_points ){
        L_indices[count] = i;
        L_indices[count + 1] = i+ m_num_points;
        L_indices[count + 2] = i;
        L_indices[count + 3] = i+1;
        count+=4;
        }
        else if (i<m_num_verts - m_num_points){
            L_indices[count] = i;
            L_indices[count + 1] = i+m_num_points;
            count+=2;
        }
        
        else {
            
            L_indices[count] = i;
            L_indices[count + 1] = i+1;
            count+=2;
            
        }
        
    }
    m_num_line_idx = count;
}



void Grid::gen_tri_indices(){
    int count =0;
    for (int i = 0; i< m_num_verts - m_num_points; i++){
        if ((i+1) % m_num_points){
            T_indices[count] = i;
            T_indices[count + 1] = i + 1;
            T_indices[count + 2] = i + m_num_points;
            count+=3;
            T_indices[count] = i + m_num_points;
            T_indices[count + 1] = i + 1 + m_num_points;
            T_indices[count + 2] = i + 1;
            count+=3;
            
        }
    }
    
    m_num_tri_idx = count;
    return;
}


void Grid::add_norm(){
    
    return;
    
}


//======================================================
Cylinder::Cylinder()
:m_len(3.0), m_rad(0.5)
{
    gen_points();
    gen_indices();
    AMD::Compute_norms(verts, indices, m_num_idx);
    //AMD::Map_Texture_Coords(verts, m_num_verts);
    
    for (int i = 0 ; i< m_num_verts; i++){
        verts[i].pos = CT * verts[i].pos;
        verts[i].norm = CT * verts[i].norm;
    }
}

Cylinder::Cylinder(float e_len, int e_num_th, int e_num_h)
:m_len(e_len)
{
    gen_points();
    gen_indices();
    
}

Cylinder::~Cylinder() { 
    return;
}

int Cylinder::num_idx() { 
    return  m_num_idx;;
}

int Cylinder::num_verts() { 
    return  m_num_verts;
}

void Cylinder::gen_points() {
    int num_z = (int)(m_len/m_dz);
    float x, y, theta;
    float z = 0.0;
    int count = 0;
    for (int i = 0; i<= num_z; i++){
        theta = 0.0;
        for (int j = 0; j< m_num_theta; j++) {
            x = m_rad*cos(theta);
            y = m_rad*sin(theta);
            verts[count].pos = Vec3(x,y,z);
            verts[count].clr = Vec4(abs(sin(theta)),0.0,abs(cos(theta)),1.0);
            verts[count].texture[0] = theta; verts[count].texture[1] = z;
            theta +=m_dth;
            count++;
        }
        z+=m_dz;
    }
    m_num_verts = count;
}

void Cylinder::gen_indices() { 
    int count = 0;
    for (int i = 0; i < m_num_verts - m_num_theta ; i++) {
        if((i+1) % m_num_theta){
            indices[count] = i;
            indices[count + 1] = i + 1;
            indices[count + 2] = i + 1 + m_num_theta;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + m_num_theta + 1;
            indices[count + 5] = i + m_num_theta ;
            count +=6;
            
            
            
        }
        
        
        else{
            indices[count] = i;
            indices[count + 1] = i + 1 - m_num_theta;
            indices[count + 2] = i + 1;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + 1;
            indices[count + 5] = i + m_num_theta;
            count +=6;

        }
    }
    
    m_num_idx = count;
}










void ReadXYZ(std::string in_file, Vertex* verts, int& num_verts){
    
    std::ifstream f_dat;
    f_dat.open(in_file, std::ios::in);
    float x, y, z;
    float cmap;
    int i = 0;
    if (!f_dat.is_open()) {
        std::cout << "FILE DID NOT OPEN!!!" << std::endl;
        exit(-1);
    }
    while (f_dat >> x >> y >> z) {
        cmap = (0.8 + z) / 1.6;
        if (/* DISABLES CODE */ (true)) {
        verts[i].pos = Vec3(x,z,y);
        verts[i].clr = Vec4(cmap, 0.5 + cmap, 1.0 - cmap ,1.0);
        verts[i].norm = Vec3(0.0,0.0,0.0);
        i++;
        }
        else{
            verts[i].pos = Vec3(x,z,y);
            verts[i].clr = Vec4(cmap, 0.2, 1.0 - cmap ,1.0);
            verts[i].norm = Vec3(0.0,0.0,0.0);
            i++;
        }
    }
    
    num_verts = i;
    f_dat.close();
    return;
    
}








void Cone::gen_points() { 
    float r; float _z = 0.0; float dz = 0.1;
    float dth = 0.314159;
    float theta;
    int count = 0;
    float _x, _y;
    for (int i =0; i < 10; i++){
        theta = 0.0;
        r = 1.0 - _z;
        for (int j = 0; j < m_num_theta; j++) {
            _x = r*cos(theta);
            _y = r* sin(theta);
            verts[count].pos = Vec3(_x,_y,_z);
            verts[count].clr = Vec4(0.0,0.0,1.0,1.0);
            theta+=dth;
            count ++;
        }
        _z+=dz;
    }
    verts[count].pos = Vec3(0.0, 0.0, 1.0);
    verts[count].clr = Vec4(0.0,0.0,1.0,1.0);
    m_num_verts = count + 1;
}

void Cone::gen_indices() {
    int count = 0;
    for (int i = 0; i < m_num_verts - m_num_theta - 1; i++) {
        if((i+1) % m_num_theta){
            indices[count] = i;
            indices[count + 1] = i + 1;
            indices[count + 2] = i + 1 + m_num_theta;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + m_num_theta + 1;
            indices[count + 5] = i + m_num_theta ;
            count +=6;
            
            
            
        }
        
        
        else{
            indices[count] = i;
            indices[count + 1] = i + 1 - m_num_theta;
            indices[count + 2] = i + 1;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + 1;
            indices[count + 5] = i + m_num_theta;
            count +=6;

        }
    }
    
    
    int start = m_num_verts - m_num_theta - 1;
    int end = m_num_verts - 1;
    for (int i = start; i < end; i++){
        if((i+1) % m_num_theta){
            indices[count] = i;
            indices[count + 1] = i + 1;
            indices[count + 2] = m_num_verts -1;
            count +=3;
            
            }
        
        
        else{
            indices[count] = i;
            indices[count + 1] = start;
            indices[count + 2] = m_num_verts - 1;
            count +=3;

        }
        
        
    }
    
    m_num_idx = count;
}

Cone::Cone() { 
    gen_points();
    gen_indices();
    AMD::Compute_norms(this ->verts, this->indices, m_num_idx);
}

Cone::~Cone() {}

int Cone::num_idx() {
    return m_num_idx;
}

int Cone::num_verts() { 
    return m_num_verts;
}






void Arrow::gen_points() { 
    float r; float _z = 0.0; float dz = 0.1;
    float dth = 0.314159;
    float theta;
    int count = 0;
    float _x, _y, _z_start;
    

    for (int i =0; i < 30; i++){
        theta = 0.0;
        r = 0.25;
        for (int j = 0; j < m_num_theta; j++) {
            _x = r*cos(theta);
            _y = r* sin(theta);
            verts[count].pos = Vec3(_x,_y,_z);
            verts[count].clr = m_color;
            theta+=dth;
            count ++;
        }
        if (i < 29){
            _z+=dz;
        }
    }
    _z_start = _z;
    for (int i =0; i < 10; i++){
        theta = 0.0;
        r = 1.0 - (_z - _z_start);
        for (int j = 0; j < m_num_theta; j++) {
            _x = r*cos(theta);
            _y = r* sin(theta);
            verts[count].pos = Vec3(_x,_y,_z);
            verts[count].clr = m_color;
            theta+=dth;
            count ++;
        }
        _z+=dz;
    }
    verts[count].pos = Vec3(0.0, 0.0, _z);
    verts[count].clr = m_color;
    m_num_verts = count + 1;
}

void Arrow::gen_indices() { 
    int count = 0;
    for (int i = 0; i < m_num_verts - m_num_theta - 1; i++) {
        if((i+1) % m_num_theta){
            indices[count] = i;
            indices[count + 1] = i + 1;
            indices[count + 2] = i + 1 + m_num_theta;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + m_num_theta + 1;
            indices[count + 5] = i + m_num_theta ;
            count +=6;
            
            
            
        }
        
        
        else{
            indices[count] = i;
            indices[count + 1] = i + 1 - m_num_theta;
            indices[count + 2] = i + 1;
            
            
            indices[count + 3] = i;
            indices[count + 4] = i + 1;
            indices[count + 5] = i + m_num_theta;
            count +=6;

        }
    }
    
    
    int start = m_num_verts - m_num_theta - 1;
    int end = m_num_verts - 1;
    for (int i = start; i < end; i++){
        if((i+1) % m_num_theta){
            indices[count] = i;
            indices[count + 1] = i + 1;
            indices[count + 2] = m_num_verts -1;
            count +=3;
            
            }
        
        
        else{
            indices[count] = i;
            indices[count + 1] = start;
            indices[count + 2] = m_num_verts - 1;
            count +=3;

        }
        
        
    }
    
    m_num_idx = count;
}

Arrow::Arrow(char color) { 
    switch (color) {
        case 'r':
            m_color = Vec4(1.0,0.0,0.0,1.0);
            break;
        case 'g':
            m_color = Vec4(0.0,1.0,0.0,1.0);
            break;
            
        case 'b':
            m_color = Vec4(0.0,0.0,1.0,1.0);
            break;
            
        default:
            break;
    }
    
    gen_points();
    gen_indices();
    AMD::Compute_norms(this->verts, this->indices, m_num_idx);
    Coordinate_Transform();
}

Arrow::Arrow(char color, char dir) {
    switch (color) {
        case 'r':
            m_color = Vec4(1.0,0.0,0.0,1.0);
            break;
        case 'g':
            m_color = Vec4(0.0,1.0,0.0,1.0);
            break;
            
        case 'b':
            m_color = Vec4(0.0,0.0,1.0,1.0);
            break;
            
        default:
            break;
    }
    
    switch (dir) {
        case 'x':
            r_mat = ROTATION_MATRIX(AMD::Vec3(0.0, PI_2, 0.0));
            break;
        
        case 'y':
            r_mat = ROTATION_MATRIX(AMD::Vec3(0.0, 0.0, -PI_2));
            break;
            
        case 'z':
            r_mat = ROTATION_MATRIX(AMD::Vec3(0.0, 0.0, 0.0));
            break;
        default:
            break;
    }
    
    
    gen_points();
    gen_indices();
    AMD::Compute_norms(this->verts, this->indices, m_num_idx);
    Rotation();
    Coordinate_Transform();
}

Arrow::~Arrow() {}

int Arrow::num_idx() { 
    return m_num_idx;
}

int Arrow::num_verts() { 
    return m_num_verts;
}



void Arrow::Coordinate_Transform(){
    for (int i = 0 ; i< m_num_verts; i++){
        verts[i].pos = CT * verts[i].pos;
        verts[i].norm = CT * verts[i].norm;
    }
}


void Arrow::Rotation(){
    for (int i = 0 ; i< m_num_verts; i++){
        verts[i].pos = r_mat* verts[i].pos;
        verts[i].norm = r_mat * verts[i].norm;
    }
}

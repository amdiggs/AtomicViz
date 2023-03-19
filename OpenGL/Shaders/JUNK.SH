#SHADER AXIS
#version 330 core
layout (location = 0) out vec4 color;
in vec4 f_color;
in vec4 f_light;
in vec2 t_coords;
in float t_index;
in vec3 f_pos;

uniform sampler2D u_Texture;
uniform sampler2D Axis_Texture[3];
vec4 t_color;

float line(vec2 st){
    return smoothstep(0.1, 0.0,abs(st.x - st.y));
}

float line2(vec2 st){
    return smoothstep(0.1, 0.0,abs((1.0-st.x) - st.y));
}

void main()
{
    
    if(t_index > 1.0){
        int slot = int(t_index - 2.0);
        t_color = texture(Axis_Texture[slot], t_coords);
        if(t_color.a < 0.25){discard;}
        else{color = f_color*t_color;}
        return;
    }
    else {
        t_color = texture(u_Texture, t_coords);
        color = t_color;
    }
}

#END



#SHADER ATOM
#version 330 core
layout (location = 0) out vec4 color;
in vec4 f_color;
in vec4 f_light;
in vec2 t_coords;
in float t_index;
in float o_type;
in vec3 f_pos;
in vec4 gl_FragCoord;

uniform sampler2D u_Texture;
uniform sampler2D Axis_Texture;
vec4 t_color;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
 
= texture(u_Texture, t_coords);
    if(int(o_type) ==1){
        color = f_light + vec4(0.8,0.6,0.2,1.0) + 0.3*t_color;
        //color*=noise(f_pos.xy);
    }
    else{
    color = f_light + f_color + 0.3*t_color;
    }
    //color = t_color + f_light + f_color;
}

#END



#SHADER AXIS
//#version 330 core
//layout (location = 0) in vec3 v_pos;
//layout (location = 1) in vec4 v_color;
//layout (location = 2) in vec3 v_norm;
//layout (location = 3) in vec2 v_tex;
//layout (location = 4) in float indx;
//out vec4 f_color;
//out vec4 f_light;
//out vec2 t_coords;
//out float l_dot;
//out float t_index;
//out vec3 f_pos;
//
//uniform mat4 u_Object;
//uniform mat4 u_Model;
//uniform mat4 u_rot;
//uniform mat4 u_View;
//uniform mat4 u_Proj;
//
//uniform vec4 l_color;
//uniform vec3 l_src;
//uniform float l_sat;
//
//
//uniform samplerBuffer off_set;
//int off = 1;
//float DOT_PROD(vec3 a, vec3 b){
//    return a.x*b.x + a.y*b.y + a.z*b.z;
//}
//
//
//void main()
//{
//
//    vec4 t_b = texelFetch(off_set,gl_InstanceID);
//    vec4 tr = vec4(t_b.x, t_b.y, t_b.z, 1.0);
//    gl_Position = u_Proj * u_View *  u_Model * vec4(v_pos,1.0);
//    vec4 n_norm = u_rot * vec4(v_norm, 1.0);
//    l_dot = DOT_PROD(vec3(n_norm),normalize(l_src));
//    f_color = v_color;
//    t_coords = v_tex;
//    f_light = l_dot*l_sat*l_color;
//    t_index = indx;
//    f_pos = v_pos;
//
//}
#END





float diffuse_dot;
float spec_dot;


float DOT_PROD(vec3 a, vec3 b){
    return max(0.0,a.x*b.x + a.y*b.y + a.z*b.z);
}





float Get_angle(vec3 A, vec3 B){
    float c_th= dot(A,B);
    return acos(c_th);
}

vec3 Set_Angles(vec3 N_hat){
    float tx;
    vec3 z_hat = vec3(0.0, 0.0, 1.0);
    vec3 y_hat = vec3(0.0, -1.0, 0.0);
    vec3 xy = vec3(N_hat.x, N_hat.y, 0.0);
    
    
    float phi = Get_angle(xy, y_hat);
    if(N_hat.x <= -1.0){tx = 6.283185 - phi;}
    else{tx = phi;}
    float tz = Get_angle(N_hat, z_hat);
    float ty = 0.0;
    return vec3(tx,ty,tz);
    
}

mat3 ROTATION(vec3 N){
    
    vec3 ang = Set_Angles(N);
    float a = ang.x;
    float b = ang.y;
    float c = ang.z;
    
    
    //vec3 c0 = vec3(cos(a)*cos(b),sin(a)*cos(b) , -sin(b));
    //vec3 c1 = vec3(cos(a)*sin(b)*sin(c) - sin(a)*cos(c), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), cos(b)*sin(c));
    //vec3 c2 = vec3(cos(a)*sin(b)*cos(c)+sin(a)*sin(c), sin(a)*sin(b)*cos(c)-cos(a)*sin(c), cos(b)*cos(c));
    
    vec3 c0 = vec3(cos(a),sin(a) , 0.0);
    vec3 c1 = vec3(-sin(a)*cos(c), cos(a)*cos(c), sin(c));
    vec3 c2 = vec3(sin(a)*sin(c), -cos(a)*sin(c), cos(b)*cos(c));
    return mat3(c0,c1,c2);
}

float MAX(float a, float b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

float double_sqrt(float x, float lim){
    float a = lim - abs(x);
    float b = sqrt(a);
    return 0.5 + 0.5 / sqrt(b);
}

float VEC_MAX(vec3 vec){
    float _max;
    float _r = double_sqrt(vec.x, 9.15);
    float _g = double_sqrt(vec.y, 9.15);
    float _b = double_sqrt(vec.z, 16.0);
    _max = MAX(_r,_g);
    return MAX(_max,_b);
}


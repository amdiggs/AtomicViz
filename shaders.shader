#shader vertex
#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_norm;
layout (location = 3) in vec2 v_tex;
layout (location = 4) in int v_idx;
out vec4 f_color;
out vec4 f_light;
out vec2 t_coords;
out float l_dot;

uniform mat4 u_Model;
uniform mat4 u_rot;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform vec4 u_color;
uniform vec3 l_src;
uniform float u_sat;
uniform mat4 u_Object;

uniform samplerBuffer off_set;
int off = 1;
float DOT_PROD(vec3 a, vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


void main()
{

    vec4 t_b = texelFetch(off_set,gl_InstanceID);
    vec4 tr = vec4(t_b.x, t_b.y, t_b.z, 0.0);
    gl_Position = u_Proj * u_View *  u_Model * u_Object * (tr + vec4(v_pos,1.0));
    vec4 n_norm = u_rot * vec4(v_norm, 1.0);
    l_dot = DOT_PROD(vec3(n_norm),normalize(l_src));
    f_color = l_dot*vec4(0.95,0.76,0.46,0.2) + (u_color + v_color);
    t_coords = v_tex;
    //f_color = t_b;
    
}

#shader fragment
#version 330 core
layout (location = 0) out vec4 color;
in vec4 f_color;
in float l_dot;
in vec2 t_coords;

uniform sampler2D u_Texture;
void main()
{
    vec4 f_light = vec4(l_dot);
    vec4 f_shade = vec4(0.3,0.3,0.3,1.0)*(1.0 - l_dot);
    vec4 t_color = texture(u_Texture, t_coords);
    //color = (f_light - f_shade + f_color)/2;
    color = f_color + t_color;
}

#SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_norm;
layout (location = 3) in vec2 v_tex;
layout (location = 4) in float v_indx;

out vec4 f_color;
out vec4 f_light;
out vec2 t_coords;
out float t_index;
out vec3 f_pos;

float l_dot;

uniform mat4 u_Model;
uniform mat4 u_rot;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform vec4 l_color;
uniform vec3 l_src;
uniform float l_sat;
float DOT_PROD(vec3 a, vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


void main()
{

    
    gl_Position = u_Proj * u_View * u_Model * vec4(v_pos,1.0);
    vec4 n_norm = u_rot * vec4(v_norm, 1.0);
    l_dot = DOT_PROD(vec3(n_norm),normalize(l_src));
    f_color = v_color;
    t_coords = v_tex;
    f_light = l_dot*l_sat*l_color;
    t_index = v_indx;
    f_pos = v_pos;
    
}
#END


#SHADER FRAGMENT
#version 330 core
layout (location = 0) out vec4 color;

in vec4 f_color;
in vec4 f_light;
in vec2 t_coords;
in float l_dot;
in float t_index;
in vec3 f_pos;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;
vec4 t_color;
vec4 t_color2;



void main()
{
 
    t_color = texture(u_Texture, t_coords);
    t_color2 = texture(u_Texture2, t_coords);
    color = vec4(f_color.xyz,1.0);
}

#END


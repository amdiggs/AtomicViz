#SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_norm;
layout (location = 3) in vec2 v_tex;
layout (location = 4) in float v_indx;



out vec3 f_pos;
out vec4 f_color;
out vec3 f_norm;
out vec2 t_coords;
out float t_index;

uniform mat4 u_MVP;
uniform mat3 u_Normal;

//For shadow map
uniform mat4 u_LightMVP;
out vec4 s_pos;

void main()
{

    
    gl_Position = u_MVP * vec4(v_pos,1.0);
    f_norm = u_Normal * v_norm;
    f_pos = v_pos;
    f_color = v_color;
    t_coords = v_tex;
    t_index = v_indx;
    s_pos = u_LightMVP * vec4(v_pos,1.0);
    
}
#END


#SHADER FRAGMENT
#version 330 core
layout (location = 0) out vec4 color;

in vec3 f_pos;
in vec4 f_color;
in vec3 f_norm;

in vec2 t_coords;
in float t_index;

in vec4 s_pos;
//Light Uniforms Struct
struct Light_Source{
    vec4 clr;
    vec3 dir;
    float sat;
    
};

uniform Light_Source l_src;

//Texture Uniforms
uniform sampler2D Env_Tex;
vec4 t_color;

uniform sampler2DShadow ShadowMap;


float Shadow_Factor(float dp){
    float bias = (1.0 - dp)*0.005;
    vec3 proj_coords = s_pos.xyz/s_pos.w;
    vec3 UV_Coords;
    UV_Coords.x = 0.5*proj_coords.x + 0.5;
    UV_Coords.y = 0.5*proj_coords.y + 0.5;
    UV_Coords.z = 0.5*proj_coords.z + 0.5 - bias;
    //float Depth = texture(ShadowMap, UV_Coords).x;
    return 0.5*texture(ShadowMap, UV_Coords) + 0.5;
    //float bias = 0.025;
    //if (Depth + bias < z){return 0.5;}
    //else{return 1.0;}
}

void main()
{
 
    t_color = texture(Env_Tex, t_coords);
    vec4 f_junk = l_src.clr + vec4(l_src.dir,l_src.sat);
    float l_dot = dot(l_src.dir,f_norm);
    color = 0.5*l_dot*l_src.clr + Shadow_Factor(l_dot)*t_color;
}

#END


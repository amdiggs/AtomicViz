#SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_norm;
layout (location = 3) in vec2 v_tex;
layout (location = 4) in float v_indx;



out vec4 f_pos;
out vec4 f_color;
out vec3 f_norm;
out vec3 t_coords;
out float t_index;

uniform mat4 u_MVP;
uniform mat3 u_Normal;



void main()
{

    
    gl_Position = u_MVP * vec4(v_pos,1.0);
    f_norm = u_Normal * v_norm;
    f_pos = u_MVP * vec4(v_pos,1.0);
    f_color = v_color;
    t_coords = vec3(v_tex,v_indx);
    t_index = v_indx;
    
}
#END


#SHADER FRAGMENT
#version 330 core
layout (location = 0) out vec4 color;

in vec4 f_pos;
in vec4 f_color;
in vec3 f_norm;

in vec3 t_coords;
in float t_index;

//Light Uniforms Struct
struct Light_Source{
    vec4 clr;
    vec3 dir;
    float sat;
    
};

uniform Light_Source l_src;

//Texture Uniforms
uniform sampler3D Vol_Tex;
vec4 t_color;


void main()
{
 
    t_color = texture(Vol_Tex, t_coords);
    vec4 f_junk = l_src.clr + vec4(l_src.dir,l_src.sat);
    if(t_color.r > 0.1){
        color = vec4(1.0,1.0,1.0,0.0);
        //discard;
    }
    else{
        color = vec4(1.0, 0.0, 0.0, 0.2);
    }
    
}
    

#END


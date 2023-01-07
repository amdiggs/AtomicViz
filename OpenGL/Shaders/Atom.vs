#SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_norm;
layout (location = 3) in vec2 v_tex;
layout (location = 4) in float indx;
layout (location = 5) in vec3 v_os;
layout (location = 6) in float v_type;

out vec4 f_color;
out vec4 f_light;
out vec2 t_coords;
out float l_dot;
out float t_index;
out float f_type;
out vec3 f_pos;
out float cam_dot;
out vec3 cam_view;


uniform mat4 u_Model;
uniform mat4 u_rot;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform vec4 l_color;
uniform vec3 l_src;

float scale;

float DOT_PROD(vec3 a, vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


void main()
{

    
    if(int(v_type) == 1){scale = 0.4;}
    else{scale= 0.6;}
    vec3 sc_pos = scale * v_pos;
    gl_Position = u_Proj * u_View * u_Model * (vec4(sc_pos,1.0) + vec4(v_os,0.0));
    vec4 n_norm = u_rot * normalize(vec4(v_norm , 0.0));
    vec3 temp = normalize(gl_Position.xyz);
    vec3 obs = vec3(-gl_Position.x,-gl_Position.y,-u_View[3][2]);
    
    l_dot = DOT_PROD(normalize(vec3(n_norm)),normalize(l_src));
    cam_dot = DOT_PROD(normalize(vec3(n_norm)),normalize(obs));
    f_light = l_color;
    f_color = v_color;
    cam_view = obs;
    t_coords = v_tex;
    t_index = indx;
    f_type = v_type;
    f_pos = v_pos;
    
}
#END


#SHADER FRAGMENT
#version 330 core
layout (location = 0) out vec4 color;
in vec4 f_color;
in vec4 f_light;
in vec2 t_coords;
in float t_index;
in float f_type;
in vec3 f_pos;

in float l_dot;
in float cam_dot;
in vec3 cam_view;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;
uniform sampler2D u_map;
vec4 t_color;
vec4 t_color2;
vec4 N_map;

float DOT_PROD(vec3 a, vec3 b){
    vec3 ta = normalize(a);
    vec3 tb = normalize(b);
    return ta.x*tb.x + ta.y*tb.y + ta.z*tb.z;
}

void main()
{
 
    N_map = texture(u_map, t_coords);
    t_color = texture(u_Texture, t_coords);
    t_color2 = texture(u_Texture2, t_coords);
    
    float border = smoothstep(0.95, 1.0,1.05 - cam_dot);
    float shine = smoothstep(0.7, 1.0, l_dot);
    vec4 light_tot = 0.3*vec4(1.0)*shine*shine*shine;
    vec3 test = vec3(cam_view.x,cam_view.y,-cam_view.z);
    vec3 Normal = N_map.xyz*2.0 - 1.0;
    if(int(f_type) == 1){
        color = light_tot + vec4(0.55*vec3(0.9,0.2,0.2)  + 0.45*f_light.xyz*abs(DOT_PROD(Normal,test)), 1.0);

    }
    else{
        color = light_tot + vec4(0.55*vec3(0.2,0.2,0.9)  + 0.45*f_light.xyz*abs(DOT_PROD(Normal,test)), 1.0);
    }
}

#END


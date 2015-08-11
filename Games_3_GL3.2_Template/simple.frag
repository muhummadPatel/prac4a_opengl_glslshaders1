#version 330
in vec3 frag_vertex;
in vec3 frag_normal;
in vec3 frag_surfaceToLight1;
in vec2 frag_texCoord;

uniform vec4 frag_colour;



vec3 camera_position = vec3(0.0, 0.0, 3.0); //make uniform
const int num_lights = 2;
uniform vec3 light_positions[num_lights];
uniform vec3 light_intensities[num_lights];
uniform float k_ambient;
float shine = 0.9;

uniform sampler2D t;

out vec4 out_color;

//optimise the pants off of this craptastic method
//vec3 lightUp(vec3 light_position, vec3 intensity){
//    vec3 ambient = k_ambient * frag_colour.rgb * intensity;//actually, move ambient outside (independent of light sources)

//    vec3 n_normal = normalize(frag_normal);
//    vec3 n_surfaceToLight = normalize(light_position - frag_vertex);
//    float k_diffuse = max(dot(n_normal, n_surfaceToLight), 0.0f);
//    vec3 diffuse = k_diffuse * frag_colour.rgb *  intensity;


//    vec3 incidence_vect = -n_surfaceToLight;
//    vec3 reflection_vect = reflect(incidence_vect, n_normal);
//    vec3 n_surfaceToCamera = normalize(camera_position - frag_vertex);
//    float cos_angle = max(0.0, dot(n_surfaceToCamera, reflection_vect));
//    float k_specular = 0.0;
//    if(k_diffuse > 0){
//        k_specular = pow(cos_angle, shine);
//    }
//    vec3 specular = k_specular * vec3(1.0, 1.0, 1.0) * intensity;

//    return (ambient + diffuse + specular);
//}

void main( )
{
//    vec3 sum = vec3(0.0, 0.0, 0.0);
//    for (int i = 0; i < num_lights; i++){
//        sum += lightUp(light_positions[i], light_intensities[i]);
//    }

//    out_color = vec4(sum, 1.0f); //vec4(colour, 1.0);
    out_color = texture(t, frag_texCoord);// * vec4(1.0, 1.0, 1.0, 1.0);
}

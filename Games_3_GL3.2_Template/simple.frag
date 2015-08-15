#version 330
in vec3 frag_vertex;
in vec3 frag_normal;
in vec2 frag_texCoord;

vec3 camera_position = vec3(0.0, 0.0, 3.0);
vec3 n_normal;

const int num_lights = 2;
float shine = 5;
uniform float k_ambient;
uniform vec3 light_positions[num_lights];
uniform vec3 light_intensities[num_lights];

uniform vec4 frag_colour;
uniform bool useTexture;
uniform sampler2D text;

out vec4 out_color;

//computes and returns the effect of the given light on this fragment
vec3 lightUp(vec3 light_position, vec3 intensity, vec4 surf_colour){
    //compute the ambient component
    vec3 ambient = k_ambient * surf_colour.rgb * intensity;

    //direction vector from the fragment surface to the light
    vec3 n_surfaceToLight = normalize(light_position - frag_vertex);

    //Compute the diffuse component
    float k_diffuse = max(dot(n_normal, n_surfaceToLight), 0.0f);
    vec3 diffuse = k_diffuse * surf_colour.rgb *  intensity;

    //compute the specular component
    vec3 incidence_vect = -n_surfaceToLight;
    vec3 reflection_vect = reflect(incidence_vect, n_normal);
    vec3 n_surfaceToCamera = normalize(camera_position - frag_vertex);
    float cos_angle = max(0.0, dot(n_surfaceToCamera, reflection_vect));
    float k_specular = pow(cos_angle, shine);
    vec3 specular = k_specular * vec3(1.0, 1.0, 1.0) * intensity;

    //phong lighting eqn
    return (ambient + diffuse+ specular);
}

//determines the color of the fragment and then sets the color
//to the sum of the effect of all the light sources in the scene
void main( void )
{
    //use default colour or texture(if enabled)
    vec4 col = frag_colour;
    if(useTexture){
        col = texture(text, frag_texCoord);
    }

    //compute the sum of the effects of the 2 lights in the scene
    n_normal = normalize(frag_normal);
    vec3 sum = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < num_lights; i++){
        sum += lightUp(light_positions[i], light_intensities[i], col);
    }

    //set the colour of this fragment to the computed sum
    out_color = vec4(sum, 1.0);
}

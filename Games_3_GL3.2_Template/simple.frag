#version 330
in vec3 frag_vertex;
in vec3 frag_normal;
in vec3 frag_surfaceToLight1;

uniform vec4 frag_colour;

vec3 camera_position = vec3(0.0, 0.0, 3.0);
uniform vec3 light_position;
uniform float k_ambient;
uniform vec3 intensity;
float shine = 0.9;

out vec4 out_color;
void main( void )
{
//    vec3 NN = normalize(N);
//    vec3 EE = normalize(E);
//    vec3 LL = normalize(L);
//    vec3 amb, diff, spec;
//    vec3 H = normalize(LL + EE);
//    float kd = max(dot(L, N), 0.0);
//    float ks = pow(max(dot(NN, H), 0.0), shine);

//    amb = k_ambient * frag_colour * intensity;
//    diff = kd * frag_colour * intensity;
//    spec = ks * vec3(1.0, 1.0, 1.0) * intensity;

//    out_color = vec4((amb + diff + spec).xyz, 1.0);

    vec3 ambient = k_ambient * frag_colour.rgb * intensity;

    vec3 n_normal = normalize(frag_normal);
    vec3 n_surfaceToLight = normalize(light_position - frag_vertex);
    float k_diffuse = max(dot(n_normal, n_surfaceToLight), 0.0f);
    vec3 diffuse = k_diffuse * frag_colour.rgb *  intensity;


    vec3 incidence_vect = -n_surfaceToLight;
    vec3 reflection_vect = reflect(incidence_vect, n_normal);
    vec3 n_surfaceToCamera = normalize(camera_position - frag_vertex);
    float cos_angle = max(0.0, dot(n_surfaceToCamera, reflection_vect));
    float k_specular = 0.0;
    if(k_diffuse > 0){
        k_specular = pow(cos_angle, shine);
    }
    vec3 specular = k_specular * vec3(1.0, 1.0, 1.0) * intensity;

    out_color = vec4(ambient + diffuse + specular, 1.0f); //vec4(colour, 1.0);
}

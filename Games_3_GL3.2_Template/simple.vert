#version 330
in vec4 vertex;

layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_colour;//

uniform mat4 MVP;//
uniform mat3 MVN;//
uniform vec3 light_position;

out vec3 frag_vertex;
out vec3 frag_normal;
out vec3 frag_colour;
out vec3 frag_surfaceToLight;

void main( void )
{
//    N = vertex_normal.xyz;
//    L = light_position.xyz - vertex.xyz;
//    E = -vertex.xyz;

//    frag_colour = vertex_colour;
//    gl_Position = vertex;

    vec4 transformed_vertex = MVP * vertex;

    frag_vertex = vec3(transformed_vertex.xyz);
    frag_normal = normalize(MVN * vertex_normal);
    frag_colour = vertex_colour;
    frag_surfaceToLight = light_position - transformed_vertex.xyz;

    gl_Position = MVP * vertex;
}

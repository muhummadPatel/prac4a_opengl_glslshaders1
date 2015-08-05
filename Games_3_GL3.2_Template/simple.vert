#version 330
in vec4 vertex;

layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_colour;

uniform mat4 MVP;
uniform mat3 MVN;

out vec3 normal;
out vec3 colour;

void main( void )
{
    normal = normalize(MVN * vertex_normal);
    colour = vertex_colour;

    gl_Position = MVP * vertex;
}

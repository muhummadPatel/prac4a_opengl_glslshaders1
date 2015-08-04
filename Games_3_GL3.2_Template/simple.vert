#version 330
in vec4 vertex;
layout(location = 1) in vec3 vertex_colour;

uniform mat4 MVP;

out vec3 colour;

void main( void )
{
    colour = vertex_colour;
    gl_Position = MVP * vertex;
}

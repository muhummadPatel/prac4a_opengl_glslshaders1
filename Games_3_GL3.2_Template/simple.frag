#version 330
in vec3 colour;

uniform vec4 fcolor;

out vec4 fragColor;
void main( void )
{
    fragColor = vec4(colour, 1.0);
}

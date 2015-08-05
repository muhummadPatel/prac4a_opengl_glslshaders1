#version 330
in vec3 colour;

uniform float k_ambient;
uniform vec3 intensity;

out vec4 frag_color;
void main( void )
{
    vec3 ambient = k_ambient * colour * intensity;

    frag_color = vec4(ambient, 1.0f); //vec4(colour, 1.0);
}

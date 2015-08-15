#version 330
in vec3 vertex;

layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_uv;

uniform mat4 MVP;
uniform mat3 MVN; //to get the normals into the correct coordinate space

out vec3 frag_vertex;
out vec3 frag_normal;
out vec3 frag_colour;
out vec2 frag_texCoord;

void main( void )
{
    vec4 transformed_vertex = MVP * vec4(vertex, 1.0);

    frag_vertex = vec3(transformed_vertex.xyz);
    frag_normal = normalize(MVN * vertex_normal);
    frag_texCoord = vertex_uv;

    gl_Position = MVP * vec4(vertex, 1.0);
}

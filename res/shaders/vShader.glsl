#version 330 core

layout (location = 0) in vec4 vertex; //<vec3 position, vec2 texcoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main(){
    TexCoords  = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
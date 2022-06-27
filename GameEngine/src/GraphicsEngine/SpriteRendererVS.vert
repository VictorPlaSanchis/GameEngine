#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

uniform vec3 transform;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
    vTexCoord = texCoord;
    vColor = vec4(color, 1.0);
    gl_Position = vec4(position, 1.0);
}
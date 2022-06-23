#version 330 core

layout(location = 0) in vec3 modelPosition;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

in vec3 transformObject;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
    vTexCoord = texCoord;
    vColor = vec4(color, 1.0);
    gl_Position = vec4(modelPosition + transformObject, 1.0);
}
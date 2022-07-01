#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

uniform vec3 transform;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 vVertex;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    vTexCoord = texCoord;
    vec4 positionProjected = projection * view * model * vec4(position, 1.0);
    vColor = color;
    vVertex = positionProjected;
    gl_Position = positionProjected;
}
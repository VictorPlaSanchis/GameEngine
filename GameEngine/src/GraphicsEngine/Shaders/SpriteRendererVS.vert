#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normalCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec3 parentPosition;

out vec3 vVertex;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    vTexCoord = texCoord;
    vColor = color;
    vVertex = (projection * view * model * vec4(position, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(position + parentPosition, 1.0);
}
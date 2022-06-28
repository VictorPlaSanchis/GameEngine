#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

uniform vec3 transform;

uniform vec3 cameraPosition;
uniform mat4 projectionMatrix;

uniform mat4 modelViewMat;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
    vTexCoord = texCoord;
    vColor = vec4(color, 1.0);
    gl_Position = projectionMatrix * modelViewMat * vec4(position + transform, 1.0);
}
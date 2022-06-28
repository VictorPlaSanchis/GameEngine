#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

uniform vec3 transform;

uniform vec3 cameraPosition;
uniform mat4 projectionMatrix;

uniform vec4 modelViewMat0;
uniform vec4 modelViewMat1;
uniform vec4 modelViewMat2;
uniform vec4 modelViewMat3;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
    
    mat4 modelViewMatrix;
    modelViewMatrix[0] = modelViewMat0;
    modelViewMatrix[1] = modelViewMat1;
    modelViewMatrix[2] = modelViewMat2;
    modelViewMatrix[3] = modelViewMat3;

    vTexCoord = texCoord;
    vColor = vec4(color, 1.0);
    gl_Position = modelViewMatrix * vec4(position + transform, 1.0);
}
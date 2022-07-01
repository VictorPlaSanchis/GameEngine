#version 330 core

uniform sampler2D textureSample;

in vec3 vColor;
in vec2 vTexCoord;
in vec4 vVertex;
out vec4 fragColor;

void main()
{
    float colorZ = vVertex.z - 4.0f;
    fragColor = vec4(colorZ, 0.0f, 0.0f, 1.0f);
}
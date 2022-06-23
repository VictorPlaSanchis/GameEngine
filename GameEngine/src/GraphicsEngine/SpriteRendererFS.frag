#version 330 core

uniform sampler2D textureSample;

in vec4 vColor;
in vec2 vTexCoord;
out vec4 fragColor;

void main()
{
    //fragColor = vColor;
    fragColor = vec4(texture(textureSample, vTexCoord).xyz, 1.0);
}
#version 330 core

uniform sampler2D textureSample;

in vec3 vColor;
in vec2 vTexCoord;
out vec4 fragColor;

void main()
{
    //fragColor = vec4(vColor,1.0f);
    fragColor = vec4(texture(textureSample, vTexCoord).xyz, 1.0);
}
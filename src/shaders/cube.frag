#version 330 core

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixvalue = 0.2;
uniform vec3 lightColor;

out vec4 outColor;

void main()
{
    outColor = vec4(lightColor, 1.0f) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixvalue);
}
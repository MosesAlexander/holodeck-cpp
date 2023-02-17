#version 330 core

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightColor;

out vec4 outColor;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    outColor = vec4(ambient, 1.0f) * texture(texture1, TexCoord);
}
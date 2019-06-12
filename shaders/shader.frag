#version 330 core

in vec2 texturePosition;

out vec4 color;

uniform sampler2D textureSampler;

void main()
{
    color = texture(textureSampler, texturePosition);
}

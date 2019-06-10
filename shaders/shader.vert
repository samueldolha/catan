#version 330 core

in vec3 vertexPosition;

in vec2 inputTexturePosition;

out vec2 texturePosition;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    texturePosition = inputTexturePosition;
}

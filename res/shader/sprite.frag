#version 460 core

in vec2 TexCoord;
in vec4 VertexColor;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;

void main()
{
    if (uUseTexture)
        FragColor = texture(uTexture, TexCoord);
    else
        FragColor = VertexColor;
}
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = ourColor;
}

#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
out vec4 outColor;

void main()
{
	outColor = color;
};
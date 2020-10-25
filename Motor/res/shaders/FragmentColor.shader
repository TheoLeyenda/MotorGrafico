/*#version 330 core

in vec4 color;
out vec4 outColor;

in vec2 texCoord;
uniform sampler2D ourTexture;
void main()
{
	outColor = texture(ourTexture, texCoord) * color;
};
*/

#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
out vec4 outColor;

void main()
{
	outColor = color;
};
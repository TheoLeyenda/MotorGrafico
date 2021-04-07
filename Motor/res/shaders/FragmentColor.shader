
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
out vec4 outColor;

struct DirectionLight
{
	vec3 colour;
	float ambientIntensity;
};

uniform DirectionLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	outColor = color * ambientColour;
};
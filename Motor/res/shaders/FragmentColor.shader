
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
out vec4 outColor;

in vec3 Normal;

struct DirectionLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform DirectionLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	outColor = color * (ambientColour + diffuseColor);
};
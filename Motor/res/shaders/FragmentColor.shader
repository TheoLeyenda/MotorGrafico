
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
in vec3 Normal;
in vec3 FragPos;

struct DirectionLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material 
{
	float specularIntensity;
	float shininess;
};

uniform DirectionLight directionalLight;
uniform Material material;

uniform vec3 posLight;
uniform vec3 cameraPos;

out vec4 outColor;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	vec3 dirLight = normalize(posLight - FragPos);

	float diffuseFactor = max(dot(normalize(Normal), dirLight), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0, 0, 0, 0);
	
	if (diffuseFactor > 0.0f)
	{
		vec3 fragToCamera = normalize(cameraPos - FragPos);
		vec3 reflectedVertex = normalize(reflect(-dirLight, normalize(Normal)));
		
		float specularFactor = max(dot(fragToCamera, reflectedVertex),0.0);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(( material.specularIntensity * specularFactor * directionalLight.colour),1.0f);
		}
	}

	outColor = color * (ambientColour + diffuseColor + specularColor);
};
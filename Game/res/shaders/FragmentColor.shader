
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
in vec3 Normal;
in vec3 FragPos;

struct DirectionLight
{
	vec3 colour;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 posLight;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform DirectionLight directionalLight;
uniform Material material;

uniform vec3 cameraPos;

out vec4 outColor;

void main()
{
	vec3 ambient = directionalLight.ambient * material.ambient;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(directionalLight.posLight - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = directionalLight.diffuse * (diff * material.diffuse);
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = directionalLight.specular * (spec * material.specular);
	
	vec3 result = (ambient + diffuse + specular);
	outColor = vec4(result, 1.0f);
};
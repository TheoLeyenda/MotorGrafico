
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec4 color;
in vec3 Normal;
in vec3 FragPos;

struct Light
{
	vec3 colour;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
	vec3 posLight;

	float cutOff;
	float outerCutOff;
	//Point values
	float constant;
	float linear;
	float quadratic;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	uniform sampler2D texture_diffuse1;
	uniform sampler2D texture_diffuse2;
	uniform sampler2D texture_diffuse3;
	uniform sampler2D texture_specular1;
	uniform sampler2D texture_specular2;
};

struct TypeLight
{
	int directional;
	int pointLight;
	int spotLight;
};

uniform TypeLight typelight;
uniform Light lightSource;
uniform Material material;

uniform vec3 cameraPos;

out vec4 outColor;

void main()
{
	vec3 lightDir = vec3(1.0);
	float distance;
	float attenuation;
	float theta;
	float epsilon;
	float intensity;
	vec3 ambient;
	vec3 norm;
	vec3 diffuse;
	vec3 viewDir;
	vec3 reflectDir;
	vec3 specular;
	float diff;
	float spec;

	if (typelight.directional == 1)
		lightDir = normalize(-lightSource.direction);
	else if (typelight.directional == 0)
		lightDir = normalize(lightSource.posLight - FragPos);

	theta = dot(lightDir, normalize(-lightSource.direction));
	epsilon = lightSource.cutOff - lightSource.outerCutOff;
	intensity = clamp((theta - lightSource.outerCutOff) / epsilon, 0.0, 1.0);

	if (typelight.directional == 1)
	{
		ambient = lightSource.ambient * material.ambient;
		norm = normalize(Normal);
		diff = max(dot(norm, lightDir), 0.0f);
		diffuse = lightSource.diffuse * (diff * material.diffuse);
		viewDir = normalize(cameraPos - FragPos);
		reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
		specular = lightSource.specular * (spec * material.specular);
	}
	if (theta > lightSource.cutOff)
	{
		if (typelight.spotLight == 1)
		{
			ambient = lightSource.ambient * material.ambient;
			norm = normalize(Normal);
			diff = max(dot(norm, lightDir), 0.0f);
			diffuse = lightSource.diffuse * (diff * material.diffuse);
			viewDir = normalize(cameraPos - FragPos);
			reflectDir = reflect(-lightDir, norm);
			spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
			specular = lightSource.specular * (spec * material.specular);

			diffuse *= intensity;
			specular *= intensity;

			distance = length(lightSource.posLight - FragPos);
			attenuation = 1.0 / (lightSource.constant + lightSource.linear * distance +
				lightSource.quadratic * (distance * distance));

			diffuse *= attenuation;
			specular *= attenuation;
		}
	}
	if (typelight.pointLight == 1)
	{
		ambient = lightSource.ambient * material.ambient;
		norm = normalize(Normal);
		diff = max(dot(norm, lightDir), 0.0f);
		diffuse = lightSource.diffuse * (diff * material.diffuse);
		viewDir = normalize(cameraPos - FragPos);
		reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
		specular = lightSource.specular * (spec * material.specular);

		distance = length(lightSource.posLight - FragPos);
		attenuation = 1.0 / (lightSource.constant + lightSource.linear * distance +
			lightSource.quadratic * (distance * distance));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}
	vec3 result = (ambient + diffuse + specular);
	outColor = vec4((result * texture(material.texture_diffuse1, texCoord)), 1.0f);
};
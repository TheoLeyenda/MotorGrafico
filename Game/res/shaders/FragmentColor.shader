
#version 330 core

in vec2 texCoord;
uniform sampler2D ourTexture;
uniform float isModel = 0; //1 = true, 0 = false.

uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_diffuse3;
//uniform sampler2D texture_specular1;
//uniform sampler2D texture_specular2;

in vec4 color;
in vec3 Normal;
in vec3 FragPos;

uniform int nr_of_directional_light;
uniform int nr_of_point_lights;
uniform int nr_of_spot_light;

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

vec3 lightDir = vec3(1.0);
float distance;
float attenuation;
float theta;
float epsilon;
float intensity;
float diff;
float spec;
vec3 ambient;
vec3 norm;
vec3 diffuse;
vec3 viewDir;
vec3 reflectDir;
vec3 specular;

vec3 CalcDirLight()
{
	lightDir = normalize(-lightSource.direction);

	theta = dot(lightDir, normalize(-lightSource.direction));
	epsilon = lightSource.cutOff - lightSource.outerCutOff;
	intensity = clamp((theta - lightSource.outerCutOff) / epsilon, 0.0, 1.0);

	ambient = lightSource.ambient * material.ambient;
	norm = normalize(Normal);
	diff = max(dot(norm, lightDir), 0.0);
	diffuse = lightSource.diffuse * (diff * material.diffuse);
	viewDir = normalize(cameraPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	specular = lightSource.specular * (spec * material.specular);


	return (ambient + diffuse + specular);

}

vec3 CalcPointLight()
{
	lightDir = normalize(lightSource.posLight - FragPos);

	theta = dot(lightDir, normalize(-lightSource.direction));
	epsilon = lightSource.cutOff - lightSource.outerCutOff;
	intensity = clamp((theta - lightSource.outerCutOff) / epsilon, 0.0, 1.0);

	ambient = lightSource.ambient * material.ambient;
	norm = normalize(Normal);
	diff = max(dot(norm, lightDir), 0.0);
	diffuse = lightSource.diffuse * (diff * material.diffuse);
	viewDir = normalize(cameraPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	specular = lightSource.specular * (spec * material.specular);

	distance = length(lightSource.posLight - FragPos);
	attenuation = 1.0 / (lightSource.constant + lightSource.linear * distance +
		lightSource.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight()
{
	lightDir = normalize(lightSource.posLight - FragPos);

	theta = dot(lightDir, normalize(-lightSource.direction));
	epsilon = lightSource.cutOff - lightSource.outerCutOff;
	intensity = clamp((theta - lightSource.outerCutOff) / epsilon, 0.0, 1.0);

	if (theta > lightSource.cutOff)
	{

		ambient = lightSource.ambient * material.ambient;
		norm = normalize(Normal);
		diff = max(dot(norm, lightDir), 0.0);
		diffuse = lightSource.diffuse * (diff * material.diffuse);
		viewDir = normalize(cameraPos - FragPos);
		reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = lightSource.specular * (spec * material.specular);

		diffuse *= intensity;
		specular *= intensity;

		distance = length(lightSource.posLight - FragPos);
		attenuation = 1.0 / (lightSource.constant + lightSource.linear * distance +
			lightSource.quadratic * (distance * distance));

		//ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}

	return (ambient + diffuse + specular);
}

void main()
{
	if (isModel == 0) 
	{
		vec3 outPutShader = vec3(0.0);

		for (int i = 0; i < nr_of_directional_light; i++)
		{
			outPutShader += CalcDirLight();
		}

		for (int i = 0; i < nr_of_point_lights; i++)
		{
			outPutShader += CalcPointLight();
		}

		for (int i = 0; i < nr_of_spot_light; i++)
		{
			outPutShader += CalcSpotLight();
		}

		vec4 result = (vec4(outPutShader, 1) + texture(ourTexture, texCoord));

		outColor = result;
	}
	else if (isModel == 1)
	{
		outColor = texture(texture_diffuse1, texCoord);
	}
}
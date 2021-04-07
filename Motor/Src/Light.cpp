#include "Light.h"

#include "glew.h"
#include "GLFW/glfw3.h"

Light::Light(Renderer * _render) : Entity(_render)
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(Renderer * _render, float _red, float _green, float _blue, float _ambientIntensity) : Entity(_render)
{
	colour = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;
}

void Light::UseLight(float ambientIntensityLocation, float ambientColourLocation)
{
	cout << "Color: " <<colour.x <<"," << colour.y << "," <<colour.z << ","<< endl;
	cout << "AmbientIntensity: "<< ambientIntensity << endl;

	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	//cout << ambientColourLocation << endl;
	//cout << ambientIntensityLocation <<endl;
}

void Light::SetAmbientIntensityShaderColor(Shader& shader)
{
	uniformAmbientIntensityShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.ambientIntensity");
}

void Light::SetAmbientColourShaderColor(Shader & shader)
{
	uniformAmbientColourShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.colour");
}

void Light::SetAmbientIntensityShaderTexture(Shader & shader)
{
	uniformAmbientIntensityShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.ambientIntensity");
}

void Light::SetAmbientColourShaderTexture(Shader & shader)
{
	uniformAmbientColourShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.colour");
}


Light::~Light() {}

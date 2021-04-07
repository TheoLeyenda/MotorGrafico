#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"

class ENGINE_API Light: public Entity 
{
public:
	Light(Renderer* _render);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity);

	void UseLight(float ambientIntensityLocation, float ambientColourLocation);

	unsigned int GetAmbientIntensityLocationShaderColor() { return uniformAmbientIntensityShaderColor; }
	unsigned int GetAmbientColorLocationShaderColor() { return uniformAmbientColourShaderColor; }

	void SetAmbientIntensityShaderColor(Shader& shader);
	void SetAmbientColourShaderColor(Shader& shader);

	unsigned int GetAmbientIntensityLocationShaderTexture() { return uniformAmbientIntensityShaderTexture; }
	unsigned int GetAmbientColorLocationShaderTexture() { return uniformAmbientColourShaderTexture; }

	void SetAmbientIntensityShaderTexture(Shader& shader);
	void SetAmbientColourShaderTexture(Shader& shader);

	~Light();
private:
	unsigned int uniformAmbientIntensityShaderColor;
	unsigned int uniformAmbientColourShaderColor;

	unsigned int uniformAmbientIntensityShaderTexture;
	unsigned int uniformAmbientColourShaderTexture;

	glm::vec3 colour;
	float ambientIntensity;

};

#endif
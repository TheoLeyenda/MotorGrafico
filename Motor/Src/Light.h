#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"

class ENGINE_API Light: public Entity 
{
public:
	Light(Renderer* _render);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity
	, float _xDir, float _yDir, float _zDir,float _diffuseIntensity);

	void UseLight(float ambientIntensityLocation, float ambientColourLocation,
		float diffuseIntensityLocation, float directionLocation);

	unsigned int GetAmbientIntensityLocationShaderColor() { return uniformAmbientIntensityShaderColor; }
	unsigned int GetAmbientColorLocationShaderColor() { return uniformAmbientColourShaderColor; }

	void SetAmbientIntensityShaderColor(Shader& shader);
	void SetAmbientColourShaderColor(Shader& shader);

	unsigned int GetAmbientIntensityLocationShaderTexture() { return uniformAmbientIntensityShaderTexture; }
	unsigned int GetAmbientColorLocationShaderTexture() { return uniformAmbientColourShaderTexture; }

	void SetAmbientIntensityShaderTexture(Shader& shader);
	void SetAmbientColourShaderTexture(Shader& shader);

	unsigned int GetDiffuseIntensityLocationShaderColor() { return uniformDiffuseIntensityShaderColor; }
	unsigned int GetDiffuseIntensityLocationShaderTexture() { return uniformDiffuseIntensityShaderTexture; }

	void SetDiffuseIntensityShaderColor(Shader& shader);
	void SetDiffuseIntensityShaderTexture(Shader& shader);

	unsigned int GetDirectionLocationShaderColor() { return uniformDirectionShaderColor; }
	unsigned int GetDirectionLocationShaderTexture() { return uniformDirectionShaderTexture; }

	void SetDirectionShaderColor(Shader& shader);
	void SetDirectionShaderTexture(Shader& shader);

	~Light();
private:
	unsigned int uniformAmbientIntensityShaderColor;
	unsigned int uniformAmbientColourShaderColor;

	unsigned int uniformAmbientIntensityShaderTexture;
	unsigned int uniformAmbientColourShaderTexture;

	unsigned int uniformDiffuseIntensityShaderColor;
	unsigned int uniformDiffuseIntensityShaderTexture;

	unsigned int uniformDirectionShaderColor;
	unsigned int uniformDirectionShaderTexture;

	glm::vec3 colour;
	float ambientIntensity;

	glm::vec3 direction;
	float diffuseIntensity;

};

#endif
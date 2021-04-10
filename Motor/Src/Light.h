#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"
#include "Material.h"

class ENGINE_API Light: public Entity 
{
public:
	Light(Renderer* _render);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity
	, float _xDir, float _yDir, float _zDir,float _diffuseIntensity);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity
		, float _xDir, float _yDir, float _zDir, float _diffuseIntensity,
		Material* newMaterial);

	void UseLight(float ambientIntensityLocation, float ambientColourLocation,
		float diffuseIntensityLocation, float directionLocation,Camera* cameraIn);

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

	unsigned int GetSpecularIntensityLocationShaderColor() { return uniformSpecularIntensityShaderColor; }
	unsigned int GetShininessLocationShaderColor() { return uniformShininessShaderColor; }
	unsigned int GetCameraPositionLocationShaderColor() { return uniformCameraPositionShaderColor; }

	void SetSpecularIntensityShaderColor(Shader& shader);
	void SetShininessShaderColor(Shader& shader);
	void SetCameraPositionShaderColor(Shader& shader);

	void SetColorLight(float r, float g, float b);
	void SetAmbientIntensity(float _ambientIntensity);
	
	void SetDirectionLight(float xDir, float yDir, float zDir);
	void SetDiffuseIntensity(float _diffuseIntensity);

	float GetAmbientIntensity() { return ambientIntensity; }
	float GetDiffuseIntensity() { return diffuseIntensity; }
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

	unsigned int uniformCameraPositionShaderColor;
	unsigned int uniformSpecularIntensityShaderColor; //Material Values
	unsigned int uniformShininessShaderColor;//Material Values

	glm::vec3 colour;
	float ambientIntensity;

	glm::vec3 direction;
	float diffuseIntensity;

	float materialSpecularInesity;
	float materialShininessInfluency;
};

#endif
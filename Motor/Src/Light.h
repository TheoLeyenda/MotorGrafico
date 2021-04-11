#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"
#include "Material.h"

const int lightIndicesCubeCount = 36;
const int lightCubeCount = 48;

class ENGINE_API Light : public Entity
{
public:
	Light(Renderer* _render);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity
		, float _xPos, float _yPos, float _zPos, float _diffuseIntensity);
	Light(Renderer* _render, float _red, float _green, float _blue, float _ambientIntensity
		, float _xPos, float _yPos, float _zPos, float _diffuseIntensity,
		Material* newMaterial);

	void UseLight(float ambientIntensityLocation, float ambientColourLocation,
		float diffuseIntensityLocation, float directionLocation, Camera* cameraIn);
	
	void Draw();

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

	unsigned int GetUniformLightPos() { return uniformLightPosition; }

	void SetUniformLightPos(Shader& shader);

	void SetColorLight(float r, float g, float b);
	void SetAmbientIntensity(float _ambientIntensity);

	void SetDirectionLight(float xDir, float yDir, float zDir);
	void SetDiffuseIntensity(float _diffuseIntensity);

	float GetAmbientIntensity() { return ambientIntensity; }
	float GetDiffuseIntensity() { return diffuseIntensity; }
	~Light();
protected:
	void SetVAO();
	void SetVBO();
	void SetIBO();
	void BindVAO();
	void BindIBO();
	void BindVBO();
	void UnbindIBO();
	void UnbindVAO();
	void UnbindBuffers();
	void CreateDataLight();
private:
	float lightSourceCube[lightCubeCount] = {
		//	x		y		z	
		  -1.0,   -1.0,    1.0,   1.0,   1.0,    1.0,
		   1.0,   -1.0,    1.0,   1.0,   1.0,    1.0,
		   1.0,    1.0,    1.0,   1.0,   1.0,    1.0,
		  -1.0,    1.0,    1.0,   1.0,   1.0,    1.0,
		  -1.0,   -1.0,   -1.0,   1.0,   1.0,    1.0,
		   1.0,   -1.0,   -1.0,   1.0,   1.0,    1.0,
		   1.0,    1.0,   -1.0,   1.0,   1.0,    1.0,
		  -1.0,    1.0,   -1.0,   1.0,   1.0,    1.0
	};
	unsigned int indexCubeLight[lightIndicesCubeCount] = {
	0, 1, 2,
	2, 3, 0,
	1, 5, 6,
	6, 2, 1,
	7, 6, 5,
	5, 4, 7,
	4, 0, 3,
	3, 7, 4,
	4, 5, 1,
	1, 0, 4,
	3, 2, 6,
	6, 7, 3
	};

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

	unsigned int uniformLightPosition;

	unsigned int _posAttribLight;
	unsigned int _colAttribLight;
	unsigned int _vboLight;
	unsigned int _iboLight;
	unsigned int _vaoLight;

	glm::vec3 colour;
	float ambientIntensity;

	//glm::vec3 direction;
	float diffuseIntensity;

	float materialSpecularInesity;
	float materialShininessInfluency;
};

#endif
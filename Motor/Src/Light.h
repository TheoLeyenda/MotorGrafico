#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"

const int lightIndicesCubeCount = 36;
const int lightCubeCount = 48;

class ENGINE_API Light : public Entity
{
public:
	enum TypeLight
	{
		Point,
		Directional,
		Spot,
		Pos
	};

	Light(Renderer* _render, TypeLight type);
	Light(glm::vec3 colour, glm::vec3 ambient, glm::vec3 diffuse
		, glm::vec3 specular, Renderer* render, TypeLight type);

	void UseLight(Camera* cameraIn);

	void Draw();

	void SetColorLight(float r, float g, float b);
	glm::vec3 GetColorLight();

	void SetTypeLight(TypeLight type);
	TypeLight GetTypeLight() { return _typeLight; }

	void SetUniformColourLocation(Shader& shader);
	unsigned int GetUniformColourLocation() { return _unifromColourLocation; }

	void SetUniformAmbientLocation(Shader& shader);
	unsigned int GetUniformAmbientLocation() { return _uniformAmbientLocation; }

	void SetUniformDiffuseLocation(Shader& shader);
	unsigned int GetUniformDiffuseLocation() { return _uniformDiffuseLocation; }

	void SetUniformSpecularLocation(Shader& shader);
	unsigned int GetUniformSpecularLocation() { return _uniformSpecularLocation; }

	void SetUniformPosLightLocation(Shader& shader);
	unsigned int GetUniformPosLightLocation() { return _uniformPosLightLocation; }

	void SetUniformPosCameraLocation(Shader& shader);
	unsigned int GetUniformPosCameraLocation() { return _uniformPosCameraLocation; }

	void SetUniformTypeLightDirectional(Shader& shader);
	unsigned int GetUniformTypeLightDirectional() { return _uniformTypeLightDirectional; }

	void SetUniformTypeLightSpot(Shader& shader);
	unsigned int GetUniformTypeLightSpot() { return _uniformTypeLightSpot; }

	void SetUniformTypeLightPoint(Shader& shader);
	unsigned int GetUniformTypeLightPoint() { return _uniformTypeLightPoint; }

	void SetUniformDirectionLightLocation(Shader& shader);
	unsigned int GetUniformDirectionalLight() { return _uniformDirectionLocation; }

	void SetUniformConstPointLight(Shader& shader);
	unsigned int GetUniformConstPointLight() { return _uniformConstPointLight; }

	void SetUniformLinearPointLight(Shader& shader);
	unsigned int GetUniformLinearPointLight() { return _uniformLinearPointLight; }

	void SetUniformQuadraticPointLight(Shader& shader);
	unsigned int GetUniformQuadraticPointLight() { return _uniformQuadraticPointLight; }

	void SetUniformCutOffSopttLight(Shader& shader);
	unsigned int GetUniformCutOffSopttLight() { return _uniformCutOffSpotLight; }

	void SetUniformOuterCutOffSopttLight(Shader& shader);
	unsigned int GetUniformOuterCutOffSopttLight() { return _uniformOuterCutOffSpotLight; }


	void SetColour(glm::vec3 colour) { _colour = colour; }
	void SetAmbient(glm::vec3 ambient) { _ambient = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { _diffuse = diffuse; }
	void SetSpecular(glm::vec3 specular) { _specular = specular; }
	void SetDirectionLight(glm::vec3 direction) { _direction = direction; }

	void SetPointLight(float linearVal, float quadraticVal);
	void SetLinearValue(float value) { _linearValue = value; }
	void SetQuadraticValue(float value) { _quadraticValue = value; }
	void SetCutOffSpotLight(float value) { _cutOffValue = value; }
	void SetOuterCutOffSpotLight(float value) { _outerCutOffValue = value; }

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

	unsigned int _posAttribLight;
	unsigned int _colAttribLight;
	unsigned int _vboLight;
	unsigned int _iboLight;
	unsigned int _vaoLight;

	unsigned int _unifromColourLocation;
	unsigned int _uniformAmbientLocation;
	unsigned int _uniformDiffuseLocation;
	unsigned int _uniformSpecularLocation;
	unsigned int _uniformPosLightLocation;
	unsigned int _uniformPosCameraLocation;
	unsigned int _uniformDirectionLocation;

	unsigned int _uniformTypeLightDirectional;
	unsigned int _uniformTypeLightPoint;
	unsigned int _uniformTypeLightSpot;

	unsigned int _uniformConstPointLight;
	unsigned int _uniformLinearPointLight;
	unsigned int _uniformQuadraticPointLight;

	unsigned int _uniformCutOffSpotLight;
	unsigned int _uniformOuterCutOffSpotLight;

	glm::vec3 _colour;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	glm::vec3 _direction;

	float _linearValue;
	float _quadraticValue;
	const float _constValue = 1.0f;
	float _cutOffValue;
	float _outerCutOffValue;

	TypeLight _typeLight;
	int _isDirectional;
	int _isPoint;
	int _isSpot;
};

#endif
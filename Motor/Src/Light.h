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
		Spot
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

	void SetColour(glm::vec3 colour) { _colour = colour; }
	void SetAmbient(glm::vec3 ambient) { _ambient = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { _diffuse = diffuse; }
	void SetSpecular(glm::vec3 specular) { _specular = specular; }

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

	glm::vec3 _colour;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;

	TypeLight _typeLight;
};

#endif
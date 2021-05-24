#ifndef LIGHT_H
#define LIGHT_H
#include "Entity.h"

const int lightIndicesCubeCount = 36;
const int lightCubeCount = 48;

class ENGINE_API Light : public Entity
{
public:

	static int nr_of_directional_light;
	static int nr_of_point_light;
	static int nr_of_spot_light;

	int my_Id;

	enum TypeLight
	{
		Point,
		Directional,
		Spot,
	};

	Light(Renderer* _render, TypeLight type);
	Light(glm::vec3 colour, glm::vec3 ambient, glm::vec3 diffuse
		, glm::vec3 specular, Renderer* render, TypeLight type);

	void UseLight(Camera* cameraIn);

	void Draw();

	void SetColorLight(float r, float g, float b);
	glm::vec3 GetColorLight();

	void SetTypeLightDefault(TypeLight type);
	void SetPointLightCustom(float linearVal, float quadraticVal, float cutOffValue);
	void SetSpotLightCustom(float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue);
	void SetDirectionalLightCustom(glm::vec3 direction);

	TypeLight GetTypeLight() { return _typeLight; }

	void SetIdLight(int id) { my_Id = id; }
	int GetMyId() { return my_Id; }

	//=====================================================
	//DIRECTIONAL LIGHT
	void SetUniformDirectionLightLocation(Shader& shader, int iter);
	unsigned int GetUniformDirectionalLight() { return _uniformDirectionLocation; }

	void SetUniformTypeLightDirectional(Shader& shader, int iter);
	unsigned int GetUniformTypeLightDirectional() { return _uniformTypeLightDirectional; }

	void SetUniformAmbDirectionalLoc(Shader& shader, int iter);
	unsigned int GetUniformAmbDirectionalLoc() { return _uniformAmbDirectionalLoc; }

	void SetUniformDiffDirectionalLoc(Shader& shader, int iter);
	unsigned int GetUniformDiffDirectionalLoc() { return _uniformDiffDirectionalLoc; }

	void SetUniformSpecDirectionalLoc(Shader& shader, int iter);
	unsigned int GetUniformSpecDirectionalLoc() { return _uniformSpecDirectionalLoc; }

	//=====================================================
	//POINT LIGHT
	void SetUniformAmbientPointLoc(Shader& shader, int iter);
	unsigned int GetUniformAmbPointLoc() { return _uniformAmbientPointLoc; }

	void SetUniformDiffPointLoc(Shader& shader, int iter);
	unsigned int GetUniformDiffPointLoc() { return _uniformDiffusePointLoc; }

	void SetUniformSpecPointLoc(Shader& shader, int iter);
	unsigned int GetUniformSpecPointLoc() { return _uniformSpecularPointLoc; }

	void SetUniformLinearPointLight(Shader& shader, int iter);
	unsigned int GetUniformLinearPointLight() { return _uniformLinearPointLight; }

	void SetUniformQuadraticPointLight(Shader& shader, int iter);
	unsigned int GetUniformQuadraticPointLight() { return _uniformQuadraticPointLight; }

	void SetUniformConstPointLight(Shader& shader, int iter);
	unsigned int GetUniformConstPointLight() { return _uniformConstPointLight; }

	void SetUniformTypeLightPoint(Shader& shader);
	unsigned int GetUniformTypeLightPoint() { return _uniformTypeLightPoint; }

	void SetUniformPosLightPoint(Shader& shader, int iter);
	unsigned int GetUniformPosLightPoint() { return _uniformPosLightPointLoc; }

	//=====================================================
	//SPOT LIGHT
	void SetUniformAmbientSpotLoc(Shader& shader, int iter);
	unsigned int GetUniformAmbSpotLoc() { return _uniformAmbientSpotLoc; }

	void SetUniformDiffSpotLoc(Shader& shader, int iter);
	unsigned int GetUniformDiffSpotLoc() { return _uniformDiffuseSpotLoc; }

	void SetUniformSpecSpotLoc(Shader& shader, int iter);
	unsigned int GetUniformSpecSpotLoc() { return _uniformSpecularSpotLoc; }

	void SetUniformTypeLightSpot(Shader& shader);
	unsigned int GetUniformTypeLightSpot() { return _uniformTypeLightSpot; }

	void SetUniformLinearSpotLight(Shader& shader, int iter);
	unsigned int GetUniformLinearSpotLight() { return _uniformLinearSpotLight; }

	void SetUniformQuadraticSpotLight(Shader& shader, int iter);
	unsigned int GetUniformQuadraticSpotLight() { return _uniformQuadraticSpotLight; }

	void SetUniformConstSpotLight(Shader& shader, int iter);
	unsigned int GetUniformConstSpotLight() { return _uniformConstSpotLight; }

	void SetUniformCutOffSopttLight(Shader& shader, int iter);
	unsigned int GetUniformCutOffSopttLight() { return _uniformCutOffSpotLight; }

	void SetUniformOuterCutOffSopttLight(Shader& shader, int iter);
	unsigned int GetUniformOuterCutOffSopttLight() { return _uniformOuterCutOffSpotLight; }

	void SetUniformPosLightSpot(Shader& shader, int iter);
	unsigned int GetUniformPosLightSpot() { return _uniformPosLightSpotLoc; }

	//=======================================================
	//CAMERA POS
	void SetUniformPosCameraLocation(Shader& shader);
	unsigned int GetUniformPosCameraLocation() { return _uniformPosCameraLocation; }

	
	//==============================
	void SetUniformPosLightLocation(Shader& shader);
	unsigned int GetUniformPosLightLocation() { return _uniformPosLightPointLoc; }

	void SetUniformColourLocation(Shader& shader);
	unsigned int GetUniformColourLocation() { return _unifromColourLocation; }
	
	
	void SetColour(glm::vec3 colour) { _colour = colour; }
	void SetAmbient(glm::vec3 ambient) { _ambientDirectional = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { _diffuseDirectional = diffuse; }
	void SetSpecular(glm::vec3 specular) { _specularDirectional = specular; }

	void SetTypeLightPoint(float linearVal, float quadraticVal, float cutOffValue);
	void SetTypeLightSpot(float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue);
	void SetTypeLightDirectional(glm::vec3 direction);

	void SetTypeLightPoint();
	void SetTypeLightSpot();
	void SetTypeLightDirectional();

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

	void SetBoolsTypeLight();

	void SetPointLight(float linearVal, float quadraticVal);
	void SetLinearValue(float value) { _linearValuePoint = value; }
	void SetQuadraticValue(float value) { _quadraticValuePoint = value; }
	void SetCutOffSpotLight(float value) { _cutOffValueSpot = value; }
	void SetOuterCutOffSpotLight(float value) { _outerCutOffValueSpot = value; }
	void SetDirectionLight(glm::vec3 direction) { _direction = direction; }

	void SetCountLightInShader(Shader shader);
	void UpdateCountLightInShader(Shader shader);

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

	//=========================================
	//Directional
	unsigned int _uniformDirectionLocation;
	unsigned int _uniformTypeLightDirectional;
	unsigned int _uniformAmbDirectionalLoc;
	unsigned int _uniformDiffDirectionalLoc;
	unsigned int _uniformSpecDirectionalLoc;
	//=========================================
	//Point
	unsigned int _uniformTypeLightPoint;
	unsigned int _uniformConstPointLight;
	unsigned int _uniformQuadraticPointLight;
	unsigned int _uniformLinearPointLight;
	unsigned int _uniformPosLightPointLoc;

	unsigned int _uniformAmbientPointLoc;
	unsigned int _uniformDiffusePointLoc;
	unsigned int _uniformSpecularPointLoc;
	//=========================================
	//Spot
	unsigned int _uniformTypeLightSpot;
	unsigned int _uniformOuterCutOffSpotLight;
	unsigned int _uniformCutOffSpotLight;
	unsigned int _uniformPosLightSpotLoc;
	unsigned int _uniformAmbientSpotLoc;
	unsigned int _uniformDiffuseSpotLoc;
	unsigned int _uniformSpecularSpotLoc;

	unsigned int _uniformQuadraticSpotLight;
	unsigned int _uniformLinearSpotLight;
	unsigned int _uniformConstSpotLight;

	//Camera pos
	unsigned int _uniformPosCameraLocation;

	//DIRECTIONAL
	glm::vec3 _ambientDirectional;
	glm::vec3 _diffuseDirectional;
	glm::vec3 _specularDirectional;
	glm::vec3 _direction;
	unsigned int nr_of_directional_lightLocation;

	//POINT
	glm::vec3 _ambientPoint;
	glm::vec3 _diffusePoint;
	glm::vec3 _specularPoint;
	float _linearValuePoint;
	float _quadraticValuePoint;
	const float _constValuePoint = 1.0f;
	unsigned int nr_of_point_lightsLocation;

	//SPOT
	glm::vec3 _ambientSpot;
	glm::vec3 _diffuseSpot;
	glm::vec3 _specularSpot;
	float _linearValueSpot;
	float _quadraticValueSpot;
	const float _constValueSpot = 1.0f;
	float _cutOffValueSpot;
	float _outerCutOffValueSpot;

	unsigned int nr_of_spot_lightLocation;

	//OTHERS
	glm::vec3 _colour;
	TypeLight _typeLight;
	int _isDirectional;
	int _isPoint;
	int _isSpot;
};

#endif
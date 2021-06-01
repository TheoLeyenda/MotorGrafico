/*
#include "glm.h"
#include "Renderer.h"
Entity:

struct Trasform:
vector4 posicion
vector4 rotacion
vector4 escala

protected:
Renderer* renderer.
public:
Trasform trasform;
Renderer* GetRenderer();

-Metodo para mover el objeto (calcule su posicion) - retorna el resultado
-Metodo para rotar el objeto (calcule su rotacion) - retorna el resultado
-Metodo para escalar el objeto (calcule su escala) - retorna el resultado

-Funcion que calcula la trasformacion del objeto (trasform) - multiplica posicion * rotacion * escala.
*/

#ifndef ENTITY_H
#define ENTITY_H

#include "../Lib/glm/vec4.hpp"
#include "../Lib/glm/vec3.hpp"
#include "../Lib/glm/vec2.hpp"
#include "../Lib/glm/mat4x4.hpp"
#include "../Lib/glm/ext/matrix_transform.hpp"
#include "../Lib/glm/ext/matrix_clip_space.hpp"
#include "../Lib/glm/ext/scalar_constants.hpp"
#include "PrivateClass/Export.h"

#include "MyMathLibrary.h"

#include "Renderer.h"

#include "stb_image.h"

#define ENTITY_2DIMENTIONS 1
#define ENTITY_3DIMENTIONS 2
//using namespace glm;

struct ENGINE_API Transform
{
	glm::vec3 forward;
	glm::vec3 backward;
	glm::vec3 left;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 down;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
struct ENGINE_API InternalData
{
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;
};
class ENGINE_API Entity
{
protected:
	Renderer* renderer;
	InternalData internalData;
	void UpdateMatrixModel();
	MyMathLibrary myMathLibrary;
	float isModel;

	unsigned int _uniformIsModelLocation;
	string nameEntity;
	bool showInDebug = false;

	unsigned int _ibo;
	unsigned int _vbo;
	unsigned int _vao;
	unsigned int _uniformModelLocation;
	unsigned int _uniformViewLocation;
	unsigned int _uniformProjectionLocation;
	unsigned int _positionLocation;
	unsigned int _texLocation;
	unsigned int _colorLocation;
	unsigned int _normalLocation;

	virtual void BindBuffer() = 0;

	bool isAlive = true;
	bool InmortalObject = false;

public:
	virtual void Draw(bool& wireFrameActive) = 0;

	void SetShowInDebug(float value) { showInDebug = value; }
	bool GetShowInDebug() { return showInDebug; }
	Entity(Renderer *_renderer);
	Entity(Renderer *_renderer, float _isModel);
	~Entity();
	Transform transform;
	Renderer* GetRenderer();
	InternalData GetInternalData();
	void SetPosition(float x, float y, float z);
	virtual void SetScale(float x, float y, float z);
	void SetName(string name);
	string GetName();
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void InitIsModelShader();
	void CheckIsModel();
	bool GetIsAlive() { return isAlive; }
	void SetIsAlive(bool value) { isAlive = value; }
	bool GetIsInmortal() { return InmortalObject; }
};
#endif
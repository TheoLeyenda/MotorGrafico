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

#include "MathLibrary.h"

#include "Renderer.h"

//#include "AxisAlignedBoundingBox.h"
class AxisAlignedBoundingBox;
class Plane_BSP;

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

	glm::vec3 globalPosition;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
struct ENGINE_API InternalData
{
	glm::mat4 originModel;
	glm::mat4 localModel;
	glm::mat4 globalModel;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;
};
class ENGINE_API Entity
{
private:
	//JERARQUIA//
	void _GetEntityNode(string nameID, vector<Entity*>& res);
	void _AddChildren(Entity* children, Entity* newParent);
	//---------//
protected:
	
	void CreateMyAxisAlignedBoundingBox();
	Entity* rootScene;
	//FRUSTRUM CULLING
	AxisAlignedBoundingBox* axisAlignedBoundingBox = NULL;
	//---------------//

	//JERARQUIA//
	Entity* parent = NULL;
	vector<Entity*> childrens;
	//-----------//

	Renderer* renderer;
	InternalData internalData;
	MathLibrary mathLibrary;
	float isModel;

	unsigned int _uniformIsModelLocation;
	string nameEntity;

	//UI//
	bool isUILocked = false;
	bool showInDebug = false;
	//---//

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
	bool isStatic = false;
	bool isAlive = true;
	//bool InmortalObject = false;
	bool isRootHerarchy = false;
public:
	void UpdateMatrixModel();
	virtual void Draw(bool& wireFrameActive) = 0;
	virtual void SetEnableDrawAABB(bool value) = 0;

	Entity(Renderer *_renderer);
	Entity(Renderer *_renderer, float _isModel);
	~Entity();
	Transform transform;
	Renderer* GetRenderer();

	InternalData GetInternalData();
	AxisAlignedBoundingBox* GetAABB() { return axisAlignedBoundingBox; }
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetScale(float x, float y, float z);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetRotationX(float x);
	virtual void SetRotationY(float y);
	virtual void SetRotationZ(float z);
	void SetName(string name);
	string GetName();
	void InitIsModelShader();
	void CheckIsModel();
	bool GetIsAlive() { return isAlive; }
	void DisableMeAndChilds();
	void AttachRootScene(Entity* value);
	virtual void SetIsAlive(bool value) 
	{
		SetEnableDrawAABB(value);
		isAlive = value;
	}

	void SetIsStatic(bool value) 
	{
		isStatic = value;
	}

	bool GetIsStatic() { return isStatic; }
	//bool GetIsInmortal() { return InmortalObject; }

	virtual string GetClassName() 
	{
		return "Entity"; // Aplicar override en todas las clases hijo.
	}

	//UI//
	void ShowUI();
	void SetShowInDebug(float value) { showInDebug = value; }
	bool GetShowInDebug() { return showInDebug; }
	void SetIsUILocked(float value) { isUILocked = value; }
	bool GetIsUILocked() { return isUILocked; }
	//------//

	// JERARQUIA // 
	Entity* GetParent() { return parent; }
	void AddChildren(Entity* children);
	void RemoveChildren(Entity* children, Entity* newParent);
	Entity* GetEntityNode(string name);
	Entity* GetChild(int childIndex) const;
	
	void PrintTree();

	//void OffMeAndChildrensObjects();

	vector<Entity*> GetChildrens() { return childrens; }
	//-----------//

	glm::vec3* GetAABBGlobalPositions();

	glm::vec3 GetForward();
	
	void SetIsRootHerarchy(bool value) { isRootHerarchy = value; }
	bool GetIsRootHerarchy() { return isRootHerarchy; }

	void CheckVisibleBSP(vector<Entity*> objectsBSP, vector<int>& indexsObjectsVisibility, vector<Plane_BSP*>& planesBSP);
};
#endif
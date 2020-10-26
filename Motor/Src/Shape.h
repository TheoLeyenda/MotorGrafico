#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"

#include "Entity2D.h"
#include "../Lib/glm/vec4.hpp"

static enum TypeShape 
{
	TRIANGLE = 0x0004,
	QUAD = 0x0007,
};
static enum TypeColorShape 
{
	SolidColor,
	VertexColor,
};
static enum TypeMaterial 
{
	Texture = 1,
	Color = 2,
};
//typedef unsigned int GLenum;
class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
	unsigned int _vbo;
	unsigned int _currentShape;
	TypeColorShape _typeColorShape;
	TypeMaterial _typeMaterial;
public:

	Shape(Renderer *_renderer, TypeMaterial typeMaterial);
	Shape(Renderer *_renderer, Material* _material, TypeMaterial typeMaterial);
	~Shape();
	void SetShape(unsigned int typeShape, TypeColorShape typeColorShape);
	void CreateVbo(float* vertexBuffer);
	unsigned int GetVbo();
	float* GetVertexBuffer();
	void SetVertexMaterial(glm::vec4 material,float* VBA, int start,int offset, int repeticiones);
	void SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe);
	void Draw(unsigned int figura, int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model);
	void SetSolidColor(float r, float g, float b);
	void SetTypeColorShape(TypeColorShape typeColorShape) { _typeColorShape = typeColorShape; }
	TypeColorShape GetTypeColorShape() { return _typeColorShape; }
};
#endif
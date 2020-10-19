#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"

#include "Entity2D.h"
#include "../Lib/glm/vec4.hpp"

static enum TypeShape 
{
	TRIANGLE = 0x0004,
	TRIANGLE_STRIP = 0x0005,
};
//typedef unsigned int GLenum;
class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
	unsigned int* _indexBuffer;
	int _countIndices;
	unsigned int _vbo;
	unsigned int _ibo;
	unsigned int _currentShape;
	unsigned int _posAttrib;
	unsigned int _colorAttrib;
public:

	Shape(Renderer *_renderer);
	Shape(Renderer *_renderer, Material* _material);
	~Shape();
	void InitShape(unsigned int typeShape);
	void CreateVbo(float* vertexBuffer);
	void CreateIbo(unsigned int* indeicesunsigned, int tamIndices);
	unsigned int GetVbo();
	unsigned int GetIbo();
	float* GetVertexBuffer();
	void SetVertexsAttrib(unsigned int& shaderId);
	unsigned int GetPosAttrib();
	unsigned int GetColAttrib();
	void SetVertexMaterial(glm::vec4 material,float* VBA, int start,int offset, int repeticiones);
	void SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe);
	void Draw(unsigned int figura, int indices, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model);
	void SetSolidColor(float r, float g, float b, float a);
};
#endif
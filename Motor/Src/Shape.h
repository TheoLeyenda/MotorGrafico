#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"

#include "Entity2D.h"
#include "../Lib/glm/vec4.hpp"


class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
public:
	Shape(Renderer *_renderer);
	Shape(Renderer *_renderer, Material* _material);
	~Shape();
	void InitShape(GLenum typeShape);
	void CreateVbo(float* vertexBuffer);
	void DrawShape(GLenum typeShape);
	float* GetVertexBuffer();
	void SetVertexMaterial(glm::vec4 material,float* VBA, int start,int offset, int repeticiones);
	void SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe);
};
#endif
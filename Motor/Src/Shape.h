#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"
#include "Entity2D.h"

class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
public:
	Shape(Renderer *_renderer);
	Shape(Renderer *_renderer, Material* _material);
	~Shape();
	void DrawShape(GLenum typeShape);
	float* GetVertexBuffer();
};
#endif
#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"
#include "Entity2D.h"
class ENGINE_API Shape : public Entity2D
{
public:
	Shape(Renderer *_renderer);
	Shape(Renderer *_renderer, Material* _material);
	~Shape();
};
#endif



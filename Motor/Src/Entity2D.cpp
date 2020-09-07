#include "Entity2D.h"

Entity2D::Entity2D(Renderer * _renderer, Material* _material): Entity(_renderer)
{
	renderer = _renderer;
	material = _material;
}

Entity2D::Entity2D(Renderer * _renderer) : Entity(_renderer)
{
	material = new Material();
}

Entity2D::~Entity2D()
{
	if (material != NULL)
	{
		delete material;
	}
}

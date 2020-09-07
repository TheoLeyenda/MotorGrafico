#include "Shape.h"

Shape::Shape(Renderer *_renderer): Entity2D(_renderer)
{
	renderer = _renderer;
}

Shape::Shape(Renderer * _renderer, Material * _material) : Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
}

Shape::~Shape(){}

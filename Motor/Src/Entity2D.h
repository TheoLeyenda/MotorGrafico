#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "Entity.h"
#include "Material.h"
#include "Renderer.h"
class ENGINE_API Entity2D : public Entity
{
public:
	Entity2D(Renderer *_renderer, Material* _material);
	Entity2D(Renderer *_renderer);
	~Entity2D();
	Material* material;
};
#endif


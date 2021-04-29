#ifndef VERTEX_H
#define VERTEX_H

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

struct VertexData
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Vertex
{
public:
	Vertex();
	~Vertex();
	VertexData data;
};
#endif // !VERTEX_H
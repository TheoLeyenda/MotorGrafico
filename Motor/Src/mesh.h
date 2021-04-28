#ifndef MESH_H
#define MESH_H

#include "PrivateClass/Export.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <string.h>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "GLEW/Include/glew.h"

using namespace std;

struct ENGINE_API Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoords;
};
struct ENGINE_API Texture
{
	unsigned int id;
	string type;
};

class ENGINE_API Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

	void setupMesh();
public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
		vector<Texture> textures);
	~Mesh();

};
#endif // !MESH_H
#ifndef MESH_H
#define MESH_H

#include "PrivateClass/Export.h"
#include "shader.h"
#include <iostream>
#include <string>
#include <vector>
#include "Texture.h"
#include "Vertex.h"

/*
struct ENGINE_API Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct ENGINE_API Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};
*/

class ENGINE_API Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

	void setupMesh();
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<Texture> textures);
	void Draw(Shader& shader);
};
#endif // !MESH_H
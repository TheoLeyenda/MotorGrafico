#ifndef MESH_H
#define MESH_H

#include "Entity.h"
#include <string>
#include <vector>

class Material;

struct ENGINE_API Vertex
{
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	//glm::vec3 Tangent;
	// bitangent
	//glm::vec3 Bitangent;
};

struct ENGINE_API Texture {
	unsigned int id;
	string type;
	string path;
};

class ENGINE_API Mesh : public Entity 
{
public:
	// mesh data
	vector<Vertex>       vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;


	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Renderer* render);
	void Draw(Shader &shader);

	void SetNewMaterial(Material* mat);
	void UseMyMaterial();

private:
	//  render data
	unsigned int VAO, VBO, EBO;
	Material* my_Mat;

	unsigned int _normAttrib;
	unsigned int _textureAttrib;
	unsigned int _tangentAttrib;
	unsigned int _bitangentAttrib;
	unsigned int _posAttrib;
	void SetupMesh();
	void BindMesh();

};

#endif

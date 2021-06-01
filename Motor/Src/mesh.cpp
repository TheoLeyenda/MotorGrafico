#include "Mesh.h"
#include "Material.h"
#include <glew.h>
#include <GLFW/glfw3.h>


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Renderer* render): Entity(render, 1)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	my_Mat = NULL;
	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
	CheckIsModel();

	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		string resultName = (name + number);
		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.id, resultName.c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	BindMesh();

	UseMyMaterial();

	//renderer->DrawMeshes(indices, shader, internalData.model, VBO, EBO, _posAttrib, _normAttrib, _textureAttrib);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::BindBuffer() {}

void Mesh::Draw(bool & wireFrameActive) {}

void Mesh::UseMyMaterial()
{
	if (my_Mat != NULL)
		my_Mat->UseMaterial(renderer->GetCurrentShaderUse());
}

void Mesh::SetNewMaterial(Material* mat)
{
	my_Mat = mat;

	renderer->SetMaterial(my_Mat);
}

void Mesh::BindMesh()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(_normAttrib);
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(_textureAttrib);
}

void Mesh::SetupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	_posAttrib = glGetAttribLocation(renderer->GetCurrentShaderUse().getId(), "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(_posAttrib);

	// vertex normals
	_normAttrib = glGetAttribLocation(renderer->GetCurrentShaderUse().getId(), "norm");
	glVertexAttribPointer(_normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(_normAttrib);

	// vertex texture coords
	_textureAttrib = glGetAttribLocation(renderer->GetCurrentShaderUse().getId(), "m_TexCoord");
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(_textureAttrib);

	// vertex tangent
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

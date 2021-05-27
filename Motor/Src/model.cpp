#include "Model.h"
#include "Material.h"
#include "Timer.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

Model::Model(string const & path,string const& _directory, bool gamma, Renderer * render): Entity(render, 1)
{
	stbi_set_flip_vertically_on_load(true);
	gammaCorrection = gamma;
	directory = _directory;
	LoadModel(path);
	my_Mat = NULL;
}

void Model::Draw(Shader & shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::CenterPivotPositionModel()
{
	float posX = 0;
	float posY = 0;
	float posZ = 0;
	float auxSumX = 0;
	float auxSumY = 0;
	float auxSumZ = 0;

	for (int i = 0; i < meshes.size(); i++)
	{
		auxSumX += meshes[i].transform.position.x;
		auxSumY += meshes[i].transform.position.y;
		auxSumZ += meshes[i].transform.position.z;
	}

	posX = auxSumX / meshes.size();
	posY = auxSumY / meshes.size();	//PROMEDIO DE CENTRO
	posZ = auxSumZ / meshes.size();

	SetPosition(posX, posY, posZ);
}

void Model::MoveModel(glm::vec3 direction, float speed, Time* timer)
{
	glm::vec3 newPosition = transform.position + (direction * speed * timer->deltaTime());

	for (int i = 0; i < meshes.size(); i++) 
	{
		meshes[i].transform.position = meshes[i].transform.position + (direction * speed * timer->deltaTime());
		meshes[i].SetPosition(meshes[i].transform.position.x, meshes[i].transform.position.y, meshes[i].transform.position.z);
	}

	CenterPivotPositionModel();

}

void Model::MoveModel(glm::vec3 direction, float speed, Time timer)
{
	glm::vec3 newPosition = transform.position + (direction * speed * timer.deltaTime());

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].transform.position = meshes[i].transform.position + (direction * speed * timer.deltaTime());
		meshes[i].SetPosition(meshes[i].transform.position.x, meshes[i].transform.position.y, meshes[i].transform.position.z);
	}

	CenterPivotPositionModel();
}

void Model::SetScaleModel(float x, float y, float z)
{
	SetScale(x, y, z);

	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].SetScale(x,y,z);
	}
}

void Model::SetRotationModelX(float RotateX)
{
	SetRotationX(RotateX);

	for (int i = 0; i < meshes.size(); i++) 
	{
		meshes[i].SetRotationX(RotateX);
	}
}

void Model::SetRotationModelY(float RotateY)
{
	SetRotationY(RotateY);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].SetRotationY(RotateY);
	}
}

void Model::SetRotationModelZ(float RotateZ)
{
	SetRotationZ(RotateZ);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].SetRotationZ(RotateZ);
	}
}

void Model::SetNewMaterial(Material * mat)
{
	my_Mat = mat;

	for (unsigned int i = 0; i < meshes.size(); i++) 
	{
		meshes[i].SetNewMaterial(my_Mat);
	}
}

unsigned int Model::TextureFromFile(const char * path, const string & directory, bool gamma, string num)
{
	string filename = directory + '/' + num + ".png";

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	//unsigned char *data = stbi_load("res/modelos/Alfator/textures/alfa.png", &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Model::LoadModel(string path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals /*| aiProcess_FlipUVs */ | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
			// tangent
			/*
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
			*/
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, renderer);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			int a = i;
			stringstream ss;
			ss << a;
			string index = ss.str();
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory, false, index);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

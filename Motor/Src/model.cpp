#include "Model.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(Renderer * render) : Entity(render)
{
	myMat = NULL;
}

Model::~Model()
{
	if (!myMat)
		delete myMat;
	UnloadModel();
}

void Model::LoadModel(const string & filePath, const string& texturePath)
{
	Assimp::Importer imporeter;
	const aiScene* scene = imporeter.ReadFile(filePath,
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		cout << "ERROR IMPORTER: Model failed to load, Location:" << filePath << " " << imporeter.GetErrorString() << endl;
		return;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterial(scene, texturePath);
}

void Model::Draw(bool & wireFrameActive)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textureList.size() && textureList[materialIndex])
			textureList[materialIndex]->BindTexture();

		if (myMat != NULL)
			myMat->UseMaterial(renderer->GetCurrentShaderUse());

		meshList[i]->Draw(wireFrameActive);

		if (materialIndex < textureList.size() && textureList[materialIndex])
			textureList[materialIndex]->UnbindTexture();
	}
}

void Model::UnloadModel()
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}

void Model::SetMaterial(Material * mat)
{
	myMat = mat;

	renderer->SetMaterial(myMat);
}

void Model::SetScale(float x, float y, float z)
{
	Entity::SetScale(x, y, z);
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetScale(x, y, z);
	}
}

void Model::SetScale(glm::vec3 scale)
{
	Entity::SetScale(scale.x, scale.y, scale.z);
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetScale(scale.x, scale.y, scale.z);
	}
}

void Model::SetPosition(float x, float y, float z)
{
	Entity::SetPosition(x, y, z);
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetPosition(x, y, z);
	}
}

void Model::SetPosition(glm::vec3 position)
{
	Entity::SetPosition(position.x, position.y, position.z);
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetPosition(position.x, position.y, position.z);
	}
}

void Model::SetRotationX(float x)
{
	Entity::SetRotationX(x);

	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetRotationX(x);
	}
}

void Model::SetRotationY(float y)
{
	Entity::SetRotationY(y);

	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetRotationY(y);
	}
}

void Model::SetRotationZ(float z)
{
	Entity::SetRotationZ(z);

	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetRotationZ(z);
	}
}

void Model::SetIsAlive(bool value)
{
	Entity::SetIsAlive(value);

	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->SetIsAlive(value);
	}
}

void Model::BindBuffer(){}

void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<float> vertices;
	vector<unsigned int> indices;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f,  0.0f });
		}
		vertices.insert(vertices.end(), { mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z });
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh(renderer);
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadTextureFromFile(aiTextureType type)
{

}

void Model::LoadMaterial(const aiScene * scene, const string& texturePath)
{
	textureList.resize(scene->mNumMaterials);

	for (int i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int index = string(path.data).rfind("\\");
				string fileName = string(path.data).substr(index + 1);

				string texPath = texturePath + fileName;

				cout << "Texture name:" << texPath << endl;

				textureList[i] = new Texture(texPath.c_str(), false);

				if (!textureList[i]->LoadTexture(false))
				{
					cout << "Failed to load texture! " << texPath << endl;
					delete textureList[i];
					textureList[i] = nullptr;
				}
			}
		}

		if (!textureList[i]) {
			textureList[i] = new Texture("res/textures/plain.png", false);
			textureList[i]->LoadTexture(false);
		}
	}
}

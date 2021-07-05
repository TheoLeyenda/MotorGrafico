#include "ModelImporter.h"

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

#include "ModelNode.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelImporter::ModelImporter() { indexChildrenLoad = 0; }

ModelImporter::~ModelImporter() {}

ModelNode* ModelImporter::LoadModel(const string& filePath, const string& texturePath, ModelNode* rootNode, vector<ModelNode*> &childrens, vector<Texture*> &textureList,Renderer* render)
{
	Assimp::Importer imporeter;
	const aiScene* scene = imporeter.ReadFile(filePath,
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		cout << "ERROR IMPORTER: Model failed to load, Location:" << filePath << " " << imporeter.GetErrorString() << endl;
		return NULL;
	}

	rootNode = new ModelNode(render, scene->mRootNode);
	auxiliarNodes.push(rootNode);
	LoadNode(scene->mRootNode, scene, childrens, render);

	LoadMaterial(scene, texturePath, textureList);

	return rootNode;
}
void ModelImporter::LoadNode(aiNode* node, const aiScene* scene, vector<ModelNode*> &childrens, Renderer* render)
{
	if (!auxiliarNodes.empty())
	{
		for (int j = 0; j < node->mNumMeshes; j++)
		{
			LoadMesh(scene->mMeshes[node->mMeshes[j]], scene, auxiliarNodes.top() ,render);
		}
	}

	int i = 0;

	for (i = 0; i < node->mNumChildren; i++)
	{
		ModelNode* n = new ModelNode(render, node->mChildren[i]);

		childrens.push_back(n);

		if (auxiliarNodes.size() > 0) {
			if(!auxiliarNodes.top()->allchildrensDone)
				auxiliarNodes.top()->AddChildren(n);

			if (i >= node->mNumChildren - 1) 
			{
				auxiliarNodes.top()->allchildrensDone = true;
			}
		}

		if (node->mChildren[i]->mNumChildren > 0) {
			auxiliarNodes.push(n);
		}
		LoadNode(node->mChildren[i], scene, childrens, render);
	}

	while (node != scene->mRootNode && !auxiliarNodes.empty() && auxiliarNodes.top()->allchildrensDone) {
		auxiliarNodes.pop();
	}
}

void ModelImporter::LoadMaterial(const aiScene * scene, const string& texturePath, vector<Texture*> &textureList)
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
void ModelImporter::LoadMesh(aiMesh* mesh, const aiScene* scene, ModelNode* &nodeMesh, Renderer* render)
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

	Mesh* newMesh = new Mesh(render);
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	nodeMesh->_meshList.push_back(newMesh);
	nodeMesh->_meshToTex.push_back(mesh->mMaterialIndex);
}
void ModelImporter::LoadTextureFromFile(aiTextureType type)
{
}
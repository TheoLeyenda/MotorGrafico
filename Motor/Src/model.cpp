#include "Model.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "ModelImporter.h"

#include "ModelNode.h"

Model::Model(Renderer * render) : Entity(render)
{
	myMat = NULL;
	rootNode = NULL;
	modelImporter = new ModelImporter();
}

Model::~Model()
{
	if (modelImporter != NULL)
		delete modelImporter;

	if (!myMat)
		delete myMat;

	UnloadModel();
}

void Model::LoadModel(const string & filePath, const string & texturePath)
{
	if (modelImporter != NULL) 
	{
		rootNode = modelImporter->LoadModel(filePath, texturePath, rootNode ,modelChildrens, textureList ,renderer);
	}

	if (rootNode != NULL) {
		AddChildren(rootNode);
		rootNode->_textureList = textureList;
	}
	
	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if(modelChildrens[i] != NULL)
			modelChildrens[i]->_textureList = textureList;
	}
}

void Model::Draw(bool & wireFrameActive)
{
	if (rootNode != NULL)
		rootNode->Draw(wireFrameActive);

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->Draw(wireFrameActive);
	}
	/*for (int i = 0; i < meshList.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textureList.size() && textureList[materialIndex])
			textureList[materialIndex]->BindTexture();

		if (myMat != NULL)
			myMat->UseMaterial(renderer->GetCurrentShaderUse());

		meshList[i]->Draw(wireFrameActive);

		if (materialIndex < textureList.size() && textureList[materialIndex])
			textureList[materialIndex]->UnbindTexture();
	}*/
}

void Model::UnloadModel()
{
	if (rootNode != NULL)
	{
		delete rootNode;
		rootNode = NULL;
	}

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL) 
		{
			delete modelChildrens[i];
			modelChildrens[i] = NULL;
		}
	}
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i] != NULL)
		{
			delete textureList[i];
			textureList[i] = NULL;
		}
	}
}

string Model::GetClassName()
{
	return "Model";
}

void Model::SetMaterial(Material * mat)
{
	myMat = mat;

	if (rootNode != NULL)
		rootNode->SetMaterialNode(myMat);

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->SetMaterialNode(myMat);
	}
}

void Model::SetScale(float x, float y, float z)
{
	Entity::SetScale(x, y, z);
	if(rootNode != NULL)
		rootNode->SetScale(x, y, z);
}

void Model::SetScale(glm::vec3 scale)
{
	Entity::SetScale(scale);
	if (rootNode != NULL)
		rootNode->SetScale(scale);
}

void Model::SetPosition(float x, float y, float z)
{
	Entity::SetPosition(x,y,z);
	if (rootNode != NULL)
		rootNode->SetPosition(x,y,z);
}

void Model::SetPosition(glm::vec3 position)
{
	Entity::SetPosition(position);
	if (rootNode != NULL)
		rootNode->SetPosition(position);
}

void Model::SetRotationX(float x)
{
	Entity::SetRotationX(x);
	if (rootNode != NULL)
		rootNode->SetRotationX(x);
}

void Model::SetRotationY(float y)
{
	Entity::SetRotationY(y);
	if (rootNode != NULL)
		rootNode->SetRotationY(y);
}

void Model::SetRotationZ(float z)
{
	Entity::SetRotationZ(z);
	if (rootNode != NULL)
		rootNode->SetRotationZ(z);
}

void Model::SetIsAlive(bool value)
{
	Entity::SetIsAlive(value);
	if (rootNode != NULL)
		rootNode->SetIsAlive(value);
}

void Model::BindBuffer(){}

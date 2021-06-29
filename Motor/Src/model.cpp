#include "Model.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "ModelImporter.h"

Model::Model(Renderer * render) : Entity(render)
{
	myMat = NULL;
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
		modelImporter->LoadModel(filePath, texturePath, textureList, meshList, meshToTex, renderer);
	}
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

#include "ModelNode.h"

#include "ModelImporter.h"
#include "mesh.h"
#include "Texture.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelNode::ModelNode(Renderer* render, aiNode* node) : Entity(render)
{
	_myNode = node;
	SetName(_myNode->mName.C_Str());
	allchildrensDone = false;
}

ModelNode::~ModelNode()
{
	for (int i = 0; i < _meshList.size(); i++)
	{
		if (_meshList[i] != NULL)
		{
			delete _meshList[i];
			_meshList[i] = NULL;
		}
	}
}

string ModelNode::GetNodeName()
{
	return _myNode->mName.C_Str();
}

aiNode* ModelNode::GetNode()
{
	return _myNode;
}

void ModelNode::PrintMyInfo()
{
	cout << "My Name is: " << GetName() << endl;
	cout << "cout meshes: " << _meshList.size() << endl;
	cout << "cout meshToTex: " << _meshToTex.size() << endl;
}

void ModelNode::BindBuffer()
{
}

void ModelNode::Draw(bool& wireFrameActive)
{
	for (int i = 0; i < _meshList.size(); i++)
	{
		unsigned int materialIndex = _meshToTex[i];

		if (materialIndex < _textureList.size() && _textureList[materialIndex])
			_textureList[materialIndex]->BindTexture();

		if (myMat != NULL)
			myMat->UseMaterial(renderer->GetCurrentShaderUse());

		_meshList[i]->Draw(wireFrameActive);

		if (materialIndex < _textureList.size() && _textureList[materialIndex])
			_textureList[materialIndex]->UnbindTexture();
	}
}

void ModelNode::SetMaterialNode(Material * mat)
{
	myMat = mat;
	renderer->SetMaterial(myMat);
}

void ModelNode::SetTexturesList(vector<Texture*> &textureList)
{
	_textureList = textureList;
}

void ModelNode::SetScale(float x, float y, float z)
{
	Entity::SetScale(x, y ,z);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetScale(x, y, z);
	}
}

void ModelNode::SetScale(glm::vec3 scale)
{
	Entity::SetScale(scale);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetScale(scale);
	}
}

void ModelNode::SetPosition(float x, float y, float z)
{
	Entity::SetPosition(x, y, z);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetPosition(x, y, z);
	}
}

void ModelNode::SetPosition(glm::vec3 position)
{
	Entity::SetPosition(position.x, position.y, position.z);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetPosition(position.x, position.y, position.z);
	}
}

void ModelNode::SetRotationX(float x)
{
	Entity::SetRotationX(x);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetRotationX(x);
	}
}

void ModelNode::SetRotationY(float y)
{
	Entity::SetRotationY(y);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetRotationY(y);
	}
}

void ModelNode::SetRotationZ(float z)
{
	Entity::SetRotationZ(z);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetRotationZ(z);
	}
}

void ModelNode::SetIsAlive(bool value)
{
	Entity::SetIsAlive(value);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetIsAlive(value);
	}
}
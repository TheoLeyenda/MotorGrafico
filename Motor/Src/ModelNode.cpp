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

void ModelNode::PrintMyInfo()
{
	cout << "My Name is: " << GetName() << endl;
	//cout << "cout meshes: " << _meshList.size() << endl;
	//cout << "cout meshToTex: " << _meshToTex.size() << endl;
	cout << "Position X: " << transform.position.x << endl;
	cout << "Position Y: " << transform.position.y << endl;
	cout << "Position Z: " << transform.position.z << endl;
	cout << "---------------------------------------------" << endl;
	
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

void ModelNode::SetIsAlive(bool value)
{
	Entity::SetIsAlive(value);
	for (int i = 0; i < _meshList.size(); i++)
	{
		_meshList[i]->SetIsAlive(value);
	}
}
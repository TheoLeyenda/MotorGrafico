#include "Model.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "ModelImporter.h"
#include "BSP_Manager.h"
#include "ModelNode.h"

#include "AxisAlignedBoundingBox.h"

Model::Model(Renderer * render) : Entity(render)
{
	myMat = NULL;
	rootNode = NULL;
	modelImporter = new ModelImporter();

	CreateMyAxisAlignedBoundingBox();
	axisAlignedBoundingBox->AttachEntity(internalData, transform);
	isRootHerarchy = true;
}

Model::~Model()
{
	if (modelImporter != NULL)
		delete modelImporter;

	if (!myMat)
		delete myMat;

	UnloadModel();
}

void Model::LoadModel(const string & filePath, const string & texturePath, BSP_Manager* bsp_manager)
{
	if (modelImporter != NULL)
	{
		rootNode = modelImporter->LoadModel(modelMeshes, filePath, texturePath, rootNode, modelChildrens, textureList, renderer, bsp_manager);
	}

	if (rootNode != NULL) {
		AddChildren(rootNode);
		rootNode->_textureList = textureList;
	}

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->_textureList = textureList;
	}

	vector<glm::vec3> _dataXYZ;

	for (int i = 0; i < modelMeshes.size(); i++)
	{
		for (int j = 0; j < modelMeshes[i]->meshXYZVertices.size(); j++)
		{
			_dataXYZ.push_back(modelMeshes[i]->meshXYZVertices[j]);
		}
	}

	if (axisAlignedBoundingBox != NULL) 
	{
		axisAlignedBoundingBox->SetVerticesColliders(axisAlignedBoundingBox->GenerateAxisAlignedBoundingBoxPos(_dataXYZ),
			axisAlignedBoundingBox->GenerateAxisAlignedBoundingBoxCol());
	}
}

void Model::Draw(bool & wireFrameActive)
{
	if (isAlive)
	{
		axisAlignedBoundingBox->UpdateInternalDataBoundingBox(internalData, transform);

		if (rootNode != NULL)
			rootNode->Draw(wireFrameActive);
	}
	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->Draw(wireFrameActive);
	}
	if (isAlive) 
	{
		axisAlignedBoundingBox->Draw(axisAlignedBoundingBox->GetEnableDraw());
	}
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

void Model::BindBuffer(){}

void Model::SetEnableDrawAABB(bool value)
{
	if (axisAlignedBoundingBox != NULL)
		axisAlignedBoundingBox->SetEnableDraw(value);
}

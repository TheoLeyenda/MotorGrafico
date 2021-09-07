#include "Model.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "ModelImporter.h"

#include "ModelNode.h"

#include "AxisAlignedBoundingBox.h"

Model::Model(Renderer * render, bool hasBPSPlane) : Entity(render)
{
	myMat = NULL;
	rootNode = NULL;
	modelImporter = new ModelImporter();

	hasBSPPlanes = hasBPSPlane;

	CreateMyAxisAlignedBoundingBox();
	axisAlignedBoundingBox->AttachEntity(internalData, transform);
}

Model::~Model()
{
	if (modelImporter != NULL)
		delete modelImporter;

	if (!myMat)
		delete myMat;

	if (planeBSP1 != NULL && planeBSP2 != NULL && planeBSP3 != NULL)
	{
		delete planeBSP1;
		delete planeBSP2;
		delete planeBSP3;

		planeBSP1 = NULL;
		planeBSP2 = NULL;
		planeBSP3 = NULL;
	}

	UnloadModel();
}

void Model::LoadModel(const string & filePath, const string & texturePath)
{
	if (modelImporter != NULL) 
	{
		rootNode = modelImporter->LoadModel(modelMeshes, filePath, texturePath, rootNode ,modelChildrens, textureList ,renderer);
	}

	if (!hasBSPPlanes)
	{
		planeBSP1 = NULL;
		planeBSP2 = NULL;
		planeBSP3 = NULL;
	}
	else
	{
		//cout << "POS PLANE 1: " << "[" << modelImporter->getPlanesBSP()[BSP_PLANE1][0].x << "][" << modelImporter->getPlanesBSP()[BSP_PLANE1][0].y <<
		//	"][" << modelImporter->getPlanesBSP()[BSP_PLANE1][0].z << "]" << endl;
		//cin.get();

		planeBSP1 = new PlaneBSP("BSP_Plane1",modelImporter->getPlanesBSP()[BSP_PLANE1][0], modelImporter->getPlanesBSP()[BSP_PLANE1][2],
			modelImporter->getPlanesBSP()[BSP_PLANE1][1]);

		planeBSP2 = new PlaneBSP("BSP_Plane2", modelImporter->getPlanesBSP()[BSP_PLANE2][0], modelImporter->getPlanesBSP()[BSP_PLANE2][1],
			modelImporter->getPlanesBSP()[BSP_PLANE2][2]);

		planeBSP3 = new PlaneBSP("BSP_Plane3", modelImporter->getPlanesBSP()[BSP_PLANE3][0], modelImporter->getPlanesBSP()[BSP_PLANE3][2],
			modelImporter->getPlanesBSP()[BSP_PLANE3][1]);

		cout<<"Normal plane 1: [" << planeBSP1->getPlaneNormal().x << "]["<<
			planeBSP1->getPlaneNormal().y << "]["<< planeBSP1->getPlaneNormal().z << "]" <<endl;
		cout << "Normal plane 2: [" << planeBSP2->getPlaneNormal().x << "][" <<
			planeBSP2->getPlaneNormal().y << "][" << planeBSP2->getPlaneNormal().z << "]" << endl;
		cout << "Normal plane 3: [" << planeBSP3->getPlaneNormal().x << "][" <<
			planeBSP3->getPlaneNormal().y << "][" << planeBSP3->getPlaneNormal().z<< "]" << endl;
		
		//planeBSP2->flipPlaneBSP();
		//planeBSP3->flipPlaneBSP();
		//
		//cout << "Normal plane 2: [" << planeBSP2->getPlaneNormal().x << "][" <<
		//	planeBSP2->getPlaneNormal().y << "][" << planeBSP2->getPlaneNormal().z << endl;
		//
		//cout << "Normal plane 3: [" << planeBSP3->getPlaneNormal().x << "][" <<
		//	planeBSP3->getPlaneNormal().y << "][" << planeBSP3->getPlaneNormal().z << "]" << endl;

		for (int i = 0; i < modelImporter->getPlanesBSP().size(); i++)
		{
			cout << "BSP_PLANE: "<< i+1 << endl;

			for (int j = 0; j < modelImporter->getPlanesBSP()[i].size(); j++)
			{
				cout <<"Position: "<< j <<
					   " X[" << modelImporter->getPlanesBSP()[i][j].x <<
					   "]Y[" << modelImporter->getPlanesBSP()[i][j].y <<
					   "]Z[" << modelImporter->getPlanesBSP()[i][j].z <<"]"<<endl;
			}
		}
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

	vector<glm::vec3> _dataXYZ;

	for (int i = 0; i < modelMeshes.size(); i++) 
	{
		for (int j = 0; j < modelMeshes[i]->meshXYZVertices.size(); j++)
		{
			_dataXYZ.push_back(modelMeshes[i]->meshXYZVertices[j]);
		}
	}
	//cout << GetName() << ": " << modelMeshes.size()<< " meshes" <<endl;
	axisAlignedBoundingBox->SetVerticesColliders(axisAlignedBoundingBox->GenerateAxisAlignedBoundingBoxPos(_dataXYZ),
		axisAlignedBoundingBox->GenerateAxisAlignedBoundingBoxCol());
}

void Model::Draw(bool & wireFrameActive)
{
	axisAlignedBoundingBox->UpdateInternalDataBoundingBox(internalData, transform);

	if (rootNode != NULL)
		rootNode->Draw(wireFrameActive);

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->Draw(wireFrameActive);
	}

	axisAlignedBoundingBox->Draw(axisAlignedBoundingBox->GetEnableDraw());
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

void Model::SetIsAlive(bool value)
{
	Entity::SetIsAlive(value);
	if (rootNode != NULL)
		rootNode->SetIsAlive(value);

	for (int i = 0; i < modelChildrens.size(); i++)
	{
		if (modelChildrens[i] != NULL)
			modelChildrens[i]->SetIsAlive(value);
	}
}

void Model::BindBuffer(){}

void Model::SetEnableDrawAABB(bool value)
{
	if (axisAlignedBoundingBox != NULL)
		axisAlignedBoundingBox->SetEnableDraw(value);
}

void Model::updateBSPPlanes(glm::vec3 posPlane1, glm::vec3 posPlane2, glm::vec3 posPlane3)
{
	if (!hasBSPPlanes)
		return;

	planeBSP1->update_BSP_Plane(modelImporter->getPlanesBSP()[0][0] + posPlane1, modelImporter->getPlanesBSP()[0][2] + posPlane1,
		modelImporter->getPlanesBSP()[0][1] + posPlane1);

	planeBSP2->update_BSP_Plane(modelImporter->getPlanesBSP()[1][0] + posPlane2, modelImporter->getPlanesBSP()[1][1] + posPlane2,
		modelImporter->getPlanesBSP()[1][2] + posPlane2);

	planeBSP3->update_BSP_Plane(modelImporter->getPlanesBSP()[2][0] + posPlane3, modelImporter->getPlanesBSP()[2][2] + posPlane3,
		modelImporter->getPlanesBSP()[2][1] + posPlane3);
}

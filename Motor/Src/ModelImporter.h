#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>

#include "PrivateClass/Export.h"

struct aiNode;
struct aiMesh;
struct aiScene;

enum aiTextureType;

class ModelNode;
class Texture;
class Renderer;
class Mesh;
class BSP_Manager;

using namespace std;

class ENGINE_API ModelImporter 
{
private:
	int indexChildrenLoad;

	int amountForward;
	//ModelNode* auxNode;
	stack<ModelNode*> auxiliarNodes;
	vector<aiNode*> nodes;

	void LoadNode(aiNode* node ,const aiScene* scene, vector<ModelNode*> &childrens ,Renderer* render);
	void LoadMesh(vector<Mesh*> &modelMeshes, vector<ModelNode*> childrens, const aiScene* scene, Renderer* render);
	void LoadMesh(vector<Mesh*> &modelMeshes, ModelNode* rootNode, const aiScene* scene, Renderer* render);
	void LoadMesh(vector<Mesh*> &modelMeshes, aiMesh* mesh, const aiScene* scene,ModelNode* &nodeMesh, Renderer* render);
	void LoadMaterial(const aiScene* scene, const string& texturePath, vector<Texture*> &textureList);
	void LoadTextureFromFile(aiTextureType type);

public:
	ModelImporter();
	~ModelImporter();
	ModelNode* LoadModel(vector<Mesh*> &modelMeshes
		, const string& filePath
		, const string& texturePath
		, ModelNode* rootNode
		, vector<ModelNode*> &childrens
		, vector<Texture*> &textureList
		, Renderer* render
		, BSP_Manager* bsp_manager);
	void ClearNodesOldModel();
	void ClearAuxiliarNodesOldModel();
};

#endif

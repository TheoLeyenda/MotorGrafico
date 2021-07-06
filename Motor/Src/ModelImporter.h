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

using namespace std;

class ENGINE_API ModelImporter 
{
private:
	int indexChildrenLoad;

	int amountForward;
	//ModelNode* auxNode;
	stack<ModelNode*> auxiliarNodes;

	void LoadNode(aiNode* node,const aiScene* scene, vector<ModelNode*> &childrens,Renderer* render);
	void LoadMaterial(const aiScene* scene, const string& texturePath, vector<Texture*> &textureList);
	void LoadMesh(aiMesh* mesh, const aiScene* scene,ModelNode* &nodeMesh, Renderer* render);
	void LoadTextureFromFile(aiTextureType type);
public:
	ModelImporter();
	~ModelImporter();
	ModelNode* LoadModel(const string& filePath, const string& texturePath, ModelNode* rootNode, vector<ModelNode*> &childrens, vector<Texture*> &textureList, Renderer* render);
};

#endif
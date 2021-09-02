#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "PrivateClass/Export.h"

#include "../Lib/glm/vec4.hpp"
#include "../Lib/glm/vec3.hpp"
#include "../Lib/glm/vec2.hpp"
#include "../Lib/glm/mat4x4.hpp"
#include "../Lib/glm/ext/matrix_transform.hpp"
#include "../Lib/glm/ext/matrix_clip_space.hpp"
#include "../Lib/glm/ext/scalar_constants.hpp"

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
	int indexCurrentPlane = 0;
	int currentPlane = 1;
	struct VertexsPlaneBSP {

	public:
		float vertex_max_x;
		float vertex_min_x;
		float vertex_max_y;
		float vertex_min_y;
		float vertex_max_z;
		float vertex_min_z;
		VertexsPlaneBSP(float max_x, float min_x, float max_y, float min_y, float max_z, float min_z) 
		{
			vertex_max_x = max_x;
			vertex_min_x = min_x;
			vertex_max_y = max_y;
			vertex_min_y = min_y;
			vertex_max_z = max_z;
			vertex_min_z = min_z;
		}
		
	};

	vector<VertexsPlaneBSP> vertexsPlanesBSP;

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

	float FindMinValue(vector<float> values);
	float FindMaxValue(vector<float> values);
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

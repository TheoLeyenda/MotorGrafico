#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <iostream>
#include <vector>
#include <string>

#include "PrivateClass/Export.h"

struct aiNode;
struct aiMesh;
struct aiScene;

enum aiTextureType;

class Texture;
class Renderer;
class Mesh;

using namespace std;

class ENGINE_API ModelImporter 
{
private:
	void LoadNode(aiNode* node, const aiScene* scene, vector<Mesh*> &meshList, vector<unsigned int> &meshToTex, Renderer* render);
	void LoadMaterial(const aiScene* scene, const string& texturePath, vector<Texture*> &textureList);
	void LoadMesh(aiMesh* mesh, const aiScene* scene, vector<Mesh*> &meshList, vector<unsigned int> &meshToTex, Renderer* render);
	void LoadTextureFromFile(aiTextureType type);
public:
	ModelImporter();
	~ModelImporter();
	void LoadModel(const string& filePath, const string& texturePath,
		vector<Texture*> &textureList, vector<Mesh*> &meshList,
		vector<unsigned int> &meshToTex, Renderer* render);
};

#endif

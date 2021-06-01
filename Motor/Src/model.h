#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

using namespace std;

class ENGINE_API Model : public Entity
{
public:
	Model(Renderer* render);
	~Model();

	void LoadModel(const string& filePath, const string& texturePath);
	void Draw(bool& wireFrameActive) override;
	void UnloadModel();

	void SetScaleModel(float x, float y, float z);
	void SetScaleModel(glm::vec3 scale);
	void SetPositionModel(float x, float y, float z);
	void SetPositionModel(glm::vec3 position);
	void SetRotation(float x, float y, float z);
protected:
	void BindBuffer() override;

private:
	vector<Mesh*> meshList;
	vector<Texture*> textureList;
	vector<unsigned int> meshToTex;

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterial(const aiScene* scene,const string& texturePath);
};

#endif

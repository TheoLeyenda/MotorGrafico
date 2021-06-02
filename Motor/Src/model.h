#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

using namespace std;

class ENGINE_API Model : public Entity
{
public:
	Model(Renderer* render);
	~Model();

	void LoadModel(const string& filePath, const string& texturePath);
	void Draw(bool& wireFrameActive) override;
	void UnloadModel();

	void SetMaterial(Material* mat);
	virtual void SetScale(float x, float y, float z);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotationX(float x);
	virtual void SetRotationY(float y);
	virtual void SetRotationZ(float z);
	virtual void SetIsAlive(bool value);
protected:
	void BindBuffer() override;

private:
	vector<Mesh*> meshList;
	vector<Texture*> textureList;
	vector<unsigned int> meshToTex;

	Material* myMat;

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterial(const aiScene* scene,const string& texturePath);
};

#endif

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

using namespace std;

class ModelImporter;
class ModelNode;

class ENGINE_API Model : public Entity
{
private:
	ModelImporter* modelImporter = NULL;
public:
	Model(Renderer* render);
	~Model();

	void LoadModel(const string& filePath, const string& texturePath);
	void Draw(bool& wireFrameActive) override;
	void UnloadModel();

	string GetClassName() override;

	void SetMaterial(Material* mat);
	virtual void SetScale(float x, float y, float z);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotationX(float x);
	virtual void SetRotationY(float y);
	virtual void SetRotationZ(float z);
	virtual void SetIsAlive(bool value);
	vector<ModelNode*> GetModelChildrens() { return modelChildrens; }
protected:
	void BindBuffer() override;
private:
	//vector<Mesh*> meshList;
	//vector<unsigned int> meshToTex;
	vector<Texture*> textureList;
	vector<ModelNode*> modelChildrens;
	ModelNode* rootNode;

	Material* myMat;
};

#endif

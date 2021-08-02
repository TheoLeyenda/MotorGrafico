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
	virtual void SetIsAlive(bool value);
	
	ModelNode* GetMyModelNode() { return rootNode; }
	vector<ModelNode*> GetModelChildrens() { return modelChildrens; }
	vector<Mesh*> GetModelMeshes() { return modelMeshes; }

protected:
	void BindBuffer() override;
	void SetEnableDrawAABB(bool value) override;
private:
	vector<Texture*> textureList;
	vector<ModelNode*> modelChildrens;
	vector<Mesh*> modelMeshes;
	ModelNode* rootNode;
	Material* myMat;
};

#endif

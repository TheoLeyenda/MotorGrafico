#ifndef MODELNODE_H
#define MODELNODE_H

#include "Entity.h"
#include "PrivateClass/Export.h"

struct aiNode;
struct aiMesh;
struct aiScene;

class Mesh;
class Texture;

class ENGINE_API ModelNode : public Entity
{
public:
	ModelNode(Renderer* render, aiNode* node);
	~ModelNode();

	void Draw(bool& wireFrameActive) override;
	
	void SetMaterialNode(Material* mat);
	void SetTexturesList(vector<Texture*> &textureList);
	virtual void SetScale(float x, float y, float z);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotationX(float x);
	virtual void SetRotationY(float y);
	virtual void SetRotationZ(float z);
	virtual void SetIsAlive(bool value);

	vector<Mesh*> _meshList;
	vector<Texture*> _textureList;
	vector<unsigned int> _meshToTex;

	string GetNodeName();
	bool allchildrensDone;

	void PrintMyInfo();

protected:
	void BindBuffer() override;
private:
	Material* myMat;

	aiNode* _myNode;
};
#endif // !MODELNODE_H
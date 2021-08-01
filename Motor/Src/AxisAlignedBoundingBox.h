#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "PrivateClass/Export.h"
#include "Entity.h"
#include <vector>

#define ERROR_CODE -999999

const int countVerticesCollider = 8;
const int verticesDataCountArr = 56;
const int elemForVertexCount = 7;
const int indicesVertexCollider = 36;

class ENGINE_API AxisAlignedBoundingBox : public Entity
{
private:

	bool enableDraw = true;
	bool enableInitData = true;

	Transform entityTransform;
	InternalData internalDataAttach;
	glm::vec3 verticesColliderPositions[countVerticesCollider];
	glm::vec4 verticesColliderColor[countVerticesCollider];
	unsigned int indexsVerticesColliderPositions[indicesVertexCollider] = {
		0,1,2,2,3,0,//FRENTE
		4,5,6,6,7,4,//ATRAS
		4,0,1,1,5,4,//IZQUIERDA
		7,3,0,0,4,7,//ARRIBA
		7,6,2,2,3,7,//DERECHA
		6,2,1,1,5,6 //ARRIBA
	};
	float verticesData[verticesDataCountArr];
	glm::vec3 returnArrPositions[countVerticesCollider];
	glm::vec4 returnArrColors[countVerticesCollider];
	Material* my_Mat;

	void UpdateVerticesData();

	float GetMinNum(vector<float> _values);
	float GetMaxNum(vector<float> _values);

	void CreateAxisAlignedBoundingBox();
	void BindGeneralData();
	void SetVAO();
	void SetVBO();
	void SetIBO();
	void UnbindBuffers();
protected:
	void BindBuffer() override;
	void UseMyMaterial();

public:
	AxisAlignedBoundingBox(Renderer* render);
	~AxisAlignedBoundingBox();

	glm::vec3* GenerateAxisAlignedBoundingBoxPos(vector<glm::vec3> _values);
	glm::vec4* GenerateAxisAlignedBoundingBoxCol();

	void SetNewMaterial(Material* mat);
	void AttachEntity(InternalData& entityInternalData, Transform& transformAttach);
	void UpdateInternalDataBoundingBox(InternalData& entityInternalData, Transform& transformAttach);
	void SetVerticesColliders(glm::vec3 values[countVerticesCollider], glm::vec4 colors[countVerticesCollider]);
	void SetVerticesColliders(unsigned int index, glm::vec3 value);
	string GetClassName() override;
	void Draw(bool& colliderDrawActive) override;
	void SetEnableDraw(bool value) { enableDraw = value; }
	bool& GetEnableDraw() { return enableDraw; }
};

#endif

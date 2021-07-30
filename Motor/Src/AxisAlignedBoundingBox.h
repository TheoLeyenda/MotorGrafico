#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "PrivateClass/Export.h"
#include "Entity.h"
#include <vector>

#define TAM_COLLIDER 8
#define TAM_VERTICES_DATA 24
#define TAM_INDICES_VERTEX_DATA 36
#define ERROR_CODE -999999

class ENGINE_API AxisAlignedBoundingBox : public Entity
{
private:

	bool enableDraw = true;
	bool enableInitData = true;

	const int elementsForVertexCount = 3;

	InternalData internalDataAttach;
	glm::vec3 verticesColliderPositions[TAM_COLLIDER];
	unsigned int indexsVerticesColliderPositions[TAM_INDICES_VERTEX_DATA] = {
	0, 1, 2, 2, 3, 0,	   //Frente
	14, 17, 18, 18, 13, 14,//Derecha
	4, 7, 6, 6, 5, 4,      //Atras			DONE
	16, 15, 12, 12, 19, 16,//Izquierda
	20, 11, 10, 10, 21, 20,//Abajo
	8, 9, 22, 22, 23, 8    //Arriba
	};
	float verticesData[TAM_VERTICES_DATA];

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

public:
	AxisAlignedBoundingBox(Renderer* render);
	~AxisAlignedBoundingBox();

	glm::vec3* GenerateAxisAlignedBoundingBox(vector<glm::vec3> _values);

	void AttachEntity(InternalData entityInternalData) { internalDataAttach = entityInternalData; }
	void SetVerticesCollidersPositions(glm::vec3 values[TAM_COLLIDER]);
	void SetVerticesCollidersPositions(unsigned int index, glm::vec3 value);
	string GetClassName() override;
	void Draw(bool& wireFrameActive) override;
	void SetEnableDraw(bool value) { enableDraw = value; }
	bool& GetEnableDraw() { return enableDraw; }
};

#endif

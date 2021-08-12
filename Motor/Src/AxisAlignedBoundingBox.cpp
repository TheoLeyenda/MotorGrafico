#include "AxisAlignedBoundingBox.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(Renderer * render) : Entity(render)
{
	my_Mat = new Material();
	my_Mat->SetAmbientMat(glm::vec3(1.0f, 1.0f, 1.0f));
	my_Mat->SetDiffuseMat(glm::vec3(1.0f, 1.0f, 1.0f));
	my_Mat->SetSpecularMat(glm::vec3(1.0f, 1.0f, 1.0f));
	my_Mat->SetNewShininess(0.6f, 124);

	SetNewMaterial(my_Mat);

	SetIsAlive(true);
	for (int i = 0; i < countVerticesCollider; i++)
	{
		verticesColliderPositions[i] = glm::vec3(0,0,0);
		verticesColliderColor[i] = glm::vec4(0.0);
	}
	for (int j = 0; j < verticesDataCountArr; j++)
	{
		verticesData[j] = 0.0f;
	}
}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox(){}

float AxisAlignedBoundingBox::GetMinNum(vector<float> _values)
{
	if (_values.size() <= 0)
		return ERROR_CODE;

	float min = _values[0];

	for (int i = 0; i < _values.size(); i++) 
	{
		if (_values[i] < min)
			min = _values[i];
	}

	//cout << "min: " << min << endl;
	return min;
}

float AxisAlignedBoundingBox::GetMaxNum(vector<float> _values)
{

	if (_values.size() <= 0)
		return ERROR_CODE;

	float max = _values[0];

	for (int i = 0; i < _values.size(); i++) 
	{
		if (_values[i] > max)
			max = _values[i];
	}

	//cout << "max: " << min << endl;
	return max;
}

glm::vec3 * AxisAlignedBoundingBox::GenerateAxisAlignedBoundingBoxPos(vector<glm::vec3> _values)
{
	if (_values.size() <= 0)
		return NULL;

	vector<float> values_x;
	vector<float> values_y;
	vector<float> values_z;

	for (int i = 0; i < _values.size(); i++) 
	{
		values_x.push_back(_values[i].x);
		values_y.push_back(_values[i].y);
		values_z.push_back(_values[i].z);
	}

	float min_x = GetMinNum(values_x) - 0.04f;
	float max_x = GetMaxNum(values_x) + 0.04f;
	float min_y = GetMinNum(values_y) - 0.04f;
	float max_y = GetMaxNum(values_y) + 0.04f;
	float min_z = GetMinNum(values_z) - 0.04f;
	float max_z = GetMaxNum(values_z) + 0.04f;

	returnArrPositions[0] = glm::vec3(min_x, max_y, min_z);
	returnArrPositions[1] = glm::vec3(min_x, min_y, min_z);
	returnArrPositions[2] = glm::vec3(max_x, min_y, min_z);
	returnArrPositions[3] = glm::vec3(max_x, max_y, min_z);
	returnArrPositions[4] = glm::vec3(min_x, max_y, max_z);
	returnArrPositions[5] = glm::vec3(min_x, min_y, max_z);
	returnArrPositions[6] = glm::vec3(max_x, min_y, max_z);
	returnArrPositions[7] = glm::vec3(max_x, max_y, max_z);

	/*cout << "DATA AABB" << endl;
	for (int i = 0; i < countVerticesCollider; i++)
	{
		cout << i << "_[" << returnArrPositions[i].x << "][" << returnArrPositions[i].y << "][" << returnArrPositions[i].z << "]." << endl;
	}*/

	return returnArrPositions;
}

glm::vec3 * AxisAlignedBoundingBox::GenerateAABBFrustrumPerspective(vector<glm::vec3> _values)
{
	if (_values.size() <= 0)
		return NULL;

	vector<float> values_x;
	vector<float> values_y;
	vector<float> values_z;

	for (int i = 0; i < _values.size(); i++)
	{
		values_x.push_back(_values[i].x);
		values_y.push_back(_values[i].y);
		values_z.push_back(_values[i].z);
	}

	for (int i = 0; i < countVerticesCollider; i++)
	{
		returnArrPositions[i] = glm::vec3(values_x[i], values_y[i], values_z[i]);
	}

	cout << "DATA AABB" << endl;
	for (int i = 0; i < countVerticesCollider; i++)
	{
		cout << i << "_[" << returnArrPositions[i].x << "][" << returnArrPositions[i].y << "][" << returnArrPositions[i].z << "]." << endl;
	}

	return returnArrPositions;
}

glm::vec4 * AxisAlignedBoundingBox::GenerateAxisAlignedBoundingBoxCol()
{
	for (int i = 0; i < countVerticesCollider; i++)
	{
		returnArrColors[i] = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	}

	return returnArrColors;
}

void AxisAlignedBoundingBox::CreateAxisAlignedBoundingBox()
{
	//---
	SetVAO();
	//---
	SetIBO();
	//---
	SetVBO();
	//---
	UnbindBuffers();
	//---
}

void AxisAlignedBoundingBox::BindGeneralData()
{
	glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, elemForVertexCount * sizeof(float), 0);
	glEnableVertexAttribArray(_positionLocation);
	glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, elemForVertexCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colorLocation);
}

void AxisAlignedBoundingBox::SetVAO()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void AxisAlignedBoundingBox::SetVBO()
{
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	
	_positionLocation = glGetAttribLocation(renderer->GetCurrentShaderUse().getId(), "position");
	_colorLocation = glGetAttribLocation(renderer->GetCurrentShaderUse().getId(), "customColor");

	BindGeneralData();
}

void AxisAlignedBoundingBox::SetIBO()
{
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexsVerticesColliderPositions), indexsVerticesColliderPositions, GL_STATIC_DRAW);
}

void AxisAlignedBoundingBox::UnbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void AxisAlignedBoundingBox::BindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	BindGeneralData();
}

void AxisAlignedBoundingBox::SetEnableDrawAABB(bool value)
{
	SetEnableDraw(value);
}

void AxisAlignedBoundingBox::UseMyMaterial()
{
	if (my_Mat != NULL)
		my_Mat->UseMaterial(renderer->GetCurrentShaderUse());
}

void AxisAlignedBoundingBox::SetNewMaterial(Material * mat)
{
	my_Mat = mat;

	renderer->SetMaterial(my_Mat);
}

void AxisAlignedBoundingBox::UpdateVerticesData()
{
	//cout << "VERTEX DATA POSITION" << endl;
	int i = 0;
	for (int j = 0; j < countVerticesCollider; j++)
	{
		if (i + 2 < verticesDataCountArr) {
			verticesData[i] = verticesColliderPositions[j].x;
			verticesData[i + 1] = verticesColliderPositions[j].y;
			verticesData[i + 2] = verticesColliderPositions[j].z;

			//cout << "[" << verticesData[i] << "][" << verticesData[i + 1] <<
			//	"][" << verticesData[i + 2] << "]." << endl;

			i = i + 7;
		}
	}
	i = 0;
	//cout << "VERTEX DATA COLOR" << endl;
	for (int j = 0; j < countVerticesCollider; j++)
	{
		if (i + 6 < verticesDataCountArr) {
			verticesData[i + 3] = verticesColliderColor[j].x;
			verticesData[i + 4] = verticesColliderColor[j].y;
			verticesData[i + 5] = verticesColliderColor[j].z;
			verticesData[i + 6] = verticesColliderColor[j].w;

			//cout << "[" << verticesData[i + 3] << "][" << verticesData[i + 4] << "][" 
			//	<< verticesData[i + 5] << "]["<< verticesData[i + 6]<<"]."<< endl;

			i = i + 7;
		}
	}

	if (enableInitData) {
		CreateAxisAlignedBoundingBox();
		enableInitData = false;
	}
}

void AxisAlignedBoundingBox::AttachEntity(InternalData& entityInternalData, Transform& transformAttach)
{
	internalDataAttach = entityInternalData;
	entityTransform = transformAttach;
	internalData = internalDataAttach;
	transform = entityTransform;
	UpdateMatrixModel();
}

void AxisAlignedBoundingBox::UpdateInternalDataBoundingBox(InternalData & entityInternalData, Transform & transformAttach)
{
	internalDataAttach = entityInternalData;
	entityTransform = transformAttach;
	internalData = internalDataAttach;
	transform = entityTransform;
	UpdateMatrixModel();
}

void AxisAlignedBoundingBox::SetVerticesColliders(glm::vec3 values[countVerticesCollider], glm::vec4 colors[countVerticesCollider])
{
	for (int i = 0; i < countVerticesCollider; i++)
	{
		verticesColliderPositions[i].x = values[i].x;
		verticesColliderPositions[i].y = values[i].y;
		verticesColliderPositions[i].z = values[i].z;

		verticesColliderColor[i].x = colors[i].x;
		verticesColliderColor[i].y = colors[i].y;
		verticesColliderColor[i].z = colors[i].z;
		verticesColliderColor[i].w = colors[i].w;
	}

	UpdateVerticesData();
}

void AxisAlignedBoundingBox::SetVerticesColliders(unsigned int index, glm::vec3 value)
{
	if (index >= countVerticesCollider || index < 0)
		return;

	verticesColliderPositions[index] = value;

	UpdateVerticesData();
}

string AxisAlignedBoundingBox::GetClassName()
{
	return "AxisAlignedBoundingBox";
}

void AxisAlignedBoundingBox::Draw(bool & colliderDrawActive)
{
	if (isAlive && enableDraw)
	{
		BindBuffer();
		//----
		if (my_Mat != NULL)
			UseMyMaterial();
		//----
		renderer->DrawColliders(indicesVertexCollider, renderer->GetCurrentShaderUse(), internalDataAttach.localModel, colliderDrawActive);
	}
}
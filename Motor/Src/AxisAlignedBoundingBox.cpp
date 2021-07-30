#include "AxisAlignedBoundingBox.h"
#include <glew.h>
#include <GLFW/glfw3.h>

AxisAlignedBoundingBox::AxisAlignedBoundingBox(Renderer * render) : Entity(render)
{}

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

glm::vec3 * AxisAlignedBoundingBox::GenerateAxisAlignedBoundingBox(vector<glm::vec3> _values)
{
	if (_values.size() <= 0)
		return NULL;

	glm::vec3 returnArr[TAM_COLLIDER];

	vector<float> values_x;
	vector<float> values_y;
	vector<float> values_z;

	for (int i = 0; i < _values.size(); i++) 
	{
		values_x.push_back(_values[i].x);
		values_y.push_back(_values[i].y);
		values_z.push_back(_values[i].z);
	}

	float min_x = GetMinNum(values_x);
	float max_x = GetMaxNum(values_x);
	float min_y = GetMinNum(values_y);
	float max_y = GetMaxNum(values_y);
	float min_z = GetMinNum(values_z);
	float max_z = GetMaxNum(values_z);

	returnArr[0] = glm::vec3(min_x, max_y, min_z);
	returnArr[1] = glm::vec3(min_x, min_y, min_z);
	returnArr[2] = glm::vec3(max_x, min_y, min_z);
	returnArr[3] = glm::vec3(max_x, max_y, min_z);
	returnArr[4] = glm::vec3(min_x, max_y, max_z);
	returnArr[5] = glm::vec3(min_x, min_y, max_z);
	returnArr[6] = glm::vec3(max_x, min_y, max_z);
	returnArr[7] = glm::vec3(max_x, max_y, max_z);

	return returnArr;
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
	glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), 0);
	glEnableVertexAttribArray(_positionLocation);
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

void AxisAlignedBoundingBox::UpdateVerticesData()
{
	int i = 0;
	for (int j = 0; j < TAM_COLLIDER; j++) 
	{
		if (i + 2 < TAM_VERTICES_DATA) {
			verticesData[i] = verticesColliderPositions[j].x;
			verticesData[i + 1] = verticesColliderPositions[j].y;
			verticesData[i + 2] = verticesColliderPositions[j].z;

			i = i + 3;
		}
	}

	if (enableInitData) {
		CreateAxisAlignedBoundingBox();
		enableInitData = false;
	}
}

void AxisAlignedBoundingBox::SetVerticesCollidersPositions(glm::vec3 values[TAM_COLLIDER])
{
	for (int i = 0; i < TAM_COLLIDER; i++) 
	{
		verticesColliderPositions[i] = values[i];
	}

	UpdateVerticesData();
}

void AxisAlignedBoundingBox::SetVerticesCollidersPositions(unsigned int index, glm::vec3 value)
{
	if (index >= TAM_COLLIDER || index < 0)
		return;

	verticesColliderPositions[index] = value;

	UpdateVerticesData();
}

string AxisAlignedBoundingBox::GetClassName()
{
	return "AxisAlignedBoundingBox";
}

void AxisAlignedBoundingBox::Draw(bool & wireFrameActive)
{
	if (isAlive && enableDraw)
	{
		//----
		BindBuffer();
		//----
		renderer->Draw(TAM_INDICES_VERTEX_DATA, renderer->GetCurrentShaderUse(), internalDataAttach.localModel, wireFrameActive);

	}
}

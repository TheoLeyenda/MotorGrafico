#include "Primitive3D.h"
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"

Primitive3D::Primitive3D(Renderer* renderer) : Entity(renderer)
{
	_type = Pyramid;
	myMathLibrary.CalcAverageNormals(indexCube, indicesCubeCount, vertexCube, verticesCubeCount, elementsForVertexCubeCount, offsetNormalDataCube);
	myMathLibrary.CalcAverageNormals(indexPyramid, indicesPyramidCount, vertexPyramid, verticesPyramidCount, elementsForVertexPyramidCount, offsetNormalDataPyramid);

	CreateDataModel();
}

Primitive3D::Primitive3D(Renderer * renderer, TypeModel typeModel) : Entity(renderer)
{
	_type = typeModel;
	myMathLibrary.CalcAverageNormals(indexCube, indicesCubeCount, vertexCube, verticesCubeCount, elementsForVertexCubeCount, offsetNormalDataCube);
	myMathLibrary.CalcAverageNormals(indexPyramid, indicesPyramidCount, vertexPyramid, verticesPyramidCount, elementsForVertexPyramidCount, offsetNormalDataPyramid);

	CreateDataModel();
}

Primitive3D::~Primitive3D()
{
}

void Primitive3D::SetVAO()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void Primitive3D::SetVBO()
{
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER,_vbo);
	switch (_type)
	{
	case Cube:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCube), vertexCube, GL_STATIC_DRAW);
		break;
	case Pyramid:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPyramid), vertexPyramid, GL_STATIC_DRAW);
		break;
	}
	_posAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(),"position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 10 *sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	
	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);

	_normalAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "norm");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);

}

void Primitive3D::SetIBO()
{
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	switch (_type)	
	{
	case Cube:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexCube), indexCube, GL_STATIC_DRAW);
		break;
	case Pyramid:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexPyramid), indexPyramid, GL_STATIC_DRAW);
		break;
	}
}

void Primitive3D::BindVAO()
{
	glBindVertexArray(_vao);
}

void Primitive3D::BindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
}

void Primitive3D::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	_posAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);

	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);

	_normalAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "norm");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);
}

void Primitive3D::UnbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Primitive3D::UnbindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Primitive3D::UnbindVAO()
{
	glBindVertexArray(0);
}

void Primitive3D::CreateDataModel()
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

void Primitive3D::UseMyMaterial()
{
	my_Mat->UseMaterial(renderer->GetShaderColor());
}

void Primitive3D::SetNewMaterial(Material * mat)
{
	my_Mat = mat;

	renderer->SetMaterial(my_Mat);
}

void Primitive3D::Draw()
{
	//----
	UseMyMaterial();
	//----
	switch (_type)
	{
	case Cube:
		renderer->DrawModel(indicesCubeCount,renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib,_colAttrib, _normalAttrib);
		break;
	case Pyramid:
		renderer->DrawModel(indicesPyramidCount, renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib, _colAttrib, _normalAttrib);
		break;
	}
	//----
}

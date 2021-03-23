#include "model.h"
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>

Model3D::Model3D(Renderer* renderer) : Entity(renderer)
{
	_type = Pyramid;
	CreateDataModel();
}

Model3D::Model3D(Renderer * renderer, TypeModel typeModel) : Entity(renderer)
{
	_type = typeModel;
	CreateDataModel();
}

Model3D::~Model3D()
{
}

void Model3D::SetVAO()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void Model3D::SetVBO()
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
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);
}

void Model3D::SetIBO()
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

void Model3D::BindVAO()
{
	glBindVertexArray(_vao);
}

void Model3D::BindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
}

void Model3D::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	_posAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);
}

void Model3D::UnbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model3D::UnbindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model3D::UnbindVAO()
{
	glBindVertexArray(0);
}

void Model3D::CreateDataModel()
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

void Model3D::Draw()
{
	//----
	switch (_type)
	{
	case Cube:
		renderer->DrawModel(indicesCube,renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib,_colAttrib);
		break;
	case Pyramid:
		renderer->DrawModel(indicesPyramid, renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib, _colAttrib);
		break;
	}
	//----
}

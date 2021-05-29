#include "Primitive3D.h"
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"

Primitive3D::Primitive3D(Renderer* renderer) : Entity(renderer)
{
	_type = Pyramid;
	//myMathLibrary.CalcAverageNormals(indexCube, indicesCubeCount, vertexCube, verticesCubeCount, elementsForVertexCount, offsetNormalDataCube);
	//myMathLibrary.CalcAverageNormals(indexPyramid, indicesPyramidCount, vertexPyramid, verticesPyramidCount, elementsForVertexCount, offsetNormalDataPyramid);

	_path = "None Path";
	_useTexture = false;
	my_Mat = NULL;
	CreateDataModel();
}

Primitive3D::Primitive3D(Renderer * renderer, TypeModel typeModel) : Entity(renderer)
{
	_type = typeModel;
	//myMathLibrary.CalcAverageNormals(indexCube, indicesCubeCount, vertexCube, verticesCubeCount, elementsForVertexCount, offsetNormalDataCube);
	//myMathLibrary.CalcAverageNormals(indexPyramid, indicesPyramidCount, vertexPyramid, verticesPyramidCount, elementsForVertexCount, offsetNormalDataPyramid);
	
	_path = "None Path";
	_useTexture = false;
	my_Mat = NULL;
	CreateDataModel();
}

Primitive3D::Primitive3D(Renderer* renderer, TypeModel typeModel, const char* filePath, bool useTransparency) : Entity(renderer)
{
	_type = typeModel;
	//myMathLibrary.CalcAverageNormals(indexCube, indicesCubeCount, vertexCube, verticesCubeCount, elementsForVertexCount, offsetNormalDataCube);
	//myMathLibrary.CalcAverageNormals(indexPyramid, indicesPyramidCount, vertexPyramid, verticesPyramidCount, elementsForVertexCount, offsetNormalDataPyramid);
	
	CreateDataModel();

	_path = filePath;
	_transparency = useTransparency;
	_useTexture = true;
	my_Mat = NULL;

	if (_transparency)
		BlendSprite();

	LoadTexture(_path, _transparency);
}

Primitive3D::~Primitive3D()
{
	if (texImporter != NULL)
		delete texImporter;
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
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, elementsForVertexCount *sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	
	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);

	_normalAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "norm");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);

	_uvAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "m_TexCoord");
	glVertexAttribPointer(_uvAttrib, 2, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(_uvAttrib);

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
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);

	_colAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttrib, 4, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttrib);

	_normalAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "norm");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);

	_uvAttrib = glGetAttribLocation(renderer->GetShaderColor().getId(), "m_TexCoord");
	glVertexAttribPointer(_uvAttrib, 2, GL_FLOAT, GL_FALSE, elementsForVertexCount * sizeof(float), (void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(_uvAttrib);
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

void Primitive3D::BlendSprite()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Primitive3D::UnBlendSprite()
{
	glDisable(GL_BLEND);
}

void Primitive3D::UseMyMaterial()
{
	if(my_Mat != NULL)
		my_Mat->UseMaterial(renderer->GetShaderColor());
}

void Primitive3D::SetNewMaterial(Material * mat)
{
	my_Mat = mat;

	renderer->SetMaterial(my_Mat);
}

void Primitive3D::Draw()
{
	CheckIsModel();
	//----
	if (_useTexture)
	{
		if (_transparency)
			BlendSprite();

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);

	}
	UseMyMaterial();
	//----
	switch (_type)
	{
	case Cube:
		renderer->DrawModel(indicesCubeCount, renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib, _colAttrib, _normalAttrib, _uvAttrib);
		break;
	case Pyramid:
		renderer->DrawModel(indicesPyramidCount, renderer->GetShaderColor(),
			internalData.model, _vbo, _ibo, _posAttrib, _colAttrib, _normalAttrib, _uvAttrib);
		break;
	}

	if (_useTexture)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		if (_transparency)
			UnBlendSprite();
	}

	//----
}

void Primitive3D::LoadTexture(const char* path, bool transparent) {
	_useTexture = true;
	_transparency = transparent;
	texImporter->LoadTexture(path, data, _texture, _width, _height, _nrChannels, _transparency);
}

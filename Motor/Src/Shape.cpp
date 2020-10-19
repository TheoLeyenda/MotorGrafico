#include <iostream>
#include "Shape.h"
#include <glew.h>
#include <GLFW/glfw3.h>


float vertexBufferTri[] = {
	//X		  Y		 Z		R	  G	    B	  A
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 1.0f
};

float vertexBufferQuad[] = {
	//X		  Y		 Z		R	  G	    B	  A
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f
};

unsigned int indicesTri[] = {
	0,1,2
};

unsigned int indicesQuad[]= {
	0,1,2,
	0,3,2
};

float ColorTri[]
{
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
};

float ColorQuad[]
{
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	1.0f,0.0f,1.0f,1.0f,
};

Shape::Shape(Renderer *_renderer): Entity2D(_renderer)
{
	renderer = _renderer;
}

Shape::Shape(Renderer * _renderer, Material * _material) : Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
}

Shape::~Shape(){}

void Shape::InitShape(unsigned int typeShape)
{
	//material->SetMaterialValue()
	_currentShape = typeShape;
	switch (_currentShape)
	{
	case GL_TRIANGLES:
		_vertexBuffer = vertexBufferTri;
		_indexBuffer = indicesTri;
		_countIndices = 3;
		
		//material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		//SetVertexMaterial(material->GetColorRGBA(), vertexBufferTri, 3, 4, 3);

		material->SetMaterialValue(ColorTri, 4,3);
		SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferTri, 3, 4, 3, 4);
		
		break;
	case GL_TRIANGLE_STRIP:
		_vertexBuffer = vertexBufferQuad;
		_indexBuffer = indicesQuad;
		_countIndices = 6;

		//material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		//SetVertexMaterial(material->GetColorRGBA(),vertexBufferQuad,3,4,4);
		
		material->SetMaterialValue(ColorQuad, 4, 4);
		SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferQuad, 3, 4, 4, 4);
		
		break;
	}
	CreateVbo(_vertexBuffer);
	CreateIbo(_indexBuffer,_countIndices);
}

void Shape::CreateVbo(float* vertexBuffer){

	int tam = 0;
	while (vertexBuffer[tam] <= 1 && vertexBuffer[tam] >= -1){
		tam++;
	}
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
}

void Shape::CreateIbo(unsigned int* indeices, int tamIndices){

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tamIndices * sizeof(unsigned int), indeices, GL_STATIC_DRAW);
}

unsigned int Shape::GetVbo(){
	return _vbo;
}

unsigned int Shape::GetIbo(){
	return _ibo;
}

float* Shape::GetVertexBuffer()
{
	return _vertexBuffer;
}

void Shape::SetVertexsAttrib(unsigned int & shaderId){
	_posAttrib = glGetAttribLocation(shaderId, "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	_colorAttrib = glGetAttribLocation(shaderId, "customColor");
	glVertexAttribPointer(_colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colorAttrib);
}

unsigned int Shape::GetPosAttrib(){
	return _posAttrib;
}

unsigned int Shape::GetColAttrib(){
	return _colorAttrib;
}

void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int offset, int stride, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = offset; j < stride+offset; j++){
			VBA[j + (offset + stride) * i] = material[j-offset];
		}
	}
}
void Shape::SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe)
{
	//SetVertexMaterial(material->GetVertexColorRGBA(), 4, vertexBufferTri, 3, 4, 3);
	int k = 0;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < repeticiones; i++) 
	{
		for (int j = start; j < offset + start; j++) 
		{
			VBA[j + (start + offset) * i] = materials[i][k];
			std::cout << VBA[j + (start + offset) * i];
			k++;
		}
		k = 0;
		std::cout << std::endl;
	}
}
void Shape::Draw(unsigned int figura,int indices, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	if (renderer != NULL)
	{
		renderer->BeignDraw();

		renderer->Draw(figura, indices, _ibo, _vbo,shaderProg,GetPosAttrib(),GetColAttrib(), model);

		renderer->EndDraw(refWindow);
	}
	_currentShape = figura;
}
void Shape::SetSolidColor(float r, float g, float b, float a)
{
	material->SetMaterialValue(r, g, b, a);
	switch (_currentShape)
	{
	case GL_TRIANGLES:

		SetVertexMaterial(material->GetColorRGBA(), vertexBufferTri, 3, 4, 3);
		break;
	case GL_QUADS:
		SetVertexMaterial(material->GetColorRGBA(), vertexBufferQuad, 3, 4, 4);
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	int tam = 0;
	int tam2 = 0;
	while (_vertexBuffer[tam] <= 1 && _vertexBuffer[tam] >= -1) {
		tam++;
	}
	while (_indexBuffer[tam2] <= 1 && _indexBuffer[tam2] >= -1) {
		tam2++;
	}
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), _vertexBuffer, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam2 * sizeof(unsigned int), _indexBuffer, GL_STATIC_DRAW);
	renderer->SetShader();
}
//float vertexBufferTri[] = {
//	//X		  Y		 Z		R	  G	    B	  A
//	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
//	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
//	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 1.0f
//};
//float vertexBufferQuad[] = {
//	//X		  Y		 Z	   R	  G	     B	   A
//	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
//	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
//	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f
//	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
//};
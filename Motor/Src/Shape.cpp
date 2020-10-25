#include <iostream>
#include "Shape.h"
#include <glew.h>
#include <GLFW/glfw3.h>

#define FINALARRAY 5

float vertexBufferTri[] = {
	//X		  Y		 Z		R	  G	    B  	  S	    T
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f, 0.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 0.5f, 1.0f, FINALARRAY
};

float vertexBufferQuad[] = {
	//X		  Y		 Z		R	  G	    B      S     T
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 0.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 1.0f,FINALARRAY
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

Shape::Shape(Renderer *_renderer, bool _useTexture): Entity2D(_renderer)
{
	renderer = _renderer;
	useTexture = _useTexture;
}

Shape::Shape(Renderer * _renderer, Material * _material, bool _useTexture) : Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
	useTexture = _useTexture;
}

Shape::~Shape(){}

void Shape::SetShape(unsigned int typeShape, TypeColorShape typeColorShape)
{
	//material->SetMaterialValue()
	_currentShape = typeShape;
	_typeColorShape = typeColorShape;
	switch (typeShape)
	{
	case GL_TRIANGLES:
		_vertexBuffer = vertexBufferTri;
		
		/*if (_typeColorShape == TypeColorShape::SolidColor) {
			material->SetMaterialValue(1.0f, 1.0f, 1.0f);
			SetVertexMaterial(material->GetColorRGB(), vertexBufferTri, 3, 4, 3);
		}
		else if (_typeColorShape == TypeColorShape::VertexColor) {
			material->SetMaterialValue(ColorTri, 4, 3);
			SetVertexMaterial(material->GetVertexColorRGB(), vertexBufferTri, 3, 4, 3, 3);
		}*/
		break;
	case GL_QUADS:
		_vertexBuffer = vertexBufferQuad;
		/*if (_typeColorShape == TypeColorShape::SolidColor) {
			material->SetMaterialValue(1.0f, 1.0f, 1.0f);
			SetVertexMaterial(material->GetColorRGB(),vertexBufferQuad,3,4,4);
		}
		else if (_typeColorShape == TypeColorShape::VertexColor) {
			material->SetMaterialValue(ColorQuad, 4, 4);
			SetVertexMaterial(material->GetVertexColorRGB(), vertexBufferQuad, 3, 4, 3, 4);
		}*/
		break;
	}
	CreateVbo(_vertexBuffer);
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

unsigned int Shape::GetVbo(){
	return _vbo;
}

float* Shape::GetVertexBuffer()
{
	return _vertexBuffer;
}

void Shape::SetVertexsAttrib(unsigned int & shaderId){

	int countElementsForVertex = 8;


	_posAttrib = glGetAttribLocation(shaderId, "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib);
	_colorAttrib = glGetAttribLocation(shaderId, "customColor");
	glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colorAttrib);

	if (useTexture)
	{
		glUniform1i(_textureAttrib = glGetUniformLocation(shaderId, "ourTexture"), 0);
		glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(_textureAttrib);
	}
}

unsigned int Shape::GetPosAttrib(){
	return _posAttrib;
}

unsigned int Shape::GetColAttrib(){
	return _colorAttrib;
}
															//     3            5             4
void Shape::SetVertexMaterial(glm::vec3 material, float* VBA, int offset, int stride, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = offset; j < stride+offset; j++){
			VBA[j + (offset + stride) * i] = material[j-offset];
		}
	}
}
/*float vertexBufferQuad[] = {
	//X		  Y		 Z		R	  G	    B      S     T
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 0.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 0.0f,FINALARRAY
};*/
void Shape::SetVertexMaterial(glm::vec3* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe)
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
void Shape::Draw(unsigned int figura,int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	if (renderer != NULL)
	{
		renderer->BeignDraw();

		renderer->Draw(figura, vertexs, GetVbo(), shaderProg,GetPosAttrib(),GetColAttrib(), GetTextureAttrib(), model, useTexture);

		renderer->EndDraw(refWindow);
	}
	_currentShape = figura;
}
void Shape::SetSolidColor(float r, float g, float b)
{
	material->SetMaterialValue(r, g, b);
	switch (_currentShape)
	{
	case GL_TRIANGLES:

		SetVertexMaterial(material->GetColorRGB(), vertexBufferTri, 3, 4, 3);
		break;
	case GL_QUADS:
		SetVertexMaterial(material->GetColorRGB(), vertexBufferQuad, 3, 4, 4);
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	int tam = 0;
	while (_vertexBuffer[tam] <= 1 && _vertexBuffer[tam] >= -1) {
		tam++;
	}
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), _vertexBuffer, GL_DYNAMIC_DRAW);
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
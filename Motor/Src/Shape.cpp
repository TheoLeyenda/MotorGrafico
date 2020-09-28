#include <iostream>
#include "Shape.h"



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

void Shape::InitShape(GLenum typeShape)
{
	//material->SetMaterialValue()
	_currentShape = typeShape;
	switch (typeShape)
	{
	case GL_TRIANGLES:
		_vertexBuffer = vertexBufferTri;
		
		//material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		//SetVertexMaterial(material->GetColorRGBA(), vertexBufferTri, 3, 4, 3);

		material->SetMaterialValue(ColorTri, 4,3);
		SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferTri, 3, 4, 3, 4);
		
		break;
	case GL_QUADS:
		_vertexBuffer = vertexBufferQuad;
		
		//material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		//SetVertexMaterial(material->GetColorRGBA(),vertexBufferQuad,3,4,4);
		
		material->SetMaterialValue(ColorQuad, 4, 4);
		SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferQuad, 3, 4, 4, 4);
		
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

void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int start, int offset, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = start; j < offset+start; j++){
			VBA[j + (start + offset) * i] = material[j-start];
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
void Shape::Draw(GLenum figura,int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	if (renderer != NULL)
	{
		renderer->BeignDraw();

		renderer->Draw(figura, vertexs, GetVbo(), shaderProg,GetPosAttrib(),GetColAttrib(), model);

		renderer->EndDraw(refWindow);
	}
	_currentShape = figura;
}
void Shape::SetSolidColor(float r, float g, float b, float a, const std::string& vertexShader, const std::string& fragmentShader)
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
	int tam = 0;
	while (_vertexBuffer[tam] <= 1 && _vertexBuffer[tam] >= -1) {
		tam++;
	}
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), _vertexBuffer, GL_DYNAMIC_DRAW);
	renderer->SetShader(vertexShader,fragmentShader);
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
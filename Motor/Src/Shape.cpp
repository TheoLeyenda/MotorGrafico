#include <iostream>
#include "Shape.h"
#include <glew.h>
#include <GLFW/glfw3.h>

#define FINALARRAY 5
//==============================================
float vertexBufferTextureTri[] = {
	//X		  Y		 Z		R	  G	    B  	  S	    T
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f, 0.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 0.5f, 1.0f, FINALARRAY
};
//==============================================
float vertexBufferTextureQuad[] = {
	//X		  Y		 Z		R	  G	    B      S     T
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 0.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 1.0f,FINALARRAY
};
//==============================================
float vertexBufferColorTri[] = {
	//X		  Y		 Z		R	  G	    B	  A
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 1.0f,FINALARRAY
};
//==============================================
float vertexBufferColorQuad[] = {
	//X		  Y		 Z	   R	  G	     B	   A
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,FINALARRAY
};
//==============================================
float ColorTri[]
{
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
};
//==============================================
float ColorQuad[]
{
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	1.0f,0.0f,1.0f,1.0f,
};


Shape::Shape(Renderer * _renderer, const char * filePath): Entity2D(_renderer)
{
	renderer = _renderer;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);
	
	_typeMaterial = TypeMaterial::Texture;
	

	renderer->SetTypeShader(TypeShader::FragmentTexture);
	renderer->SetShader();
	_filePathTexture = filePath;

	//BindTexture();

}

Shape::Shape(Renderer * _renderer, Material * _material,  const char * filePath): Entity2D(_renderer, _material)
{
	renderer = _renderer;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);

	material = _material;
	_typeMaterial = TypeMaterial::Color;

	renderer->SetTypeShader(TypeShader::FragmentTexture);
	renderer->SetShader();
	_filePathTexture = filePath;

	//BindTexture();
}

//==============================================
Shape::Shape(Renderer *_renderer): Entity2D(_renderer)
{
	renderer = _renderer;
	_typeMaterial = TypeMaterial::Color;
	
	renderer->SetTypeShader(TypeShader::FragmentColor);
	renderer->SetShader();

	_filePathTexture = "None Path";
}
//==============================================
Shape::Shape(Renderer * _renderer, Material * _material) : Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
	_typeMaterial = TypeMaterial::Color;

	renderer->SetTypeShader(TypeShader::FragmentColor);
	renderer->SetShader();

	_filePathTexture = "None Path";
}
//==============================================
Shape::~Shape(){}
void Shape::BindTexture()
{
	textureImporter.BindTexture(texture);
}
//==============================================
void Shape::SetShape(unsigned int typeShape, TypeColorShape typeColorShape)
{
	_currentShape = typeShape;
	_typeColorShape = typeColorShape;
	switch (typeShape)
	{
	case GL_TRIANGLES:
		if (_typeMaterial == TypeMaterial::Texture) 
		{
			_vertexBuffer = vertexBufferTextureTri;
		}
		else 
		{
			_vertexBuffer = vertexBufferColorTri;
			if (_typeColorShape == TypeColorShape::SolidColor) {
				material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
				SetVertexMaterial(material->GetColorRGBA(), vertexBufferColorTri, 3, 4, 3);
			}
			else if (_typeColorShape == TypeColorShape::VertexColor) {
				material->SetMaterialValue(ColorTri, 4, 3);
				SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferColorTri, 3, 4, 3, 4);
			}
		}
		break;
	case GL_QUADS:
		if (_typeMaterial == TypeMaterial::Texture) 
		{
			_vertexBuffer = vertexBufferTextureQuad;
		}
		else 
		{
			_vertexBuffer = vertexBufferColorQuad;
			if (_typeColorShape == TypeColorShape::SolidColor) {
				material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
				SetVertexMaterial(material->GetColorRGBA(),vertexBufferColorQuad,3,4,4);
			}
			else if (_typeColorShape == TypeColorShape::VertexColor) {
				material->SetMaterialValue(ColorQuad, 4, 4);
				SetVertexMaterial(material->GetVertexColorRGBA(), vertexBufferColorQuad, 3, 4, 4, 4);
			}
		}
		break;
	}
	CreateVbo(_vertexBuffer);
}
//==============================================
void Shape::CreateVbo(float* vertexBuffer){

	int tam = 0;
	while (vertexBuffer[tam] <= 1 && vertexBuffer[tam] >= -1){
		tam++;
	}
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
}
//==============================================
unsigned int Shape::GetVbo(){
	return _vbo;
}
//==============================================
float* Shape::GetVertexBuffer()
{
	return _vertexBuffer;
}
//==============================================
void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int offset, int stride, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = offset; j < stride+offset; j++){
			VBA[j + (offset + stride) * i] = material[j-offset];
		}
	}
}
//==============================================
void Shape::SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe)
{
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
//==============================================
void Shape::Draw(unsigned int figura,int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	if (renderer != NULL)
	{
		//renderer->BeignDraw();

		if (_typeMaterial == TypeMaterial::Texture) 
		{
			renderer->DrawShape(figura, vertexs, GetVbo(), shaderProg, model, true);
			BindTexture();
			//if (figura == TypeShape::TRIANGLE)
				//std::cout << "Tri:" << texture << std::endl;
			//else if (figura == TypeShape::QUAD)
				//std::cout << "Quad:" << texture << std::endl;
		}
		else
		{
			renderer->DrawShape(figura, vertexs, GetVbo(), shaderProg, model, false);
		}

		//renderer->EndDraw(refWindow);
	}
	_currentShape = figura;
}
//==============================================
void Shape::SetSolidColor(float r, float g, float b)
{
	material->SetMaterialValue(r, g, b,1.0f);
	switch (_currentShape)
	{
	case GL_TRIANGLES:
		SetVertexMaterial(material->GetColorRGBA(), vertexBufferColorTri, 3, 4, 3);
		break;
	case GL_QUADS:
		SetVertexMaterial(material->GetColorRGBA(), vertexBufferColorQuad, 3, 4, 4);
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
//==============================================
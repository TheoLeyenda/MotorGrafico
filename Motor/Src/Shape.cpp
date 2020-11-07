#include <iostream>
#include "Shape.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#define FINALARRAY 5

float vertexBufferTextureTri[] = {
	//X		  Y		 Z		R	  G	    B  	  S	    T
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f, 0.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 0.5f, 1.0f, FINALARRAY
};

float vertexBufferTextureQuad[] = {
	//X		  Y		 Z		R	  G	    B      S     T
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 0.0f, 0.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 0.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f, 1.0f,FINALARRAY
};

float vertexBufferColorTri[] = {
	//X		  Y		 Z		R	  G	    B	  A
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 1.0f,FINALARRAY
};

float vertexBufferColorQuad[] = {
	//X		  Y		 Z	   R	  G	     B	   A
	-0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
	 0.5f ,  0.5f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,FINALARRAY
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


Shape::Shape(Renderer * _renderer,TypeShape typeShape, const char * filePath): Entity2D(_renderer)
{
	_currentShape = typeShape;
	renderer = _renderer;
	_path = filePath;
	_transparency = false;
	texImporter = new TextureImporter();

	_typeMaterial = TypeMaterial::Texture;
	
	renderer->SetTypeShader(TypeShader::FragmentTexture);
	renderer->SetShader();
	
	SetShape(_currentShape, _typeColorShape);
	SetVertexsAttribShape(_typeMaterial);

	if (_transparency)
		BlendSprite();

	LoadTexture(_path, _transparency);
	
}

Shape::Shape(Renderer * _renderer, TypeShape typeShape, Material * _material,  const char * filePath): Entity2D(_renderer, _material)
{
	_currentShape = typeShape;
	renderer = _renderer;

	_path = filePath;
	_transparency = false;
	texImporter = new TextureImporter();

	material = _material;
	_typeMaterial = TypeMaterial::Texture;

	renderer->SetTypeShader(TypeShader::FragmentTexture);
	renderer->SetShader();

	SetShape(_currentShape, _typeColorShape);
	SetVertexsAttribShape(_typeMaterial);
	if(_transparency)
		BlendSprite();

	LoadTexture(_path, _transparency);
}

Shape::Shape(Renderer *_renderer, TypeShape typeShape, TypeColorShape typeColorShape): Entity2D(_renderer)
{
	_currentShape = typeShape;
	_typeColorShape = typeColorShape;
	renderer = _renderer;
	_typeMaterial = TypeMaterial::Color;
	
	renderer->SetTypeShader(TypeShader::FragmentColor);
	renderer->SetShader();

	_path = "None Path";
	SetShape(_currentShape, _typeColorShape);
	SetVertexsAttribShape(_typeMaterial);

}

Shape::Shape(Renderer * _renderer, Material * _material, TypeShape typeShape, TypeColorShape typeColorShape) : Entity2D(_renderer, _material)
{
	_currentShape = typeShape;
	_typeColorShape = typeColorShape;
	renderer = _renderer;
	material = _material;
	_typeMaterial = TypeMaterial::Color;

	renderer->SetTypeShader(TypeShader::FragmentColor);
	renderer->SetShader();
	
	_path = "None Path";
	SetShape(_currentShape, _typeColorShape);
	SetVertexsAttribShape(_typeMaterial);

}
Shape::~Shape()
{
	if (texImporter != NULL)
		delete texImporter;
}
//==============================================
void Shape:: BlendSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Shape::UnBlendSprite() {
	glDisable(GL_BLEND);
}
void Shape::LoadTexture(const char* path, bool transparent) {
	_transparency = transparent;
	texImporter->LoadTexture(path, data, _texture, _width, _height, _nrChannels, _transparency);
}
//==============================================
void Shape::SetVertexsAttribShape(TypeMaterial typeMaterial)
{
	renderer->SetVertexsAttribShape(typeMaterial);
}
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

void Shape::CreateVbo(float* vertexBuffer)
{
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

void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int offset, int stride, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = offset; j < stride+offset; j++){
			VBA[j + (offset + stride) * i] = material[j-offset];
		}
	}
}

void Shape::SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe)
{
	int k = 0;
	//std::cout << std::endl;
	//std::cout << std::endl;
	for (int i = 0; i < repeticiones; i++) 
	{
		for (int j = start; j < offset + start; j++) 
		{
			VBA[j + (start + offset) * i] = materials[i][k];
			std::cout << VBA[j + (start + offset) * i];
			k++;
		}
		k = 0;
		//std::cout << std::endl;
	}
}

void Shape::Draw(unsigned int figura,int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	_currentShape = figura;
	if (renderer != NULL)
	{

		if (_typeMaterial == TypeMaterial::Texture)
		{

			if (_transparency)
				BlendSprite();
			glEnable(GL_TEXTURE_2D);

			renderer->UpdateModel(model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture);

			renderer->DrawShape(figura, vertexs, GetVbo(), shaderProg, model, true);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisable(GL_TEXTURE_2D);

			if (_transparency)
				UnBlendSprite();
			
			//renderer->SetVertexsAttribShape(_typeMaterial);
		}
		else if(_typeMaterial == TypeMaterial::Color)
		{
			renderer->DrawShape(figura, vertexs, GetVbo(), shaderProg, model, false);
		}
	}
}

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

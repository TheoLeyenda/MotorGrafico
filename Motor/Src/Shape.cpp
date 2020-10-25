#include <iostream>
#include "Shape.h"
#include <glew.h>
#include <GLFW/glfw3.h>

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

Shape::Shape(Renderer *_renderer, TypeMaterial typeMaterial): Entity2D(_renderer)
{
	renderer = _renderer;
	_typeMaterial = typeMaterial;
	
	if (_typeMaterial == TypeMaterial::Color)
	{
		renderer->SetTypeShader(TypeShader::FragmentColor);
		renderer->SetShader();
	}
	else if (_typeMaterial == TypeMaterial::Texture)
	{
		renderer->SetTypeShader(TypeShader::FragmentTexture);
		renderer->SetShader();
	}
}

Shape::Shape(Renderer * _renderer, Material * _material, TypeMaterial typeMaterial) : Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
	_typeMaterial = typeMaterial;

	if (_typeMaterial == TypeMaterial::Color) 
	{
		renderer->SetTypeShader(TypeShader::FragmentColor);
		renderer->SetShader();
	}
	else if(_typeMaterial == TypeMaterial::Texture)
	{
		renderer->SetTypeShader(TypeShader::FragmentTexture);
		renderer->SetShader();
	}
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
		if (_typeMaterial == TypeMaterial::Texture) 
		{
			//renderer->SetTypeShader(TypeShader::FragmentTexture);
			_vertexBuffer = vertexBufferTextureTri;
		}
		else 
		{
			//renderer->SetTypeShader(TypeShader::FragmentColor);
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
			//renderer->SetTypeShader(TypeShader::FragmentTexture);
			_vertexBuffer = vertexBufferTextureQuad;
		}
		else 
		{
			//renderer->SetTypeShader(TypeShader::FragmentColor);
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
	

	if (_typeMaterial == TypeMaterial::Texture)
	{
		_posAttrib = glGetAttribLocation(shaderId, "position");
		glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttrib);
		_colorAttrib = glGetAttribLocation(shaderId, "customColor");
		glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
		glUniform1i(_textureAttrib = glGetUniformLocation(shaderId, "ourTexture"), 0);
		glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(_textureAttrib);
	}
	else if(_typeMaterial == TypeMaterial::Color)
	{
		_posAttrib = glGetAttribLocation(shaderId, "position");
		glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttrib);
		_colorAttrib = glGetAttribLocation(shaderId, "customColor");
		glVertexAttribPointer(_colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
	}

}

unsigned int Shape::GetPosAttrib(){
	return _posAttrib;
}

unsigned int Shape::GetColAttrib(){
	return _colorAttrib;
}
															//     3            5             4
void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int offset, int stride, int repeticiones){
	
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
void Shape::Draw(unsigned int figura,int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model)
{
	if (renderer != NULL)
	{
		renderer->BeignDraw();

		if (_typeMaterial == TypeMaterial::Texture) 
		{
			renderer->Draw(figura, vertexs, GetVbo(), shaderProg, GetPosAttrib(), GetColAttrib(), GetTextureAttrib(), model, true);
		}
		else
		{
			renderer->Draw(figura, vertexs, GetVbo(), shaderProg, GetPosAttrib(), GetColAttrib(), GetTextureAttrib(), model, false);
		}

		renderer->EndDraw(refWindow);
	}
	_currentShape = figura;
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

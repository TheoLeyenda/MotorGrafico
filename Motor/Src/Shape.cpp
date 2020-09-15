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
	switch (typeShape)
	{
	case GL_TRIANGLES:
		_vertexBuffer = vertexBufferTri;
		material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		SetVertexMaterial(material->GetColorRGBA(), vertexBufferTri, 3, 4, 3);
		break;
	case GL_QUADS:
		_vertexBuffer = vertexBufferQuad;
		material->SetMaterialValue(0.5f, 0.3f, 0.2f, 1.0f);
		SetVertexMaterial(material->GetColorRGBA(),vertexBufferQuad,3,4,4);
		break;
	}
	CreateVbo(_vertexBuffer);
}

void Shape::CreateVbo(float* vertexBuffer){

	int tam = 0;
	while (vertexBuffer[tam] <= 1 && vertexBuffer[tam] >= -1){
		tam++;
	}
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
}

void Shape::DrawShape(GLenum typeShape)
{
	switch (typeShape)
	{
	case GL_TRIANGLES: glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	case GL_QUADS: glDrawArrays(GL_QUADS, 0, 4);
		break;
	}
}

float* Shape::GetVertexBuffer()
{
	return _vertexBuffer;
}

void Shape::SetVertexMaterial(glm::vec4 material, float* VBA, int start, int offset, int repeticiones){
	
	for (int i = 0; i < repeticiones; i++){
		for (int j = start; j < offset+start; j++){
			VBA[j + (start + offset) * i] = material[j-start];
		}
	}
}
//float vertexBufferTri[] = {
//	//X		  Y		 Z		R	  G	    B	  A
//	-0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
//	 0.5f , -0.5f , 0.0f, 0.0f , 0.0f ,0.0f, 1.0f,
//	 0.0f ,  0.5f , 0.0f, 0.0f , 0.0f, 0.0f, 1.0f
//};
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
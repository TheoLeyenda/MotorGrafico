#include "Shape.h"

float vertexBufferTri[] = {
	-0.5f , -0.5f , 1.0f , 0.0f ,0.0f,
	 0.5f , -0.5f , 0.0f , 1.0f ,0.0f,
	 0.0f ,  0.5f , 0.0f , 0.0f, 1.0f
};
float vertexBufferQuad[] = {
	-0.5f ,  0.5f , 1.0f , 0.0f , 0.0f,
	-0.5f , -0.5f , 0.0f , 1.0f , 0.0f,
	 0.5f , -0.5f , 0.0f , 0.0f , 1.0f,
	 0.5f ,  0.5f , 1.0f , 0.0f , 0.0f
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

void Shape::DrawShape(GLenum typeShape)
{
	switch (typeShape){
	case GL_TRIANGLES:
		_vertexBuffer = vertexBufferTri;
		break;
	case GL_QUADS:
		_vertexBuffer = vertexBufferQuad;
		break;
	}
	GetRenderer()->CreateVbo(_vertexBuffer);
	GetRenderer()->CreateShaderProgram();

}

float* Shape::GetVertexBuffer()
{
	return _vertexBuffer;
}
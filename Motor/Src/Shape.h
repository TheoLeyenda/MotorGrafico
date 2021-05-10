#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"

#include "Entity2D.h"
#include "../Lib/glm/vec4.hpp"
#include "TextureImporter.h"

static enum TypeShape 
{
	TRIANGLE = 0x0004,
	QUAD = 0x0007,
};
static enum TypeColorShape 
{
	SolidColor,
	VertexColor,
};
static enum TypeMaterial 
{
	TextureType = 1,
	ColorType = 2,
};
//typedef unsigned int GLenum;
class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
	unsigned int _vbo;
	unsigned int _currentShape;
	TypeColorShape _typeColorShape;
	TypeMaterial _typeMaterial;

	//Texture
	unsigned char* data;
	int _height;
	int _width;
	int _nrChannels;
	const char* _path;
	bool _transparency;
	TextureImporter* texImporter;

	//Texture
	//unsigned int texture;
	//const char* _filePathTexture;
	//TextureImporter textureImporter;
	//unsigned char* data;
	//int width;
	//int height;
	//int nrChannels;
public:
	unsigned int _texture;

	Shape(Renderer *_renderer, TypeShape typeShape, const char* filePath);
	Shape(Renderer *_renderer, TypeShape typeShape, Material* _material, const char* filePath);
	Shape(Renderer *_renderer, TypeShape typeShape, TypeColorShape typeColorShape);
	Shape(Renderer *_renderer, Material* _material, TypeShape typeShape, TypeColorShape typeColorShape);
	~Shape();

	//Textures

	void SetShape(unsigned int typeShape, TypeColorShape typeColorShape);
	void CreateVbo(float* vertexBuffer);
	unsigned int GetVbo();
	float* GetVertexBuffer();
	void SetVertexMaterial(glm::vec4 material,float* VBA, int start,int offset, int repeticiones);
	void SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe);
	void Draw(unsigned int figura, int vertexs);
	void SetSolidColor(float r, float g, float b);
	void SetTypeColorShape(TypeColorShape typeColorShape) { _typeColorShape = typeColorShape; }
	TypeColorShape GetTypeColorShape() { return _typeColorShape; }
	unsigned int GetCurrentShape() { return _currentShape; }
	void SetVertexsAttribShape(TypeMaterial typeMaterial);
	
	void BlendSprite();
	void UnBlendSprite();
	void LoadTexture(const char* path, bool transparent);
};
#endif
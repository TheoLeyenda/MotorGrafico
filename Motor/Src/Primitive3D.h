#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "PrivateClass/Export.h"
#include "Entity.h"
#include "TextureImporter.h"

ENGINE_API enum TypeModel
{
	Cube,
	Pyramid
};

const int indicesCubeCount = 36;
const int verticesCubeCount = 96;
const int offsetNormalDataCube = 7;

const int indicesPyramidCount = 24;
const int verticesPyramidCount = 60;
const int offsetNormalDataPyramid = 7;

const int elementsForVertexCount = 12;

class ENGINE_API Primitive3D : public Entity
{
private:

	float vertexCube[verticesCubeCount] = {
	//	x		y		z		r		g		b		 a			 Normal           UV
	  -1.0,   -1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   1.0,   -1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   1.0,    1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	  -1.0,    1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	  -1.0,   -1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   1.0,   -1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   1.0,    1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	  -1.0,    1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	float vertexPyramid[verticesPyramidCount] = {
		//	x		y		z		r		g		b		a		  Normal             UV 
		  -1.0f,  -1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		   0.0f,  -1.0f,   1.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 1.0f, 0.0f,	 0.5f, 0.0f,
		   1.0f,  -1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
		   0.0f,   1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  1.0f, 0.0f, 0.0f,	 0.5f, 1.0f,
		   0.0f,  -1.0f,  -1.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  1.0f, 1.0f, 0.0f,	 0.5f, -1.0f,
	};																				
	unsigned int indexCube[indicesCubeCount] = {	
		0, 1, 2,							
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};
	unsigned int indexPyramid[indicesPyramidCount] = {
		0,3,1,
		1,3,2,
		0,3,4,
		4,3,2,
		0,1,2,
		2,4,0
	};
	TypeModel _type;
	unsigned int _ibo;
	unsigned int _vbo;
	unsigned int _vao;

	unsigned int _posAttrib;
	unsigned int _colAttrib;
	unsigned int _normalAttrib;
	unsigned int _uvAttrib;

	//Texture
	bool _useTexture = true;
	unsigned char* data;
	int _height;
	int _width;
	int _nrChannels;
	const char* _path;
	bool _transparency;
	unsigned int _texture;
	TextureImporter* texImporter;

	Material* my_Mat;
protected:
	void SetVAO();
	void SetVBO();
	void SetIBO();
	void BindVAO();
	void BindIBO();
	void BindVBO();
	void UnbindBuffers();
	void UnbindIBO();
	void UnbindVAO();
	void CreateDataModel();
	void BlendSprite();
	void UnBlendSprite();
public:
	Primitive3D(Renderer* renderer);
	Primitive3D(Renderer* renderer, TypeModel typeModel);
	Primitive3D(Renderer* renderer, TypeModel typeModel, const char* filePath, bool useTransparency);
	~Primitive3D();
	//GETERS
	TypeModel GetTypeModel() { return _type; }
	//FUNCTIONS
	void UseMyMaterial();
	void SetNewMaterial(Material* mat);
	void Draw();
	void LoadTexture(const char* path, bool transparent);
	void SetUseTexture(bool useTexture) { _useTexture = useTexture; }
	
};
#endif // !MODEL_H
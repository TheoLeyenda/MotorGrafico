#ifndef MODEL_H
#define MODEL_H

#include "PrivateClass/Export.h"
#include "Entity.h"

ENGINE_API enum TypeModel
{
	Cube,
	Pyramid
};

const int indicesCubeCount = 36;
const int verticesCubeCount = 80;
const int elementsForVertexCubeCount = 10;
const int offsetNormalDataCube = 7;

const int indicesPyramidCount = 24;
const int verticesPyramidCount = 50;
const int elementsForVertexPyramidCount = 10;
const int offsetNormalDataPyramid = 7;


class ENGINE_API Model3D : public Entity
{
private:

	float vertexCube[verticesCubeCount] = {
	//	x		y		z		r		g		b		 a			 Normal
	  -1.0,   -1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	   1.0,   -1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	   1.0,    1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	  -1.0,    1.0,    1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	  -1.0,   -1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	   1.0,   -1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	   1.0,    1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	  -1.0,    1.0,   -1.0,    1.0f,  1.0f,	  1.0f,    0.0f,	0.0f, 0.0f, 0.0f,
	};
	float vertexPyramid[verticesPyramidCount] = {
		//	x		y		z		r		g		b		a		  Normal
		  -1.0f,  -1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 0.0f,
		   0.0f,  -1.0f,   1.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 0.0f,
		   1.0f,  -1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 0.0f,
		   0.0f,   1.0f,   0.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 0.0f,
		   0.0f,  -1.0f,  -1.0f,  1.0f,	  1.0f,	  1.0f,	   1.0f,  0.0f, 0.0f, 0.0f,
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
public:
	Model3D(Renderer* renderer);
	Model3D(Renderer* renderer,TypeModel typeModel);
	~Model3D();
	//GETERS
	TypeModel GetTypeModel() { return _type; }
	//FUNCTIONS
	void UseMyMaterial();
	void SetNewMaterial(Material* mat);
	void Draw();
};
#endif // !MODEL_H
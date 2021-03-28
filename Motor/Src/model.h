#ifndef MODEL_H
#define MODEL_H

#include "PrivateClass/Export.h"
#include "Entity.h"

ENGINE_API enum TypeModel
{
	Cube,
	Pyramid
};

const int indicesPyramid = 24;
const int indicesCube = 20;

class ENGINE_API Model3D : public Entity
{
private:

	float vertexCube[48] = {
	//	x		y		z		r		g		b		A
	  -0.5f,  0.0f,	   0.0f,  1.0f,	  0.0f,	  0.0f,	   1.0f,
	  -0.0f, -0.5f,    0.0f,  1.0f,	  0.0f,	  0.0f,	   1.0f,

	};
	float vertexPyramid[35] = {
		//	x		y		z		r		g		b		A
		  -1.0f,  -1.0f,   0.0f,  1.0f,	  0.0f,	  0.0f,	   1.0f,
		   0.0f,  -1.0f,   1.0f,  0.0f,	  1.0f,	  0.0f,	   1.0f,
		   1.0f,  -1.0f,   0.0f,  0.0f,	  0.0f,	  1.0f,	   1.0f,
		   0.0f,   1.0f,   0.0f,  1.0f,	  0.0f,	  0.0f,	   1.0f,
		   0.0f,  -1.0f,  -1.0f,  0.0f,	  1.0f,	  0.0f,	   1.0f,
	};
	unsigned int indexCube[8] = {
		
	};
	unsigned int indexPyramid[indicesPyramid] = {
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
	void UpdateDataModel();
public:
	Model3D(Renderer* renderer);
	Model3D(Renderer* renderer,TypeModel typeModel);
	~Model3D();
	//GETERS
	TypeModel GetTypeModel() { return _type; }
	//FUNCTIONS
	void Draw();
};
#endif // !MODEL_H
#ifndef MYMATHLIBRARY_H
#define MYMATHLIBRARY_H

#include "PrivateClass/Export.h"

class ENGINE_API MyMathLibrary 
{
public:
	MyMathLibrary();
	~MyMathLibrary();

	//Metodo que calcula las normales de cada vertice segun los datos de posicion de estos.
	void CalcAverageNormals(unsigned int* indices,
		unsigned int indicesCount,
		float* vertices,
		unsigned int verticesCount,
		unsigned int vLenght,
		unsigned int normalOffset);
};

#endif
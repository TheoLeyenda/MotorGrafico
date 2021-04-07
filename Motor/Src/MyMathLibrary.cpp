#include "MyMathLibrary.h"
#include "../../glm/glm.hpp"
#include "../Lib/glm/vec4.hpp"
#include "../Lib/glm/vec3.hpp"
#include "../Lib/glm/vec2.hpp"
#include "../Lib/glm/mat4x4.hpp"
#include "../Lib/glm/mat3x3.hpp"
#include "../Lib/glm/mat2x2.hpp"

MyMathLibrary::MyMathLibrary(){}

MyMathLibrary::~MyMathLibrary(){}

void MyMathLibrary::CalcAverageNormals(unsigned int * indices, 
	unsigned int indicesCount, 
	float* vertices, 
	unsigned int verticesCount, 
	unsigned int vLenght, 
	unsigned int normalOffset)
{
	for (unsigned int i = 0; i < indicesCount; i += 3) 
	{
		unsigned int in0 = indices[i] * vLenght;
		unsigned int in1 = indices[i + 1] * vLenght;
		unsigned int in2 = indices[i + 2] * vLenght;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;

	}

	for (unsigned int i = 0; i < verticesCount / vLenght; i++) 
	{
		unsigned int nOffset = i * vLenght + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;

	}
}

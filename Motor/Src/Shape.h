#ifndef SHAPE_H
#define SHAPE_H
#include "PrivateClass/Export.h"

#include "Entity2D.h"
#include "../Lib/glm/vec4.hpp"
class ENGINE_API Shape : public Entity2D
{
private:
	float* _vertexBuffer;
	unsigned int _vbo;
	GLenum _currentShape;
	unsigned int _posAttrib;
	unsigned int _colorAttrib;
public:
	Shape(Renderer *_renderer);
	Shape(Renderer *_renderer, Material* _material);
	~Shape();
	void InitShape(GLenum typeShape);
	void CreateVbo(float* vertexBuffer);
	unsigned int GetVbo();
	float* GetVertexBuffer();
	void SetVertexsAttrib(unsigned int& shaderId);
	unsigned int GetPosAttrib();
	unsigned int GetColAttrib();
	void SetVertexMaterial(glm::vec4 material,float* VBA, int start,int offset, int repeticiones);
	void SetVertexMaterial(glm::vec4* materials, float* VBA, int start, int offset, int repeticiones, int countElementsForRepe);
	void Draw(GLenum figura, int vertexs, unsigned int& shaderProg, Windows* refWindow, glm::mat4 model);
	void SetSolidColor(float r, float g, float b, float a, const std::string& vertexShader, const std::string& fragmentShader);
};
#endif
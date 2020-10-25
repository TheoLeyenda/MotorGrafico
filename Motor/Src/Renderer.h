#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include "Windows.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

struct matrixMVP
{
	glm::mat4 view;
	glm::mat4 projection;
};
static enum TypeShader 
{
	FragmentTexture,
	FragmentColor,
};
class ENGINE_API Renderer {
private:
	//nothing
	unsigned int _shaderProgram;
	matrixMVP _MVP;
	TypeShader _typeShader;
public:
	Renderer();
	~Renderer();
	unsigned int& GetShader();
	glm::mat4 getViewMat();
	glm::mat4 getProjMat();
	void SetShader();
	void GLEWInit();
	void GLClearError();
	bool GLLogCall();
	void UseProgram(unsigned int& shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void ClearShader();
	void BindBuffer(unsigned int vbo, unsigned int posAttrib, unsigned int colAttrib, bool useTexture, unsigned int textureAttrib);
	void UnbindBuffer();
	void BeignDraw();
	void Draw(unsigned int figura, int vertexs, unsigned int vbo, unsigned int& shaderProg, unsigned int posAttrib, unsigned int colAttrib, unsigned int textureAttrib, glm::mat4 model, bool useTexture);
	void EndDraw(Windows* refWindow);
	unsigned int CompileShader(unsigned int type, const char* source);
	int CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
	void SetTypeShader(TypeShader typeShader) { _typeShader = typeShader; }
};
#endif // !RENDERER_H
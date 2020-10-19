#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include "Windows.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct matrixMVP
{
	glm::mat4 view;
	glm::mat4 projection;
};

class ENGINE_API Renderer {
private:
	//nothing
	unsigned int _shaderProgram;
	matrixMVP _MVP;
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
	void BindBuffer(unsigned int ibo,unsigned int vbo, unsigned int posAttrib, unsigned int colAttrib);
	void UnbindBuffer();
	void BeignDraw();
	void Draw(unsigned int figura, int indices, unsigned int ibo,unsigned int vbo,unsigned int& shaderProg, unsigned int posAttrib, unsigned int colAttrib, glm::mat4 model);
	void EndDraw(Windows* refWindow);
	unsigned int CompileShader(unsigned int type, const char* source);
	int CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
};
#endif // !RENDERER_H
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

	//---------
	unsigned int _posAttribShape;
	unsigned int _colorAttrib;
	unsigned int _textureAttribShape;

	unsigned int _posAttribSprite;
	unsigned int _textureAttribSprite;
	//---------
public:
	Renderer();
	~Renderer();
	unsigned int& GetShader();
	glm::mat4 getViewMat();
	glm::mat4 getProjMat();
	//------------
	void SetVertexsAttribShape(int typeMaterial);
	void SetAttribsSprite();
	//------------
	void SetShader();
	void GLEWInit();
	void GLClearError();
	bool GLLogCall();
	void UseProgram(unsigned int& shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void ClearShader();
	void BindBufferShape(unsigned int vbo, bool useTexture);
	void UnbindBuffer();
	//=====================
	void BindBufferSprite(unsigned int vbo);
	//void SetCurrentTexture(unsigned int& texture);
	//=====================
	void BeignDraw();
	void DrawShape(unsigned int figura, int vertexs, unsigned int vbo, unsigned int& shaderProg,glm::mat4 model, bool useTexture);
	void DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, unsigned int & shaderProg, glm::mat4 model);
	void EndDraw(Windows* refWindow);
	//=====================
	unsigned int CompileShader(unsigned int type, const char* source);
	int CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
	void SetTypeShader(TypeShader typeShader) { _typeShader = typeShader; }
};
#endif // !RENDERER_H
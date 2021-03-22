#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include "Windows.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

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
	Shader _shaderColor;
	Shader _shaderTexture;
	matrixMVP _MVP;

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
	Shader& GetShaderColor();
	Shader& GetShaderTexture();
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
	void UseShaderEnt(Shader& shader, glm::mat4 model);
	void ClearShader();
	void BindBufferShape(unsigned int vbo, bool useTexture);
	void UnbindBuffer();

	void SetView();
	void SetView(glm::vec3 posCamera);
	void SetProjection();
	void drawCamera(Shader& shader);
	//=====================
	void BindBufferSprite(unsigned int vbo);
	//=====================
	void BeignDraw();
	void DrawShape(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model, bool useTexture);
	void DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model);
	void EndDraw(Windows* refWindow);
};
#endif // !RENDERER_H
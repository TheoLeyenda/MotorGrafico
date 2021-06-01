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
#include <vector>

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

class Camera;
class Light;
class Material;

const float toRadians = 3.14159265f / 180;

class ENGINE_API Renderer {
private:
	//nothing
	Shader _shaderUse;
public:
	Renderer();
	~Renderer();

	Shader& GetCurrentShaderUse(){ return _shaderUse; }
	void SetCurrentShaderUse(const char* pathVertex, const char* pathFragment);

	//------------
	//------------
	void GLEWInit();
	void GLClearError();
	bool GLLogCall();
	void UseShaderEnt(Shader& shader, glm::mat4 model);
	void ClearShader();
	void UnbindBuffer();

	void SetMaterial(Material* _material);

	void SetLighting(Light* _light, int iteration);

	//=====================

	void Draw(int indices, Shader& shaderProg, glm::mat4 model, bool& wireframeActive);
	//=====================
	void DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model);
	void BeignDraw();
	void EndDraw(Windows* refWindow);
};
#endif // !RENDERER_H
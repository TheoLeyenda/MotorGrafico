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
	void BindBufferModel(unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt, unsigned int normalAtt, unsigned int uvAtt);
	void BindBufferLight(unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt);
	void UnbindBuffer();

	void SetView(Camera* _camera);
	void SetProjectionPerspective(float FOV, float aspect, float near, float front);
	void SetProjectionOrtho(float left, float right, float bottom, float top, float near, float front);
	void drawCamera(Shader& shader, glm::mat4 trsCamera);

	void SetMaterial(Material* _material);

	void SetLighting(Light* _light);
	void SetLighting(Light* _light, int iteration);
	void LightingInfluence(Light* _light, Camera* camera);

	void DrawMeshes(std::vector<unsigned int> indices, Shader & shaderProg, glm::mat4 model, unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int nomAtt, unsigned int texAtt);
	void LocateModel(Shader & shaderProg, glm::mat4 model, unsigned int vbo, unsigned int posAtt);

	//=====================
	void BindBufferSprite(unsigned int vbo);
	//=====================
	void BeignDraw();
	void DrawShape(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model, bool useTexture);
	void DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model);
	void DrawModel(int indices, Shader& shaderProg, glm::mat4 model, unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt, unsigned int normalAtt, unsigned int uvAtt);
	void DrawLight(int indices, Shader& shaderProg, glm::mat4 model,unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt);
	void EndDraw(Windows* refWindow);
};
#endif // !RENDERER_H
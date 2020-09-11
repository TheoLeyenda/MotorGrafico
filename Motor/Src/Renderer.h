#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include <glew.h>
#include <GLFW/glfw3.h>

class ENGINE_API Renderer {
private:
	//float _AttribVertex[TAMVBO];
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _shaderProgram;
	GLuint _vbo;
	GLuint _posAttrib;
	GLuint _colorAttrib;
public:
	Renderer();
	~Renderer();
	void GLEWInit();
	void CreateVbo(float* _vertexBuffer);
	void DrawShapes(GLenum type);
	GLuint CreateVertexShader();
	GLuint CreateFragmentShader();
	void CreateShaderProgram();
	void DeleteShaders();
};
#endif // !RENDERER_H
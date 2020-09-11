#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ENGINE_API Renderer {
private:
	//unsigned int _vertexShader;
	//unsigned int _fragmentShader;
	//unsigned int _shaderProgram;
	//unsigned int _vbo;
	//unsigned int _posAttrib;
	//unsigned int _colorAttrib;
public:
	Renderer();
	~Renderer();
	void GLEWInit();
	void CreateVbo(float* _vertexBuffer);
	void Draw();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	//void DeleteShaders();
};
#endif // !RENDERER_H
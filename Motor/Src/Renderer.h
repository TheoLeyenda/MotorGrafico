#ifndef RENDERER_H
#define RENDERER_H

#define TAMVBO 14

#include "PrivateClass/Export.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ENGINE_API Renderer {
private:
	//nothing
	unsigned int _shader;
public:

	Renderer();
	~Renderer();
	unsigned int GetShader();
	void SetShader(const std::string& vertexShader, const std::string& fragmentShader);
	void GLEWInit();
	void GLClearError();
	bool GLLogCall();
	void Draw(GLenum figura, int vertexs, unsigned int vbo, unsigned int& shaderProg);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
};
#endif // !RENDERER_H
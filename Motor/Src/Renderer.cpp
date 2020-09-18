#include "Renderer.h"
#include <iostream>
Renderer::Renderer() {
	//Nada
}
Renderer::~Renderer() {
	//DeleteShaders();
}

unsigned int Renderer::GetShader()
{
	return _shader;
}
void Renderer::SetShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	_shader = CreateShaderProgram(vertexShader, fragmentShader);
}

void Renderer::GLEWInit(){
	glewExperimental = GL_TRUE;
	glewInit();
}

void Renderer::GLClearError(){
	while (glGetError() != GL_NO_ERROR);
}

bool Renderer::GLLogCall(){
	while (GLenum error = glGetError()){
		std::cout << "[OpenGL Error]	(" << error << ")" << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(GLenum figura, int vertexs, unsigned int vbo, unsigned int& shaderProg){
	
	glUseProgram(shaderProg);

	glBindBuffer(1, vbo);

	glDrawArrays(figura, 0, vertexs);

}

unsigned int Renderer::CompileShader(unsigned int type, const std::string& source){
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		std::cin.get();
		return -1;
	}
	return id;
}

int Renderer::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int sProgram = glCreateProgram();
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(sProgram, vertex);
	glAttachShader(sProgram, fragment);
	glLinkProgram(sProgram);
	glValidateProgram(sProgram);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	unsigned int posAttrib = glGetAttribLocation(sProgram, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);
	unsigned int colorAttrib = glGetAttribLocation(sProgram, "customColor");
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	return sProgram;
}
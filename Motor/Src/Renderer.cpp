
#include "Renderer.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>



Renderer::Renderer() {
	//Nada
}
Renderer::~Renderer() {
	//DeleteShaders();
}

unsigned int& Renderer::GetShader()
{
	return _shaderProgram;
}
void Renderer::SetShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	_shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
}

void Renderer::GLEWInit(){
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK)
		std::cout << "Error on GLEW!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
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

void Renderer::UseProgram(unsigned int& shader, glm::mat4 model){

	unsigned int modelLocation = glGetUniformLocation(shader, "model");
	std::cout << "model location: "<<modelLocation << std::endl;
	//unsigned int viewLocation = glGetUniformLocation(shader, "view");
	//unsigned int projectionLocation = glGetUniformLocation(shader, "projection");
	glUseProgram(shader);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::ClearShader(){
	glUseProgram(0);
}

void Renderer::BindBuffer(unsigned int vbo, unsigned int posAttrib, unsigned int colAttrib){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colAttrib);
}

void Renderer::UnbindBuffer(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::BeignDraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(unsigned int figura, int vertexs, unsigned int vbo, unsigned int& shaderProg, unsigned int posAttrib, unsigned int colAttrib, glm::mat4 model){
	
	BindBuffer(vbo, posAttrib, colAttrib);

	UseProgram(shaderProg, model);

	glDrawArrays(figura, 0, vertexs);

	UnbindBuffer();
}

void Renderer::EndDraw(Windows* refWindow){
	refWindow->SwapBuffersWindows();
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

	return sProgram;
}
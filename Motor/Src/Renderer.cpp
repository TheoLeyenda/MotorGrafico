#include "Renderer.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include "CompilationController.h"

Renderer::Renderer() {
	_MVP.view = glm::mat4(1.0f);
	_MVP.projection = glm::mat4(1.0f);
	_typeShader = TypeShader::FragmentColor;
}
Renderer::~Renderer() {
	//glDeleteProgram(_shaderProgram);
}

unsigned int& Renderer::GetShader()
{
	return _shaderProgram;
}
glm::mat4 Renderer::getViewMat()
{
	return _MVP.view;
}
glm::mat4 Renderer::getProjMat()
{
	return _MVP.projection;
}
void Renderer::SetVertexsAttribShape(int typeMaterial) {

	int countElementsForVertex = 8;
	const int typeMaterialTexture = 1;
	const int typeMaterialColor = 2;

	if (typeMaterial == typeMaterialTexture)	//TEXTURE
	{
		_posAttribShape = glGetAttribLocation(_shaderProgram, "position");
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);

		_colorAttrib = glGetAttribLocation(_shaderProgram, "customColor");
		glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);

		glUniform1i(_textureAttribShape = glGetUniformLocation(_shaderProgram, "ourTexture"), 0);
		glVertexAttribPointer(_textureAttribShape, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(_textureAttribShape);
	}
	else if (typeMaterial == typeMaterialColor) //COLOR
	{
		_posAttribShape = glGetAttribLocation(_shaderProgram, "position");
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);
		_colorAttrib = glGetAttribLocation(_shaderProgram, "customColor");
		glVertexAttribPointer(_colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
	}
}

void Renderer::SetAttribsSprite()
{
	int countElementsForVertex = 5;

	_posAttribSprite = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(_posAttribSprite, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttribSprite);
	//_colorAttrib = glGetAttribLocation(_shaderProgram, "customColor");
	//glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(_colorAttrib);
	glUniform1i(_textureAttribSprite = glGetUniformLocation(_shaderProgram, "ourTexture"), 0);
	glVertexAttribPointer(_textureAttribSprite, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_textureAttribSprite);
}

void Renderer::SetShader()
{
	if (typeCompilation == TypeCompilation::Debug) 
	{
		//std::cout << "Entre al Debug" << std::endl;
		if (_typeShader == TypeShader::FragmentColor)
			_shaderProgram = CreateShaderProgram("../Motor/res/shaders/Vertex.shader", "../Motor/res/shaders/FragmentColor.shader");
		else if (_typeShader == TypeShader::FragmentTexture)
			_shaderProgram = CreateShaderProgram("../Motor/res/shaders/Vertex.shader", "../Motor/res/shaders/FragmentTexture.shader");
	}
	else if (typeCompilation == TypeCompilation::Exe) 
	{
		//std::cout << "Entre al Exe" << std::endl;
		if (_typeShader == TypeShader::FragmentColor)
			_shaderProgram = CreateShaderProgram("res/shaders/Vertex.shader", "res/shaders/FragmentColor.shader");
		else if (_typeShader == TypeShader::FragmentTexture) {
			//std::cout << "Entre al Textura" << std::endl;
			_shaderProgram = CreateShaderProgram("res/shaders/Vertex.shader", "res/shaders/FragmentTexture.shader");
		}
	}
}

void Renderer::GLEWInit() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK)
		std::cout << "Error on GLEW!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Renderer::GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool Renderer::GLLogCall() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]	(" << error << ")" << std::endl;
		return false;
	}
	return true;
}

void Renderer::UseProgram(unsigned int& shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

	unsigned int modelLocation = glGetUniformLocation(shader, "model");
	unsigned int viewLocation = glGetUniformLocation(shader, "view");
	unsigned int projectionLocation = glGetUniformLocation(shader, "projection");

	glUseProgram(shader);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::ClearShader() {
	glUseProgram(0);
}

void Renderer::UpdateModel(glm::mat4 model) {
	unsigned int modelLocation = glGetUniformLocation(GetShader(), "model");
	glUseProgram(GetShader());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void Renderer::BindBufferShape(unsigned int vbo, bool useTexture) {
	
	unsigned int countElementsForVertex = 8;
	
	if (useTexture) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);
		glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
		glVertexAttribPointer(_textureAttribShape, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(_textureAttribShape);
	}
	else 
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);
		glVertexAttribPointer(_colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
	}
}

void Renderer::UnbindBuffer() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Renderer::BindBufferSprite(unsigned int vbo)
{
	unsigned int countElementsForVertex = 5;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_posAttribSprite, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttribSprite);
	glVertexAttribPointer(_textureAttribSprite, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_textureAttribSprite);
}

void Renderer::BeignDraw() {
	glClearColor(0.0f, 1.0, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawShape(unsigned int figura, int vertexs, unsigned int vbo, unsigned int& shaderProg, glm::mat4 model, bool useTexture)
{
	BindBufferShape(vbo, useTexture);

	UseProgram(shaderProg, model,_MVP.view, _MVP.projection);

	//shape->BindTexture();

	glDrawArrays(figura, 0, vertexs);

	UnbindBuffer();
}

void Renderer::DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, unsigned int & shaderProg, glm::mat4 model)
{
	BindBufferSprite(vbo);

	UseProgram(shaderProg, model, _MVP.view, _MVP.projection);

	glDrawArrays(figura, 0, vertexs);

	UnbindBuffer();
}

void Renderer::EndDraw(Windows* refWindow) {
	ClearShader();
	refWindow->SwapBuffersWindows();
	//std::cin.get();
}

unsigned int Renderer::CompileShader(unsigned int type, const char* source) {
	unsigned int id = glCreateShader(type);
	std::string shaderSourceCode;
	std::ifstream shaderSourceFile;

	shaderSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderSourceFile.open(source);
		std::stringstream sourceShaderStream;

		sourceShaderStream << shaderSourceFile.rdbuf();

		shaderSourceFile.close();

		shaderSourceCode = sourceShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPEN" << std::endl;
	}

	const char* sourceCode = shaderSourceCode.c_str();

	glShaderSource(id, 1, &sourceCode, nullptr);
	glCompileShader(id);

	return id;
}

int Renderer::CreateShaderProgram(const char* vertexShader, const char* fragmentShader)
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
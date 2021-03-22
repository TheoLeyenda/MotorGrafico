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
}
Renderer::~Renderer() {
	_shaderColor.deleteShader();
	_shaderTexture.deleteShader();
}

Shader& Renderer::GetShaderColor()
{
	return _shaderColor;
}
Shader& Renderer::GetShaderTexture()
{
	return _shaderTexture;
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
		_posAttribShape = glGetAttribLocation(_shaderTexture.getId(), "position");
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);

		_colorAttrib = glGetAttribLocation(_shaderTexture.getId(), "customColor");
		glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);

		glUniform1i(_textureAttribShape = glGetUniformLocation(_shaderTexture.getId(), "ourTexture"), 0);
		glVertexAttribPointer(_textureAttribShape, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(_textureAttribShape);
	}
	else if (typeMaterial == typeMaterialColor) //COLOR
	{
		_posAttribShape = glGetAttribLocation(_shaderColor.getId(), "position");
		glVertexAttribPointer(_posAttribShape, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		glEnableVertexAttribArray(_posAttribShape);
		_colorAttrib = glGetAttribLocation(_shaderColor.getId(), "customColor");
		glVertexAttribPointer(_colorAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(_colorAttrib);
	}
}

void Renderer::SetAttribsSprite()
{
	int countElementsForVertex = 5;

	_posAttribSprite = glGetAttribLocation(_shaderTexture.getId(), "position");
	glVertexAttribPointer(_posAttribSprite, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttribSprite);
	//_colorAttrib = glGetAttribLocation(_shaderProgram, "customColor");
	//glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(_colorAttrib);
	glUniform1i(_textureAttribSprite = glGetUniformLocation(_shaderTexture.getId(), "ourTexture"), 0);
	glVertexAttribPointer(_textureAttribSprite, 2, GL_FLOAT, GL_FALSE, countElementsForVertex * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_textureAttribSprite);
}

void Renderer::SetShader()
{
	if (typeCompilation == TypeCompilation::Debug) 
	{
		_shaderColor.CreateShader("../Motor/res/shaders/Vertex.shader", "../Motor/res/shaders/FragmentColor.shader");
		_shaderTexture.CreateShader("../Motor/res/shaders/Vertex.shader", "../Motor/res/shaders/FragmentTexture.shader");
	}
	else if (typeCompilation == TypeCompilation::Exe) 
	{
		_shaderColor.CreateShader("res/shaders/Vertex.shader", "res/shaders/FragmentColor.shader");
		_shaderTexture.CreateShader("res/shaders/Vertex.shader", "res/shaders/FragmentTexture.shader");
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

/*
void Renderer::UseProgram(unsigned int& shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

	unsigned int modelLocation = glGetUniformLocation(shader, "model");
	unsigned int viewLocation = glGetUniformLocation(shader, "view");
	unsigned int projectionLocation = glGetUniformLocation(shader, "projection");

	glUseProgram(shader);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
*/

void Renderer::UseShaderEnt(Shader& shader, glm::mat4 model)
{
	unsigned int modelLocation = glGetUniformLocation(shader.getId(), "model");
	glUseProgram(shader.getId());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void Renderer::ClearShader() {
	glUseProgram(0);
}

/*
void Renderer::UpdateModel(glm::mat4 model) {
	unsigned int modelLocation = glGetUniformLocation(GetShaderColor(), "model");
	glUseProgram(GetShaderColor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

*/
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

void Renderer::SetView()
{
	_MVP.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::SetView(glm::vec3 posCamera)
{
	_MVP.view = glm::lookAt(posCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::SetProjection()
{
	_MVP.projection = glm::ortho(0.0f, 1080.0f, 0.0f, 680.0f, 0.1f, 1000.0f);
	//                               FOV              Aspect      near  front
	//projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Renderer::drawCamera(Shader& shader)
{
	unsigned int transformLoc = glGetUniformLocation(shader.getId(), "model");
	unsigned int projectionLoc = glGetUniformLocation(shader.getId(), "projection");
	unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");
	glUseProgram(shader.getId());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_MVP.projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_MVP.view));
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
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawShape(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model, bool useTexture)
{
	BindBufferShape(vbo, useTexture);

	UseShaderEnt(shaderProg, model);

	glDrawArrays(figura, 0, vertexs);

	UnbindBuffer();
}

void Renderer::DrawSprite(unsigned int figura, int vertexs, unsigned int vbo, Shader& shaderProg, glm::mat4 model)
{
	BindBufferSprite(vbo);

	UseShaderEnt(shaderProg, model);

	glDrawArrays(figura, 0, vertexs);

	UnbindBuffer();
}

void Renderer::EndDraw(Windows* refWindow) {
	ClearShader();
	refWindow->SwapBuffersWindows();
}
#include "Renderer.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include "CompilationController.h"

#include "Camera.h"
#include "Light.h"
#include "Material.h"
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

void Renderer::BindBufferModel(unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt, unsigned int normalAtt, unsigned int uvAtt)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glVertexAttribPointer(posAtt, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), 0);
	glEnableVertexAttribArray(posAtt);
	glVertexAttribPointer(colAtt, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colAtt);
	glVertexAttribPointer(normalAtt, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(normalAtt);
	glVertexAttribPointer(uvAtt, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(uvAtt);
}

void Renderer::BindBufferLight(unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glVertexAttribPointer(posAtt, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(posAtt);
	glVertexAttribPointer(colAtt, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colAtt);
}

void Renderer::UnbindBuffer() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	ClearShader();
}

void Renderer::SetView(Camera * _camera)
{
	_MVP.view = _camera->CalculateViewMatrix();
}

void Renderer::SetProjectionPerspective(float FOV, float aspect, float near, float front)
{
	 //                                      FOV          Aspect  near   front
	_MVP.projection = glm::perspective(glm::radians(FOV), aspect, near, front);
}

void Renderer::SetProjectionOrtho(float left, float right, float bottom, float top, float near, float front)
{
	_MVP.projection = glm::ortho(left, right, bottom, top, near, front);
}

//void Renderer::SetLighting(Light * _light)
//{
//	if (_light != NULL) 
//	{
//
//#pragma region TYPES LIGHT
//		//_light->SetUniformTypeLightDirectional(GetShaderColor(),0);
//		//_light->SetUniformTypeLightPoint(GetShaderColor());
//		//_light->SetUniformTypeLightSpot(GetShaderColor());
//#pragma endregion
//
//#pragma region DIRECTIONAL LIGHT
//		_light->SetUniformDirectionLightLocation(GetShaderColor(), 0);
//		_light->SetUniformAmbDirectionalLoc(GetShaderColor(), 0);
//		_light->SetUniformDiffDirectionalLoc(GetShaderColor(), 0);
//		_light->SetUniformSpecDirectionalLoc(GetShaderColor(), 0);
//#pragma endregion
//
//#pragma region POINT LIGHT
//		_light->SetUniformQuadraticPointLight(GetShaderColor());
//		_light->SetUniformLinearPointLight(GetShaderColor());
//		_light->SetUniformConstPointLight(GetShaderColor());
//#pragma endregion
//
//#pragma region SPOT LIGHT
//		_light->SetUniformOuterCutOffSopttLight(GetShaderColor());
//		_light->SetUniformCutOffSopttLight(GetShaderColor());
//#pragma endregion
//
//#pragma region BASIC LIGHTING (POS LIGHT)
//		_light->SetUniformPosCameraLocation(GetShaderColor());
//		_light->SetUniformColourLocation(GetShaderColor());
//		_light->SetUniformPosLightLocation(GetShaderColor());
//#pragma endregion
//	}
//}

void Renderer::SetLighting(Light * _light, int iteration)
{
	if (_light != NULL)
	{

#pragma region TYPES LIGHT
		//_light->SetUniformTypeLightDirectional(GetShaderColor(), iteration);
		//_light->SetUniformTypeLightPoint(GetShaderColor());
		//_light->SetUniformTypeLightSpot(GetShaderColor());
#pragma endregion

#pragma region DIRECTIONAL LIGHT
		_light->SetUniformDirectionLightLocation(GetShaderColor(), iteration);
		_light->SetUniformAmbDirectionalLoc(GetShaderColor(), iteration);
		_light->SetUniformDiffDirectionalLoc(GetShaderColor(),iteration);
		_light->SetUniformSpecDirectionalLoc(GetShaderColor(),iteration);
#pragma endregion

#pragma region POINT LIGHT
		_light->SetUniformPosLightPoint(GetShaderColor(), iteration);
		_light->SetUniformQuadraticPointLight(GetShaderColor(), iteration);
		_light->SetUniformLinearPointLight(GetShaderColor(), iteration);
		_light->SetUniformConstPointLight(GetShaderColor(), iteration);
		_light->SetUniformAmbientPointLoc(GetShaderColor(), iteration);
		_light->SetUniformDiffPointLoc(GetShaderColor(), iteration);
		_light->SetUniformSpecPointLoc(GetShaderColor(), iteration);
#pragma endregion

#pragma region SPOT LIGHT
		_light->SetUniformPosLightSpot(GetShaderColor(), iteration);
		_light->SetUniformOuterCutOffSopttLight(GetShaderColor(), iteration);
		_light->SetUniformCutOffSopttLight(GetShaderColor(), iteration);
		_light->SetUniformLinearSpotLight(GetShaderColor(), iteration);
		_light->SetUniformQuadraticSpotLight(GetShaderColor(), iteration);
		_light->SetUniformConstSpotLight(GetShaderColor(), iteration);
		_light->SetUniformAmbientSpotLoc(GetShaderColor(), iteration);
		_light->SetUniformDiffSpotLoc(GetShaderColor(), iteration);
		_light->SetUniformSpecSpotLoc(GetShaderColor(), iteration);
		_light->SetUniformSpotLightDirection(GetShaderColor(), iteration);
#pragma endregion

#pragma region BASIC LIGHTING (POS LIGHT)
		_light->SetUniformPosCameraLocation(GetShaderColor());
		_light->SetUniformColourLocation(GetShaderColor());
		//_light->SetUniformPosLightLocation(GetShaderColor());
#pragma endregion
	}
}

void Renderer::LightingInfluence(Light * _light, Camera* camera)
{
	if (_light != NULL)
	{
		_light->UseLight(camera);
	}
}

void Renderer::DrawMeshes(std::vector<unsigned int> indices, Shader & shaderProg, glm::mat4 model, unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int nomAtt, unsigned int texAtt)
{
	UseShaderEnt(shaderProg, model);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	UnbindBuffer();
}

void Renderer::LocateModel(Shader & shaderProg, glm::mat4 model, unsigned int vbo, unsigned int posAtt)
{
	UseShaderEnt(shaderProg, model);
}

void Renderer::SetMaterial(Material * _material)
{
	if (_material != NULL) 
	{
		_material->SetUniformAmbientMatLocation(GetShaderColor());
		_material->SetUniformDiffuseMatLocation(GetShaderColor());
		_material->SetUniformSpecularMatLocation(GetShaderColor());
		_material->SetUniformShininessLocation(GetShaderColor());
	}
}

void Renderer::drawCamera(Shader& shader, glm::mat4 trsCamera)
{
	unsigned int transformLoc = glGetUniformLocation(shader.getId(), "model");
	unsigned int projectionLoc = glGetUniformLocation(shader.getId(), "projection");
	unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");
	glUseProgram(shader.getId());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trsCamera));
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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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

void Renderer::DrawModel(int indices,Shader& shaderProg, glm::mat4 model, 
	unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt, unsigned int normalAtt, unsigned int uvAtt)
{
	BindBufferModel(vbo, ibo, posAtt, colAtt, normalAtt, uvAtt);

	UseShaderEnt(shaderProg, model);

	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);

	UnbindBuffer();
}

void Renderer::DrawLight(int indices, Shader & shaderProg, glm::mat4 model, unsigned int vbo, unsigned int ibo, unsigned int posAtt, unsigned int colAtt)
{
	BindBufferLight(vbo, ibo, posAtt, colAtt);

	UseShaderEnt(shaderProg, model);

	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);

	UnbindBuffer();
}

void Renderer::EndDraw(Windows* refWindow) {
	ClearShader();
	refWindow->SwapBuffersWindows();
}
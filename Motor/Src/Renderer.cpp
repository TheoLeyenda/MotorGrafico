#include "Renderer.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include <iostream>

Renderer::Renderer() {
	//Nada
}
Renderer::~Renderer() {
	DeleteShaders();
}

void Renderer::GLEWInit(){
	glewExperimental = GL_TRUE;
	glewInit();
}
void Renderer::CreateVbo(float* _vertexBuffer){
	/*GLfloat _vertexBuffer[] = {
		-0.5f , -0.5f , 0.0f , 0.0f ,1.0f,
		 0.5f , -0.5f , 0.0f , 0.0f ,1.0f,
		 0.0f ,  0.5f , 0.0f , 0.0f, 1.0f
	};*/

	int tam = 0;
	while (_vertexBuffer[tam] <= 1 && _vertexBuffer[tam] >= -1){
		tam++;
	}
	std::cout << tam << std::endl;
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, tam * sizeof(float), _vertexBuffer, GL_STATIC_DRAW);
}
void Renderer::DeleteShaders() {
	glDeleteProgram(_shaderProgram);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	glDeleteBuffers(1, &_vbo);
}
GLuint Renderer::CreateVertexShader() {
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
		return vertexShader;
}
GLuint Renderer::CreateFragmentShader() {
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
		return fragmentShader;
}
void Renderer::CreateShaderProgram() {
	unsigned int vertex;
	unsigned int fragment;
	
	vertex = CreateVertexShader();
	fragment = CreateFragmentShader();
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	unsigned int posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);
	unsigned int colorAttrib = glGetAttribLocation(shaderProgram, "customColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);
}
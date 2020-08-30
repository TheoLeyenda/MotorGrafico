#include "Renderer.h"
#include "vertexShader.h"
#include "fragmentShader.h"

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
void Renderer::CreateVbo(){
	GLfloat _vertexBuffer[] = {
		-0.5f , -0.5f , 0.0f , 0.0f ,1.0f,
		 0.5f , -0.5f , 0.0f , 0.0f ,1.0f,
		 0.0f ,  0.5f , 0.0f , 0.0f, 1.0f
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexBuffer), _vertexBuffer, GL_STATIC_DRAW);
}
void Renderer::DeleteShaders() {
	glDeleteProgram(_shaderProgram);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	glDeleteBuffers(1, &_vbo);
}
GLuint Renderer::CreateVertexShader() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
		return vertexShader;
}
GLuint Renderer::CreateFragmentShader() {
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
		return fragmentShader;
}
void Renderer::CreateShaderProgram() {
	GLuint vertex;
	GLuint fragment;
	
	vertex = CreateVertexShader();
	fragment = CreateFragmentShader();
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);
	GLuint colorAttrib = glGetAttribLocation(shaderProgram, "customColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);
}
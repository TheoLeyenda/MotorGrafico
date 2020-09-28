#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

std::string vertexShader =
	"#version 330 core\n"
	"\n"
	"in vec4 position;\n"
	"in vec4 customColor;\n"
	"out vec4 color;\n"
	"uniform mat4 model;\n"
	//"uniform mat4 view;\n"
	//"uniform mat4 projection;\n"
	"void main()"
	"{"
	//"	gl_Position = projection * view * model * vec4(position,1.0); \n"
	"	gl_Position = model * vec4(position); \n"
	"	color = customColor;\n"
	"}\n"
	;
/*
const GLchar* vertexSource = R"glsl(
	#version 150 core
	
	in vec4 position;
	
	in vec3 customColor;
	out vec3 color;
	
	void main()
	{
		color = customColor;
		gl_Position = position;
	}

)glsl";
*/
#endif // !VERTEXSHADER_H
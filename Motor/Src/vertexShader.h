#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

std::string vertexShader =
	"#version 330 core\n"
	"\n"
	"in vec4 position;"
	"\n"
	"in vec3 customColor;\n"
	"out vec3 color;"
	"void main()"
	"{"
	"	color = customColor;"
	"	gl_Position = position;"
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
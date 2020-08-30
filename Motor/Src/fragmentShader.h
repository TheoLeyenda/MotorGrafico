#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include <glew.h>
#include <GLFW/glfw3.h>

const GLchar* fragmentSource = R"glsl(
	#version 150 core
	
	in vec3 color;
	out vec4 outColor;
	
	void main()
	{
	outColor = vec4(color, 1.0);
	}
)glsl";
#endif // !FRAGMENTSHADER_H
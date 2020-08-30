#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glew.h>
#include <GLFW/glfw3.h>

const GLchar* vertexSource = R"glsl(
	#version 150 core
	
	in vec2 position;
	
	in vec3 customColor;
	out vec3 color;
	
	void main()
	{
		color = customColor;
		gl_Position = vec4(position,0.0, 1.0);
	}
)glsl";
#endif // !VERTEXSHADER_H
#version 330 core

in vec4 position;
in vec4 customColor;
out vec4 color;
uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
void main()
{
//	gl_Position = projection * view * model * vec4(position,1.0); 
	gl_Position = model * vec4(position); 
	color = customColor;
}
;
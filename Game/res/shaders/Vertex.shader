#version 330 core

in vec3 position;
in vec4 customColor;
out vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec2 m_TexCoord;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(position,1.0); 
	//gl_Position = model * vec4(position);
	color = customColor;
	texCoord = m_TexCoord;
};


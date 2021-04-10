#version 330 core

in vec3 position;
in vec4 customColor;
in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec2 m_TexCoord;
out vec2 texCoord;
out vec4 color;
out vec3 Normal;

out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0); 

	color = customColor;
	texCoord = m_TexCoord;

	Normal = mat3(transpose(inverse(model))) * norm;
	
	FragPos = (model * vec4(position, 1.0)).xyz;
};


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
	FragPos = vec3(model * vec4(position, 1.0));
	Normal = mat3(transpose(inverse(model))) * norm;

	color = customColor;
	texCoord = m_TexCoord;

	gl_Position = projection * view * vec4(FragPos, 1.0);
};


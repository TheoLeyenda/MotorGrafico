#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 m_TexCoord;

in vec4 customColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
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

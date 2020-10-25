#include "TextureImporter.h"
#include "glew.h"
#include "stb_image.h"
#include <iostream>

TextureImporter::TextureImporter(){}

TextureImporter::~TextureImporter(){}

void TextureImporter::LoadTexture(const char* filePath, unsigned char* data, int width, int height, int nrChannels)
{
	data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);
}

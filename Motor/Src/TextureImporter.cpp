#include "TextureImporter.h"
#include "glew.h"
#include "stb_image.h"
#include <iostream>

//===================================================
TextureImporter::TextureImporter(){}
//===================================================
TextureImporter::~TextureImporter(){}
//===================================================
void TextureImporter::LoadTexture(const char* filePath, unsigned char* data, int width, int height, int nrChannels)
{
	data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);
}
//===================================================
void TextureImporter::GenTexture(int countTexture, unsigned int& texture)
{
	stbi_set_flip_vertically_on_load(countTexture);
	glGenTextures(countTexture, &texture);
	glActiveTexture(GL_TEXTURE0);
}
//===================================================
void TextureImporter::SetParametrer()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
}
//===================================================
void TextureImporter::SetTexture(const char * filePath, unsigned char * data, int width, int heigth, int nrChannels)
{
	LoadTexture(filePath, data, width, heigth, nrChannels);
}
//===================================================
void TextureImporter::BindTexture(unsigned int& texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
//===================================================
void TextureImporter::GenerateTexture(const char * filePath, int countTexture, unsigned int& texture,
	unsigned char* data ,int width, int heigth, int nrChannels)
{
	GenTexture(countTexture , texture);
	BindTexture(texture);
	SetParametrer();
	SetTexture(filePath ,data ,width ,heigth ,nrChannels);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//===================================================
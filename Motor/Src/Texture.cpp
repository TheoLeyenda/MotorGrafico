#include "Texture.h"

#include <glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(const char* path)
{
	_path = path;
	_texData = 0;
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
	_channels = 0;
}

Texture::~Texture() 
{ 
	UnloadTexture();
}

bool Texture::LoadTexture(bool hasAlpha)
{
	return _myImporter.LoadTexture(_path, _texData, _textureID, _width, _height, _channels, hasAlpha);
}

bool Texture::LoadTexture(const char * path, bool hasAlpha)
{
	return _myImporter.LoadTexture(path, _texData, _textureID, _width, _height, _channels, hasAlpha);
}

void Texture::BindTexture()
{
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,_textureID);
}

void Texture::UnbindTexture()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Texture::UnloadTexture()
{
	glDeleteTextures(1, &_textureID);
	_path = " ";
	_texData = 0;
	_textureID = -1;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
	_channels = 0;
}
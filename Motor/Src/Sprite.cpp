#include "Sprite.h"
#include "glew.h"

//============================================
Sprite::Sprite(Renderer *_renderer, Material* _material, const char* filePath):Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);
}
//============================================
Sprite::Sprite(Renderer * _renderer, const char* filePath):Entity2D(_renderer)
{
	renderer = _renderer;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);
}
//============================================
Sprite::~Sprite() {
	glDeleteTextures(1, &texture);
}
//============================================
int Sprite::getWidth()
{
	return width;
}
//============================================
int Sprite::getHeigth()
{
	return height;
}
//============================================
int Sprite::getNrChannels()
{
	return nrChannels;
}
//============================================
void Sprite::BindSprite()
{
	textureImporter.BindTexture(texture);
}
//============================================
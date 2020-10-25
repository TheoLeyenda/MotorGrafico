#include "Sprite.h"
#include "glew.h"


Sprite::Sprite(Renderer *_renderer, Material* _material):Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
}

Sprite::Sprite(Renderer * _renderer):Entity2D(_renderer)
{
	renderer = _renderer;
}

Sprite::~Sprite() {
	glDeleteTextures(1, &texture);
}

void Sprite::GenerateTexture(const char* filePath)
{
	GenTexture();
	BindTexture();
	SetParametrer();
	SetTexture(filePath);
}

void Sprite::GenTexture() {
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
}

void Sprite::BindTexture() {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Sprite::SetParametrer() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
}

void Sprite::SetTexture(const char* filePath) {
	textureImporter.LoadTexture(filePath, data, width, height, nrChannels);
}

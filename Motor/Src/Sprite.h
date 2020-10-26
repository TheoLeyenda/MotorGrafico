#ifndef SPRITE_H
#define SPRITE_H
#include "Entity2D.h"
#include "TextureImporter.h"

class ENGINE_API Sprite : public Entity2D
{
private:
	unsigned int texture;
	unsigned char* data;
	int width;
	int height;
	int nrChannels;
	TextureImporter textureImporter;
public:
	Sprite(Renderer *_renderer, Material* _material, const char* filePath);
	Sprite(Renderer *_renderer, const char* filePath);
	~Sprite();
	int getWidth();
	int getHeigth();
	int getNrChannels();
	TextureImporter GetTextureImporter() { return textureImporter; }
	void BindSprite();
};
#endif
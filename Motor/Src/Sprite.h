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
private:
	void GenTexture();
	void SetParametrer();
	void SetTexture(const char* filePath);

public:
	Sprite(Renderer *_renderer, Material* _material);
	Sprite(Renderer *_renderer);
	~Sprite();
	void BindTexture();
	void GenerateTexture(const char* filePath);
};
#endif


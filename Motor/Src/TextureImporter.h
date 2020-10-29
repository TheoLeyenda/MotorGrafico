#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H
#include "PrivateClass/Export.h"

struct TextureVertex 
{
	float x;
	float y;
	float z;
	float u;
	float v;
};

class ENGINE_API TextureImporter
{
private:
	void GenTexture(int countTexture, unsigned int& texture);
	void SetParametrer();
	void SetTexture(const char* filePath,unsigned char* data,
		int width, int heigth, int nrChannels);

public:
	TextureImporter();
	~TextureImporter();
	void LoadTexture(const char* filePath,unsigned char* data,
		int width,int height, int nrChannels);
	
	void BindTexture(unsigned int& texture);
	void GenerateTexture(const char* filePath, int countTexture ,
		unsigned int& texture, unsigned char* data, int width, int heigth, int nrChannels);
};
#endif
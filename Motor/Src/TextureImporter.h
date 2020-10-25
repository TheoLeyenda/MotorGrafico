#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H
#include "PrivateClass/Export.h"
class ENGINE_API TextureImporter
{
public:
	TextureImporter();
	~TextureImporter();
	void LoadTexture(const char* filePath,unsigned char* data, int width,int height, int nrChannels);
};
#endif


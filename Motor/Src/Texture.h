#ifndef TEXTURE_H
#define TEXTURE_H

#include "PrivateClass/Export.h"
#include <iostream>
#include <string>

struct TextureData
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Texture
{
public:
	Texture();
	~Texture();
	TextureData data;
};
#endif // !TEXTURE_H
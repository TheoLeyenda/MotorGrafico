#ifndef IMPORTER_H
#define IMPORTER_H

#include "PrivateClass/Export.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ENGINE_API Importer
{
private:

	//Nodos
public:
	Importer();
	~Importer();
};
#endif // !IMPORTER_H
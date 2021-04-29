#ifndef MODEL_H
#define MODEL_H

#include "stb_image.h"
#include <fstream>
#include <sstream>
#include <map>
#include "mesh.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

class ENGINE_API Model
{
private:
	string directory;
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;

	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type,
		string typeName);
	void loadModel(string path);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

public:
	Model(const char * path);
	void Draw(Shader& shader);
};
#endif // !MODEL_H
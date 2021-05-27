#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
//#include <glad/glad.h> 

#include <glm/glm.hpp>
//#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

class Time;

class ENGINE_API Model : public Entity
{
public:
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	Model(string const &path,string const& _directory, bool gamma, Renderer* render);
	
	void Draw(Shader &shader);
	
	void MoveModel(glm::vec3 direction, float speed, Time* timer);
	void MoveModel(glm::vec3 direction, float speed, Time timer);

	void SetScaleModel(float x, float y, float z);

	void SetRotationModelX(float RotateX);
	void SetRotationModelY(float RotateY);
	void SetRotationModelZ(float RotateZ);

	void SetNewMaterial(Material* mat);
private:

	void CenterPivotPositionModel();
	unsigned int TextureFromFile(const char * path, const string & directory, bool gamma, string num);
	void LoadModel(string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);

	Material* my_Mat;
};

#endif

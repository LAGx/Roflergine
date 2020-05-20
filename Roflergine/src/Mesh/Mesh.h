#pragma once
#include <vector>
#include <GL/glew.h>
#include <filesystem>
#include "../Utils/Error.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>
#include "../Utils/System.h"


class Mesh {
public:

	Error loadFromFile(const std::filesystem::path&);

	void render();

	void reset();

	~Mesh();

private:

	void loadModel(const aiScene* scene);
	void loadNode(const aiNode* node, const aiScene* scene);
	void loadMesh(const aiMesh* mesh, const aiScene* scene);

	void loadAssimpMash(aiMesh* mesh);

	void glRegisterData();

	std::vector<GLfloat> vertexBuffer;
	std::vector<GLuint> indexBuffer;
	int lastIndexValue = 0;

	GLuint VAO = 0; //mode binding
	GLuint VBO = 0; //vertex array
	GLuint IBO = 0; //index array
};
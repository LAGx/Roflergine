#include "Mesh.h"
#include "../Utils/System.h"
#include <fstream>
#include <sstream>


Error Mesh::loadFromFile(const std::filesystem::path& path) {
	Assimp::Importer importer;

	auto scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
		return { {std::string() + "Model importing error: " + importer.GetErrorString(), ErrorCode::General} };

	
	loadModel(scene);

	glRegisterData();

	return std::nullopt;
}

void Mesh::loadModel(const aiScene* scene) {
	vertexBuffer.clear();
	indexBuffer.clear();
	lastIndexValue = 0;
	loadNode(scene->mRootNode, scene);
}

void Mesh::loadNode(const aiNode* node, const aiScene* scene) {
	for (size_t i = 0; i < node->mNumMeshes; i++)
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);

	for (size_t i = 0; i < node->mNumChildren; i++)
		loadNode(node->mChildren[i], scene);
}

void Mesh::loadMesh(const aiMesh* mesh, const aiScene* scene) {
	for (u64 i = 0; i < mesh->mNumVertices; ++i)
	{

		vertexBuffer.insert(vertexBuffer.end(), { (float)mesh->mVertices[i].x, (float)mesh->mVertices[i].z, (float)mesh->mVertices[i].y });
		if (mesh->mTextureCoords[0])
		{
			vertexBuffer.insert(vertexBuffer.end(), { (float)mesh->mTextureCoords[0][i].x, -(float)mesh->mTextureCoords[0][i].y });
		}
		else {
			vertexBuffer.insert(vertexBuffer.end(), { 0.0f, 0.0f });
		}
		vertexBuffer.insert(vertexBuffer.end(), { -(float)mesh->mNormals[i].x, -(float)mesh->mNormals[i].z, -(float)mesh->mNormals[i].y });
	}

	for (u64 f = 0; f < mesh->mNumFaces; ++f)
	{
		aiFace* face = &mesh->mFaces[f];
		for (u64 i = 0; i < face->mNumIndices; ++i)
		{
			indexBuffer.push_back(face->mIndices[i+ lastIndexValue]);
		}
	}
	lastIndexValue += mesh->mNumFaces;
}

void Mesh::glRegisterData(){

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VECTOR_SIZE_IN_BYTES(indexBuffer), indexBuffer.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VECTOR_SIZE_IN_BYTES(vertexBuffer), vertexBuffer.data(), GL_STATIC_DRAW);

	constexpr auto vertexSizeof = sizeof(decltype(vertexBuffer)::value_type);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSizeof * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSizeof * 8, reinterpret_cast<void*>(vertexSizeof * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexSizeof * 8, reinterpret_cast<void*>(vertexSizeof * 5));
	glEnableVertexAttribArray(2);

	//clear/unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::render()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_ZERO);
	glBindVertexArray(GL_ZERO);
}

void Mesh::reset()
{
	indexBuffer.clear();
	vertexBuffer.clear();
	lastIndexValue = 0;

	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);

	if (VBO != 0)
		glDeleteBuffers(1, &VBO);

	if (IBO != 0)
		glDeleteBuffers(1, &IBO);
}


Mesh::~Mesh()
{
	reset();
}

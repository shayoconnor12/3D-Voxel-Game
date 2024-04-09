#pragma once
#include "block.h"

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "texture.h"

#include <vector>

class chunk
{
public:
	unsigned int indexCount;
	std::vector<float> chunkVertices;
	std::vector<unsigned int> chunkIndices;
	std::vector<float> chunkPosition;

	chunk(std::vector<float> chunkPos);
	void renderChunk(shader& shaderProgram, renderer& rendererProgram);

	vertexArray chunkVAO;
	vertexBuffer chunkVBO;
	indexBuffer chunkIBO;
	vertexBufferLayout layout;

private:

	const unsigned int WIDTH = 16;
	const unsigned int HEIGHT = 32;

	float dx;
	float dy;
	float dz;

	void genBlocks(std::vector<std::vector<float>> heights);
	std::vector<std::vector<float>> genChunk();

	void setBuffers();
	void addIndices(unsigned int faceCount);

	void integrateFace(block& block, faces face);

};
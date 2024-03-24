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
	void renderChunk(shader shaderProgram, renderer rendererProgram);

private:
	void genBlocks();
	void addIndices(unsigned int faceCount);
};
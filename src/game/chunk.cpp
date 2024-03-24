#include "chunk.h"
#include <iostream>

chunk::chunk(std::vector<float> chunkPos)
{
	chunkPosition = chunkPos;

	genBlocks();
}

void chunk::genBlocks()
{
	unsigned int faceCount;
	for (int i = 0; i < 3; i++)
	{
		faceCount = 0;

		block generatedBlock({(float) i, 0.0, 0.0});

		//i know i can probably use a loop here i just think the code looks cool
		//also this is probably a lot more readable, and uses less memory than a loop would

		std::vector<float> frontFaceData	= generatedBlock.getFaceData(FRONT);
		std::vector<float> backFaceData		= generatedBlock.getFaceData(BACK);
		std::vector<float> rightFaceData	= generatedBlock.getFaceData(RIGHT);
		std::vector<float> leftFaceData		= generatedBlock.getFaceData(LEFT);
		std::vector<float> topFaceData		= generatedBlock.getFaceData(TOP);
		std::vector<float> bottomFaceData	= generatedBlock.getFaceData(BOTTOM);
		
		chunkVertices.insert(chunkVertices.end(), frontFaceData .begin(), frontFaceData .end());
		chunkVertices.insert(chunkVertices.end(), backFaceData	.begin(), backFaceData	.end());
		chunkVertices.insert(chunkVertices.end(), rightFaceData .begin(), rightFaceData .end());
		chunkVertices.insert(chunkVertices.end(), leftFaceData	.begin(), leftFaceData	.end());
		chunkVertices.insert(chunkVertices.end(), topFaceData	.begin(), topFaceData	.end());
		chunkVertices.insert(chunkVertices.end(), bottomFaceData.begin(), bottomFaceData.end());

		faceCount += 6;

		addIndices(faceCount);
	}
}

void chunk::renderChunk(shader shaderProgram, renderer rendererProgram)
{
	rendererProgram.Clear();

	vertexArray chunkVAO;
	vertexBuffer chunkVBO = vertexBuffer(chunkVertices);
	vertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	chunkVAO.addBuffer(chunkVBO, layout);

	indexBuffer chunkIBO = indexBuffer(chunkIndices, chunkIndices.size() * sizeof(unsigned int));
	rendererProgram.Clear();
	shaderProgram.Bind();
	chunkVAO.Bind();
	chunkIBO.Bind();
	rendererProgram.Draw(chunkVAO, chunkIBO, shaderProgram);
}

void chunk::addIndices(unsigned int faceCount)
{
	for (int i = 0; i < faceCount; i++)
	{
		chunkIndices.push_back(0 + indexCount);
		chunkIndices.push_back(1 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(3 + indexCount);
		chunkIndices.push_back(0 + indexCount);

		indexCount += 4;
	}
}

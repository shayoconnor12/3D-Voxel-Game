#include "chunk.h"
#include "../vendor/noise/FastNoiseLite.h"
#include <iostream>
#include <random>

chunk::chunk(std::vector<float> chunkPos)
{
	dx = chunkPos[0];
	dy = chunkPos[1];
	dz = chunkPos[2];


	std::vector<std::vector<float>> heightMap = genChunk();
	genBlocks(heightMap);
	setBuffers();
}

void chunk::renderChunk(shader& shaderProgram, renderer& rendererProgram)
{
	shaderProgram.Bind();
	chunkVAO.Bind();
	chunkIBO.Bind();
	rendererProgram.Draw(chunkVAO, chunkIBO, shaderProgram);
}

std::vector<std::vector<float>> chunk::genChunk()
{
	std::vector<std::vector<float>> heightMap(WIDTH, std::vector<float>(WIDTH));
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetSeed(38374);

	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < WIDTH; z++)
		{
			heightMap[x][z] = noise.GetNoise((float)x, (float)z);
		}
	}
	return heightMap;
}

void chunk::genBlocks(std::vector<std::vector<float>> heights)
{
	std::vector<std::vector<std::vector<block>>> chunkBlocks(WIDTH, std::vector<std::vector<block>>(HEIGHT, std::vector<block>(WIDTH, block({ 0.0f,0.0f,0.0f }))));

	unsigned int faceCount;
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < WIDTH; z++)
		{
			int columnHeight = (int)(heights[x][z] * 10);
			//std::cout << "COLUMN HEIGHT AT " << x << "," << z << " = " << columnHeight << std::endl;
			for (int y = 0; y < columnHeight; y++)
			{
				faceCount = 0;

				block generatedBlock({ (float)x + dx, (float)y + dy, (float)z + dz }, GRASS);

				integrateFace(generatedBlock, FRONT);
				integrateFace(generatedBlock, BACK);
				integrateFace(generatedBlock, RIGHT);
				integrateFace(generatedBlock, LEFT);
				integrateFace(generatedBlock, TOP);
				integrateFace(generatedBlock, BOTTOM);

				faceCount += 6;

				addIndices(faceCount);
			}
		}
	}
}


void chunk::integrateFace(block& block, faces face)
{
	std::vector<float> faceData = block.getFaceData(face);
	chunkVertices.insert(chunkVertices.end(), faceData.begin(), faceData.end());
}

void chunk::setBuffers()
{
	chunkVBO.setVertexBuffer(chunkVertices);
	layout.Push<float>(3);
	layout.Push<float>(2);
	chunkVAO.addBuffer(chunkVBO, layout);
	chunkIBO.setIndexBuffer(chunkIndices, chunkIndices.size() * sizeof(unsigned int));
	std::cout << "HELLO" << std::endl;
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

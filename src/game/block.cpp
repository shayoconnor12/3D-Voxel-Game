#include "block.h"
#include <iostream>
#include <map>

block::block(std::vector<float> pos, blockName blockType)
{
    if (blockType != AIR)
    {
        position = pos;

        std::map<unsigned int, int> topFaceOffsets = {
            {14, 1} //GRASS BLOCK
        };
        std::map<unsigned int, int> bottomFaceOffsets = {
            {14, -1} //GRASS BLOCK
        };

        std::map<blockName, int> blockTypeIndex = {
            {GRASS, 14},
            {DIRT, 13},
            {COBBLE, 12},
        };

        unsigned int blockIndex = blockTypeIndex[blockType];

        int x_coordinate = blockIndex % 16;
        int y_coordinate = blockIndex / 16;

        float uMin = static_cast<float>(x_coordinate) / 16;
        float vMin = 1.0 - static_cast<float>(y_coordinate) / 16;

        float uvScale = 1.0f / 16.0f;

        float uMax = uMin + uvScale;
        float vMax = vMin - uvScale;

        int topOffset = 0;
        int bottomOffset = 0;

        if (topFaceOffsets.find(blockIndex) != topFaceOffsets.end()) {
            topOffset = topFaceOffsets[blockIndex];
        }
        if (bottomFaceOffsets.find(blockIndex) != bottomFaceOffsets.end()) {
            bottomOffset = bottomFaceOffsets[blockIndex];
        }

        float uvTO = static_cast<float>(topOffset) / 16;
        float uvBO = static_cast<float>(bottomOffset) / 16;

        rawVertexData =
        {
            { FRONT,
                {
                    -0.5f, -0.5f,  0.5f,  uMin, vMin,   // Bottom-left
                     0.5f, -0.5f,  0.5f,  uMax, vMin,   // Bottom-right
                     0.5f,  0.5f,  0.5f,  uMax, vMax,   // Top-right
                    -0.5f,  0.5f,  0.5f,  uMin, vMax    // Top-left
                }
            },
            { BACK,
                {
                    -0.5f, -0.5f, -0.5f,  uMin, vMin,   // Bottom-left
                     0.5f, -0.5f, -0.5f,  uMax, vMin,   // Bottom-right
                     0.5f,  0.5f, -0.5f,  uMax, vMax,   // Top-right
                    -0.5f,  0.5f, -0.5f,  uMin, vMax    // Top-left
                }
            },
            { RIGHT,
                {
                     0.5f, -0.5f,  0.5f,  uMin, vMin,   // Bottom-left
                     0.5f, -0.5f, -0.5f,  uMax, vMin,   // Bottom-right
                     0.5f,  0.5f, -0.5f,  uMax, vMax,   // Top-right
                     0.5f,  0.5f,  0.5f,  uMin, vMax    // Top-left
                }
            },
            { LEFT,
                {
                    -0.5f, -0.5f, -0.5f,  uMin, vMin,   // Bottom-left
                    -0.5f, -0.5f,  0.5f,  uMax, vMin,   // Bottom-right
                    -0.5f,  0.5f,  0.5f,  uMax, vMax,   // Top-right
                    -0.5f,  0.5f, -0.5f,  uMin, vMax    // Top-left
                }
            },
            { TOP,
                {
                    -0.5f,  0.5f,  0.5f,  uMin + uvTO, vMin,   // Bottom-left
                     0.5f,  0.5f,  0.5f,  uMax + uvTO, vMin,   // Bottom-right
                     0.5f,  0.5f, -0.5f,  uMax + uvTO, vMax,   // Top-right
                    -0.5f,  0.5f, -0.5f,  uMin + uvTO, vMax    // Top-left
                }
            },
            { BOTTOM,
                {
                    -0.5f, -0.5f, -0.5f,  uMin + uvBO, vMin,   // Bottom-left
                     0.5f, -0.5f, -0.5f,  uMax + uvBO, vMin,   // Bottom-right
                     0.5f, -0.5f,  0.5f,  uMax + uvBO, vMax,   // Top-right
                    -0.5f, -0.5f,  0.5f,  uMin + uvBO, vMax    // Top-left
                }
            }
        };

        faceMap =
        {
            {FRONT , transformVertices(rawVertexData[FRONT])},
            {BACK  , transformVertices(rawVertexData[BACK])},
            {RIGHT , transformVertices(rawVertexData[RIGHT])},
            {LEFT  , transformVertices(rawVertexData[LEFT])},
            {TOP   , transformVertices(rawVertexData[TOP])},
            {BOTTOM, transformVertices(rawVertexData[BOTTOM])},
        };
    }
}

std::vector<float> block::transformVertices(std::vector<float> vertices)
{
	float dx = position[0];
	float dy = position[1];
	float dz = position[2];

	for (int i = 0; i < vertices.size(); i += 5) {
		// Update position coordinates
		vertices[i]		+= dx;
		vertices[i + 1] += dy;
		vertices[i + 2] += dz;
	}
	return vertices;
}

std::vector<float> block::getFaceData(faces face)
{
	return faceMap[face];
}



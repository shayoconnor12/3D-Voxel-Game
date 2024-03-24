#include "block.h"

block::block(std::vector<float> pos)
{
	position = pos;
	rawVertexData =
	{
		{				 FRONT,
		{
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left
		} },
		{				 BACK,
		{
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
		} },
		{				 RIGHT,
		{
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left
		} },
		{				 LEFT,
		{
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
		} },
		{				 TOP,
		{
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
		} },
		{				BOTTOM,
		{
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f  // Top-left
		} }
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



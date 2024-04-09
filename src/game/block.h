#pragma once
#include <vector>
#include <map>

enum blockName
{
	GRASS,
	DIRT,
	COBBLE,
	AIR,
};

enum faces
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};

class block
{
private:
	std::vector<float> position;
	std::vector<float> transformVertices(std::vector<float> vertices);
	std::map<faces, std::vector<float>> rawVertexData;
	std::map<faces, std::vector<float>> faceMap;


public:
	block(std::vector<float> pos, blockName blockType = AIR);
	std::vector<float> getFaceData(faces face);
};
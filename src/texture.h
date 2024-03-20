#pragma once
#include "renderer.h"

class texture
{

private:
	int atlasDimension;
	unsigned int mRendererID;
	std::string mFilePath;
	unsigned char* mLocalBuffer;
	int mWidth, mHeight, mBPP;

public:
	texture(const std::string& path);
	~texture();

	void Bind(unsigned int slot = 0) const;
	void unBind() const;

	int getAtlasDimension();
	float getTextureXOffset(int textureIndex);
	float getTextureYOffset(int textureIndex);


	inline int getWidth() const { return mWidth; }
	inline int getHeight() const { return mHeight; }

};
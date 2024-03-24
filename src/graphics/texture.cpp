#include "texture.h"
#include "../vendor/stbImage/stbImage.h"
#include <iostream>

texture::texture(const std::string& path)
:	mRendererID(0), 
	mFilePath(path),
	mLocalBuffer(nullptr), 
	mWidth(0), mHeight(0), 
	mBPP(0),
	atlasDimension(16)
{
	stbi_set_flip_vertically_on_load(0);
	mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

	glGenTextures(1, &mRendererID);
	glBindTexture(GL_TEXTURE_2D, mRendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (mLocalBuffer) stbi_image_free(mLocalBuffer);
}

int texture::getAtlasDimension()
{
	return atlasDimension;
}

float texture::getTextureXOffset(int textureIndex)
{
	float column = textureIndex % atlasDimension;
	std::cout << "COLUMN: " << column << std::endl;
	float xOffset = column / atlasDimension;

	return xOffset;
}

float texture::getTextureYOffset(int textureIndex)
{
	float row = textureIndex / atlasDimension;
	std::cout << "ROW: " << row << std::endl;
	float yOffset = row / atlasDimension;

	return yOffset;
}

texture::~texture()
{
	glDeleteTextures(1, &mRendererID);
}

void texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void texture::unBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

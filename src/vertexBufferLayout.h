#pragma once
#include <vector>
#include <assert.h>
#include <GL/glew.h>
#include "renderer.h"

struct vertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalised;
	
	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class vertexBufferLayout
{
private:
	std::vector<vertexBufferElement> mElements;
	unsigned int mStride;
public:
	vertexBufferLayout()
		:mStride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		mElements.push_back({ GL_FLOAT, count, GL_FALSE });
		mStride += vertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		mStride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		mStride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<vertexBufferElement> getElements() const { return mElements; }
	inline unsigned int getStride() const { return mStride; }

};
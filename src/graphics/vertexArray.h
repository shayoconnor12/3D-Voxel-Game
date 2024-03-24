#pragma once

#include "vertexBuffer.h"

class vertexBufferLayout;

class vertexArray
{
private:
	unsigned int mRendererID;
public:
	vertexArray();
	~vertexArray();

	void addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout);

	void Bind() const;
	void unBind() const;
};
#include "vertexArray.h"
#include "renderer.h"
#include "vertexBufferLayout.h"
#include <iostream>

vertexArray::vertexArray()
{
	glGenVertexArrays(1, &mRendererID);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &mRendererID);
}

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void*) offset);
		std::cout << layout.getStride() << std::endl;
		offset += element.count * vertexBufferElement::getSizeOfType(element.type);
	}
}

void vertexArray::Bind() const
{
	glBindVertexArray(mRendererID);
}

void vertexArray::unBind() const
{
	glBindVertexArray(0);
}

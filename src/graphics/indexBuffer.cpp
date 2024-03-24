#include "indexBuffer.h"
#include "renderer.h"

indexBuffer::indexBuffer(const std::vector<unsigned int>& data, unsigned int count)
    :mCount(static_cast<unsigned int>(data.size())) 
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
}

indexBuffer::~indexBuffer()
{
    glDeleteBuffers(1, &mRendererID);
}

void indexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void indexBuffer::unBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

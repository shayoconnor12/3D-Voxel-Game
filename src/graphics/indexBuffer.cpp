#include "indexBuffer.h"
#include "renderer.h"

void indexBuffer::setIndexBuffer(const std::vector<unsigned int>& data, unsigned int count)
{
    mCount = static_cast<unsigned int>(data.size());
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
}

indexBuffer::indexBuffer()
{
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

#include "vertexBuffer.h"
#include "renderer.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertexBuffer::~vertexBuffer()
{
    glDeleteBuffers(1, &mRendererID);
}

void vertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void vertexBuffer::unBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

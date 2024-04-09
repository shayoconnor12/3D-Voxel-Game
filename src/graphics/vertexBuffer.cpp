#include "vertexBuffer.h"
#include "renderer.h"

void vertexBuffer::setVertexBuffer(const std::vector<float>& vertices) 
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

vertexBuffer::vertexBuffer()
{
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

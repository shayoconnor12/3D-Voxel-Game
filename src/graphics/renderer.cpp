#include "renderer.h"
#include <iostream>

void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout   << "---------------------------------------"<< "\n"
                    << "[OPENGL ERROR] ("   << error << ")"     << "\n"
                    << "FUNC CALL "         << function         << "\n"
                    << "IN FILE "           << file             << "\n"
                    << "ON LINE "           << line             << "\n"
                    << "---------------------------------------"<< std::endl;
        return false;
    }
    return true;
}

void renderer::Clear() const
{
    /* Render here */
    glClearColor(0.5f, 0.65f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::Draw(const vertexArray& vArray, const indexBuffer& iBuffer, const shader& shader) const
{
    shader.Bind();
    vArray.Bind();
    iBuffer.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, iBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}

#pragma once

#include <GL/glew.h>
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"


#define ASSERT(x) if (!(x)) __debugbreak();

#define DEBUG
#ifdef DEBUG
#define GLCALL(x) glClearError(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__))
#else
#define GLCALL(x) x
#endif

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

class renderer
{
public:
	void Clear() const;
	void Draw(const vertexArray& va, const indexBuffer& ib, const shader& shader) const;

private:

};

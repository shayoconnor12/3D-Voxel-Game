#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class vertexBuffer
{
	private:
		unsigned int mRendererID;
	public:

		vertexBuffer();

		void setVertexBuffer(const std::vector<float>& vertices);

		~vertexBuffer();

		void Bind() const;
		void unBind() const;
};
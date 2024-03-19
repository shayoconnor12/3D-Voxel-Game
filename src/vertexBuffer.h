#pragma once

class vertexBuffer
{
	private:
		unsigned int mRendererID;
	public:
		vertexBuffer(const void* data, unsigned int size);
		~vertexBuffer();

		void Bind() const;
		void unBind() const;
};
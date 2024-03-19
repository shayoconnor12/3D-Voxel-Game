#pragma once

class indexBuffer
{
	private:
		unsigned int mRendererID;
		unsigned int mCount;
	public:
		indexBuffer(const unsigned int* data, unsigned int count);
		~indexBuffer();

		void Bind() const;
		void unBind() const;

		inline unsigned int GetCount() const { return mCount; }
};
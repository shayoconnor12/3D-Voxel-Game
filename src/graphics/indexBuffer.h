#pragma once
#include <vector>

class indexBuffer
{
	private:
		unsigned int mRendererID;
		unsigned int mCount;
	public:
		indexBuffer(const std::vector<unsigned int>& data, unsigned int count);
		~indexBuffer();

		void Bind() const;
		void unBind() const;

		inline unsigned int GetCount() const { return mCount; }
};
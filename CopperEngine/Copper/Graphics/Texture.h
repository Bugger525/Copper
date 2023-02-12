#pragma once

#include <string>

namespace cu
{
	class Texture
	{
	private:
		unsigned int m_Data;

		unsigned int m_Width;
		unsigned int m_Height;
	public:
		Texture();
		~Texture();

		bool LoadFromFile(std::string_view filePath);
		bool LoadFromData(unsigned int width, unsigned int height, unsigned char* const data);
		void Use() const;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		void Cleanup();
	};
}
#include "Texture.h"
#include "../System/Debug.h"
#include <GL/gl3w.h>

namespace cu
{
	Texture::Texture()
		: m_Data(NULL), m_Width(0), m_Height(0)
	{
	}
	Texture::Texture(unsigned int width, unsigned int height, std::span<unsigned char> image) : m_Data(NULL), m_Width(width), m_Height(height)
	{
		m_Image.assign(image.begin(), image.end());

		glBindTexture(GL_TEXTURE_2D, m_Data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Texture::~Texture()
	{
		Cleanup();
	}
	void Texture::Use() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Data);
	}
	unsigned int Texture::GetWidth() const
	{
		return m_Width;
	}
	unsigned int Texture::GetHeight() const
	{
		return m_Height;
	}
	const std::vector<unsigned char>& Texture::GetImage() const
	{
		return m_Image;
	}
	void Texture::Cleanup()
	{
		if (m_Data)
			glDeleteTextures(1, &m_Data);
	}
}
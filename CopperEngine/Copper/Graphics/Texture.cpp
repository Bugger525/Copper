#include "Texture.h"
#include "../System/Debug.h"
#include <GL/gl3w.h>

namespace Copper
{
	Texture::Texture() : m_Data(NULL)
	{
	}
	Texture::Texture(const Image& image) : m_Data(NULL)
	{
		m_Image = image;

		glBindTexture(GL_TEXTURE_2D, m_Data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image.GetWidth(), m_Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.GetData().data());
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
	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Data);
	}
	const Image& Texture::GetImage() const
	{
		return m_Image;
	}
	void Texture::Cleanup()
	{
		if (m_Data)
			glDeleteTextures(1, &m_Data);
	}
	bool Texture::IsNull() const
	{
		return m_Image.IsNull() || m_Data == NULL;
	}
}
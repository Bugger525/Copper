#include "Texture.h"
#include "../System/Debug.h"
#include <GL/gl3w.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cu
{
	Texture::Texture()
		: m_Data(NULL), m_Width(0), m_Height(0)
	{
	}
	Texture::~Texture()
	{
		Cleanup();
	}
	bool Texture::LoadFromFile(std::string_view filePath)
	{
		int width, height, nrChannels;

		//stbi_set_flip_vertically_on_load(true);
		auto data = stbi_load(filePath.data(), &width, &height, &nrChannels, STBI_rgb_alpha);

		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
			return false;
		}

		m_Width = width;
		m_Height = height;

		glBindTexture(GL_TEXTURE_2D, m_Data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

		return true;
	}
	bool Texture::LoadFromData(unsigned int width, unsigned int height, unsigned char* const data)
	{
		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
			return false;
		}

		m_Width = width;
		m_Height = height;

		glBindTexture(GL_TEXTURE_2D, m_Data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

		return true;
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
	void Texture::Cleanup()
	{
		glDeleteTextures(1, &m_Data);
	}
}
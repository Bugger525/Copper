#pragma once

#include <string>
#include <vector>
#include <span>
#include "../core/IAsset.h"

namespace cu::gfx
{
	class Image : public core::IAsset
	{
	private:
		std::vector<unsigned char> m_Data;
		unsigned int m_Width, m_Height;
	public:
		Image();
		Image(unsigned int width, unsigned int height, std::span<unsigned char> data);

		const std::vector<unsigned char>& GetData() const;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		bool IsNull() const override;
	};
}
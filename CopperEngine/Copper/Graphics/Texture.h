#pragma once

#include <string>
#include "Image.h"
#include "../core/IAsset.h"

namespace cu::gfx
{
	class Texture : core::IAsset
	{
	private:
		unsigned int m_Data;

		Image m_Image;
	public:
		Texture();
		Texture(const Image& image);
		~Texture();

		void Bind() const;

		const Image& GetImage() const;

		void Cleanup();

		bool IsNull() const override;
	};
}
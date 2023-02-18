#include "Image.h"
#include "../System/Debug.h"

namespace Copper
{
	Image::Image() : m_Width(0), m_Height(0)
	{
	}
	Image::Image(unsigned int width, unsigned int height, std::span<unsigned char> data) : m_Width(width), m_Height(height)
	{
		m_Data.assign(data.begin(), data.end());
	}
	const std::vector<unsigned char>& Image::GetData() const
	{
		return m_Data;
	}
	unsigned int Image::GetWidth() const
	{
		return m_Width;
	}
	unsigned int Image::GetHeight() const
	{
		return m_Height;
	}
	bool Image::IsNull() const
	{
		return (m_Width == 0) || (m_Height == 0) || (m_Data.size() <= 0);
	}
}
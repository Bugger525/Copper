#pragma once

namespace Copper
{
	class IAsset
	{
	public:
		virtual bool IsNull() const = 0;
	};
}
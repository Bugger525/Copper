#pragma once

namespace cu::core
{
	class IAsset
	{
	public:
		virtual bool IsNull() const = 0;
	};
}
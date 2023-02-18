#pragma once

#include <string>
#include <map>
#include <memory>
#include <concepts>
#include "IAsset.h"

namespace Copper
{
	template<class T, class U>
	concept Derived = std::is_base_of<U, T>::value;

	template <Derived<IAsset> T>
	class AssetManager
	{
	private:
		std::map<std::string, std::weak_ptr<T>> m_Assets;
	public:
		void Add(std::string_view name, std::shared_ptr<T> ref);
		std::shared_ptr<T> Load(std::string_view name);
		bool Exists(std::string_view name);
		void Clear();
	};
}
#include "AssetManager.inl"
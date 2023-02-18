#include "../System/Debug.h"

namespace cu::core
{
	template <Derived<IAsset> T>
	void AssetManager<T>::Add(std::string_view name, std::shared_ptr<T> ref)
	{
		if (Exists(name))
		{
			CU_DBG_WARN("Asset {} already exists.", name);
			return;
		}
		m_Assets[std::string(name)] = ref;
	}
	template <Derived<IAsset> T>
	std::shared_ptr<T> AssetManager<T>::Load(std::string_view name)
	{
		if (!Exists(name))
		{
			CU_DBG_WARN("Asset {} does not exist.", name);
			return nullptr;
		}
		return std::static_pointer_cast<T>(m_Assets[std::string(name)].lock());
	}
	template <Derived<IAsset> T>
	bool AssetManager<T>::Exists(std::string_view name)
	{
		return m_Assets.find(std::string(name)) != m_Assets.end();
	}
	template <Derived<IAsset> T>
	void AssetManager<T>::Clear()
	{
		m_Assets.clear();
	}
}
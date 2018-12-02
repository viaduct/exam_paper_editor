#pragma once
#include "container.h"

namespace wally {
namespace data {

template <typename K, typename V, typename Ptr>
class MapContainer : public Container
{
public:
	using Container::Container;

	ContainerType type() const override final { return ContainerType::Map; }
	std::vector<Data*> datas() const override final;

	std::vector<K> keyList() const;
	std::vector<V*> valueList() const;
	std::vector<std::pair<K, V*>> list() const;
	K key(V const* v) const;
	V* value(K const& k) const { return m_map.at(k).get(); }
	bool hasKey(K const& k) const { return m_map.find(k) != m_map.end(); }
	bool hasValue(V const* v) const;
	size_t size() const override final { return m_map.size(); }

	void add(Ptr const& v, K const& k);
	void add(Ptr&& v, K const& k);
	void remove(K const& k);
	void clear();

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (V*, K const&)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	std::map<K, Ptr>
	m_map;
};

template <typename K, typename V, typename Ptr>
std::vector<Data*> MapContainer<K, V, Ptr>::datas() const
{
	std::vector<Data*> result;
	result.reserve(size());
	for ( auto& i : m_map )
	{
		result.push_back(i.second.get());
	}
	return result;
}

template <typename K, typename V, typename Ptr>
std::vector<K> MapContainer<K, V, Ptr>::keyList() const
{
	std::vector<K> result;
	result.reserve(m_map.size());
	for ( auto& i : m_map )
	{
		result.push_back(i.first);
	}
	return result;
}

template <typename K, typename V, typename Ptr>
std::vector<V*> MapContainer<K, V, Ptr>::valueList() const
{
	std::vector<V*> result;
	result.reserve(size());
	for ( auto& i : m_map )
	{
		result.push_back(i.second.get());
	}
	return result;
}

template <typename K, typename V, typename Ptr>
std::vector<std::pair<K, V*>> MapContainer<K, V, Ptr>::list() const
{
	std::vector<std::pair<K, V*>> result;
	result.reserve(m_map.size());
	for ( auto& i : m_map )
	{
		result.push_back(std::make_pair(i.first, i.second.get()));
	}
	return result;
}

template <typename K, typename V, typename Ptr>
K MapContainer<K, V, Ptr>::key(V const* v) const
{
	for ( auto& i : m_map )
	{
		if ( i.second.get() == v )
		{
			return i.first;
		}
	}
	assert(false);
}

template <typename K, typename V, typename Ptr>
bool MapContainer<K, V, Ptr>::hasValue(V const* v) const
{
	for ( auto& i : m_map )
	{
		if ( i.second.get() == v )
		{
			return true;
		}
	}
	return false;
}

template <typename K, typename V, typename Ptr>
void MapContainer<K, V, Ptr>::add(Ptr const& v, K const& k)
{
	m_map[k] = v;
	v->load(this);
	m_sig_added(v.get(), k);
}

template <typename K, typename V, typename Ptr>
void MapContainer<K, V, Ptr>::add(Ptr&& v, K const& k)
{
	auto raw = v.get();
	m_map[k] = std::move(v);
	raw->load(this);
	m_sig_added(raw, k);
}

template <typename K, typename V, typename Ptr>
void MapContainer<K, V, Ptr>::remove(K const& k)
{
	auto iter = m_map.find(k);
	m_sig_beforeRemoved(iter->second.get(), k);
	iter->second->unload();
	m_map.erase(iter);
}

template <typename K, typename V, typename Ptr>
void MapContainer<K, V, Ptr>::clear()
{
	m_sig_beforeCleared();
	for ( auto& pair : m_map )
	{
		pair.second->unload();
	}
	m_map.clear();
}

template <typename K, typename V>
class MapContainer<K, V, TypeEnum::Ref> : public Container
{
	class Remove;

public:
	using Container::Container;

	ContainerType type() const override final { return ContainerType::Map; }
	std::vector<Data*> datas() const override final;

	std::vector<K> keyList() const;
	std::vector<V*> valueList() const;
	std::vector<std::pair<K, V*>> list() const;
	K key(V const* v) const;
	V* value(K const& k) const { return m_map.at(k); }
	bool hasKey(K const& k) const { return m_map.find(k) != m_map.end(); }
	bool hasValue(V const* v) const;
	size_t size() const override final { return m_map.size(); }

	void add(V* v, K const& k);
	void remove(K const& k);
	void clear();

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (V*, K const&)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	std::map<K, V*>
	m_map;
};

template <typename K, typename V>
class MapContainer<K, V, TypeEnum::Ref>::Remove : public DataCmd
{
public:
	Remove(MapContainer<K, V, TypeEnum::Ref>* owner, K const& target) :
		m_owner(owner), m_target(target) {}
	void run() override final
	{
		m_prevValue = m_owner->value(m_target);
		m_owner->remove(m_target);
	}
	void undo() override final
	{
		m_owner->add(m_prevValue, m_target);
	}

private:
	MapContainer<K, V, TypeEnum::Ref>*
	m_owner;

	K
	m_target;

	V*
	m_prevValue;
};

template <typename K, typename V>
std::vector<Data*> MapContainer<K, V, TypeEnum::Ref>::datas() const
{
	std::vector<Data*> result;
	result.reserve(size());
	for ( auto& i : m_map )
	{
		result.push_back(i.second);
	}
	return result;
}

template <typename K, typename V>
std::vector<K> MapContainer<K, V, TypeEnum::Ref>::keyList() const
{
	std::vector<K> result;
	result.reserve(m_map.size());
	for ( auto& i : m_map )
	{
		result.push_back(i.first);
	}
	return result;
}

template <typename K, typename V>
std::vector<V*> MapContainer<K, V, TypeEnum::Ref>::valueList() const
{
	std::vector<V*> result;
	result.reserve(size());
	for ( auto& i : m_map )
	{
		result.push_back(i.second);
	}
	return result;
}

template <typename K, typename V>
std::vector<std::pair<K, V*>> MapContainer<K, V, TypeEnum::Ref>::list() const
{
	std::vector<std::pair<K, V*>> result;
	result.reserve(m_map.size());
	for ( auto& i : m_map )
	{
		result.push_back(i);
	}
	return result;
}

template <typename K, typename V>
K MapContainer<K, V, TypeEnum::Ref>::key(V const* v) const
{
	for ( auto& i : m_map )
	{
		if ( i.second == v )
		{
			return i.first;
		}
	}
	assert(false);
}

template <typename K, typename V>
bool MapContainer<K, V, TypeEnum::Ref>::hasValue(V const* v) const
{
	for ( auto& i : m_map )
	{
		if ( i.second == v )
		{
			return true;
		}
	}
	return false;
}

template <typename K, typename V>
void MapContainer<K, V, TypeEnum::Ref>::add(V* v, K const& k)
{
	m_map[k] = v;
	v->addDepended(this, std::make_shared<Remove>(this, k));
	m_sig_added(v, k);
}

template <typename K, typename V>
void MapContainer<K, V, TypeEnum::Ref>::remove(K const& k)
{
	auto iter = m_map.find(k);
	m_sig_beforeRemoved(iter->second, k);
	iter->second->removeDepended(this);
	m_map.erase(iter);
}

template <typename K, typename V>
void MapContainer<K, V, TypeEnum::Ref>::clear()
{
	m_sig_beforeCleared();
	for ( auto& item : m_map )
	{
		item->second->removeDepended(this);
	}
	m_map.clear();
}

}}

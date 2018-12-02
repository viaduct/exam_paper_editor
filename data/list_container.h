#pragma once
#include "container.h"

namespace wally {
namespace data {

template <typename T, typename Ptr>
class ListContainer : public Container
{
public:
	using Container::Container;

	ContainerType type() const override final { return ContainerType::List; }
	std::vector<Data*> datas() const override final;

	T* single(size_t at) const { return m_list.at(at).get(); }
	std::vector<T*> list() const;
	size_t size() const override final { return m_list.size(); }
	size_t index(T const* one, bool* isValid = nullptr) const;
	bool has(T const* one) const;

	void append(Ptr const& one);
	void append(Ptr&& one);
	void insert(Ptr const& one, size_t at);
	void insert(Ptr&& one, size_t at);
	void remove(size_t at);
	void move(size_t moveThis, size_t toHere);
	void clear();

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_moved() { return &m_sig_moved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (T*, size_t)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void (T*, size_t, size_t)>
	m_sig_moved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	std::vector<Ptr>
	m_list;
};

template <typename T, typename Ptr>
std::vector<Data*> ListContainer<T, Ptr>::datas() const
{
	std::vector<Data*> result;
	result.reserve(m_list.size());
	for ( auto& i : m_list )
	{
		result.push_back(i.get());
	}
	return result;
}

template <typename T, typename Ptr>
std::vector<T*> ListContainer<T, Ptr>::list() const
{
	std::vector<T*> result;
	result.reserve(m_list.size());
	for ( auto& i : m_list )
	{
		result.push_back(i.get());
	}
	return result;
}

template <typename T, typename Ptr>
size_t ListContainer<T, Ptr>::index(T const* one, bool* isValid) const
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_list.size(); ++i )
	{
		if ( m_list.at(i).get() == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

template <typename T, typename Ptr>
bool ListContainer<T, Ptr>::has(T const* one) const
{
	bool isValid;
	index(one, &isValid);
	return isValid;
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::append(Ptr const& one)
{
	auto at = m_list.size();
	m_list.push_back(one);
	one->load(this);
	m_sig_added(one.get(), at);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::append(Ptr&& one)
{
	auto at = m_list.size();
	auto raw = one.get();
	m_list.push_back(std::move(one));
	raw->load(this);
	m_sig_added(raw, at);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::insert(Ptr const& one, size_t at)
{
	m_list.insert(m_list.begin() + at, one);
	one->load(this);
	m_sig_added(one.get(), at);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::insert(Ptr&& one, size_t at)
{
	auto raw = one.get();
	m_list.insert(m_list.begin() + at, std::move(one));
	raw->load(this);
	m_sig_added(raw, at);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::remove(size_t at)
{
	m_sig_beforeRemoved(single(at), at);
	single(at)->unload();
	m_list.erase(m_list.begin() + at);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::move(size_t moveThis, size_t toHere)
{
	auto item = std::move(m_list[moveThis]);
	m_list.erase(m_list.begin() + moveThis);
	m_list.insert(m_list.begin() + toHere, std::move(item));

	m_sig_moved(m_list[toHere].get(), moveThis, toHere);
}

template <typename T, typename Ptr>
void ListContainer<T, Ptr>::clear()
{
	m_sig_beforeCleared();
	for ( auto& i : m_list )
	{
		i->unload();
	}
	m_list.clear();
}

template <typename T>
class ListContainer<T, TypeEnum::Ref> : public Container
{
	class Remove;

public:
	using Container::Container;

	ContainerType type() const override final { return ContainerType::List; }
	std::vector<Data*> datas() const override final;

	T* single(size_t at) const { return m_list.at(at); }
	std::vector<T*> list() const;
	size_t size() const override final { return m_list.size(); }
	size_t index(T const* one, bool* isValid = nullptr) const;
	bool has(T const* one) const;

	void append(T* one);
	void insert(T*, size_t at);
	void remove(size_t at);
	void move(size_t moveThis, size_t toHere);
	void clear();

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_moved() { return &m_sig_moved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (T*, size_t)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void (T*, size_t, size_t)>
	m_sig_moved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	std::vector<T*>
	m_list;
};

template <typename T>
class ListContainer<T, TypeEnum::Ref>::Remove : public DataCmd
{
public:
	Remove(ListContainer<T, TypeEnum::Ref>* owner, T* removeThis) :
		m_owner(owner), m_target(removeThis) {}
	void run() override final
	{
		m_prevIndex = m_owner->index(m_target);
		m_owner->remove(m_prevIndex);
	}
	void undo() override final
	{
		m_owner->insert(m_target, m_prevIndex);
	}

private:
	ListContainer<T, TypeEnum::Ref>*
	m_owner;

	T*
	m_target;

	size_t
	m_prevIndex;
};

template <typename T>
std::vector<Data*> ListContainer<T, TypeEnum::Ref>::datas() const
{
	std::vector<Data*> result;
	result.reserve(m_list.size());
	for ( auto& i : m_list )
	{
		result.push_back(i);
	}
	return result;
}

template <typename T>
std::vector<T*> ListContainer<T, TypeEnum::Ref>::list() const
{
	std::vector<T*> result;
	result.reserve(m_list.size());
	for ( auto& i : m_list )
	{
		result.push_back(i);
	}
	return result;
}

template <typename T>
size_t ListContainer<T, TypeEnum::Ref>::index(T const* one, bool* isValid) const
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_list.size(); ++i )
	{
		if ( m_list.at(i) == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

template <typename T>
bool ListContainer<T, TypeEnum::Ref>::has(T const* one) const
{
	bool isValid;
	index(one, &isValid);
	return isValid;
}

template <typename T>
void ListContainer<T, TypeEnum::Ref>::append(T* one)
{
	auto at = m_list.size();
	m_list.push_back(one);
	one->addDepended(this, std::make_shared<Remove>(this, one));
	m_sig_added(one, at);
}

template <typename T>
void ListContainer<T, TypeEnum::Ref>::insert(T* one, size_t at)
{
	m_list.insert(m_list.begin() + at, one);
	one->addDepended(this, std::make_shared<Remove>(this, one));
	m_sig_added(one, at);
}

template <typename T>
void ListContainer<T, TypeEnum::Ref>::remove(size_t at)
{
	m_sig_beforeRemoved(single(at), at);
	m_list.at(at)->removeDepended(this);
	m_list.erase(m_list.begin() + at);
}

template <typename T>
void ListContainer<T, TypeEnum::Ref>::move(size_t moveThis, size_t toHere)
{
	auto item = m_list[moveThis];
	m_list.erase(m_list.begin() + moveThis);
	m_list.insert(m_list.begin() + toHere, item);

	m_sig_moved(item, moveThis, toHere);
}

template <typename T>
void ListContainer<T, TypeEnum::Ref>::clear()
{
	m_sig_beforeCleared();
	for ( auto& item : m_list )
	{
		item->removeDepended(this);
	}
	m_list.clear();
}

}}

#pragma once
#include "container.h"

namespace wally {
namespace data {

template <typename T, typename Ptr>
class SetContainer : public Container
{
public:
	using Container::Container;

	ContainerType type() const override final { return ContainerType::Set; }
	std::vector<Data*> datas() const override final;

	std::vector<T*> list() const;
	size_t size() const override final { return m_set.size(); }

	void add(Ptr const& one);
	void add(Ptr&& one);
	void remove(T const* one);
	void clear();
	bool has(T const* one) const;

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (T* one)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	struct PtrComp
	{
		using is_transparent = std::true_type;
		struct Helper
		{
			T* ptr;
			Helper(T* ptr) : ptr(ptr) {}
			Helper(Ptr const& ptr) : ptr(ptr.get()) {}
		};
		bool operator ()(Helper const& first, Helper const& second) const
		{
			return first.ptr < second.ptr;
		}
	};
	std::set<Ptr, PtrComp>
	m_set;
};

template <typename T, typename Ptr>
std::vector<Data*> SetContainer<T, Ptr>::datas() const
{
	std::vector<Data*> result;
	result.reserve(size());
	for ( auto& i : m_set )
	{
		result.push_back(i.get());
	}
	return result;
}

template <typename T, typename Ptr>
std::vector<T*> SetContainer<T, Ptr>::list() const
{
	std::vector<T*> result;
	result.reserve(size());
	for ( auto& i : m_set )
	{
		result.push_back(i.get());
	}
	return result;
}

template <typename T, typename Ptr>
void SetContainer<T, Ptr>::add(Ptr const& one)
{
	m_set.insert(one);
	one->load(this);
	m_sig_added(one.get());
}

template <typename T, typename Ptr>
void SetContainer<T, Ptr>::add(Ptr&& one)
{
	auto raw = one.get();
	m_set.insert(std::move(one));
	raw->load(this);
	m_sig_added(raw);
}

template <typename T, typename Ptr>
void SetContainer<T, Ptr>::remove(T const* constOne)
{
	auto one = const_cast<T*>(constOne);
	m_sig_beforeRemoved(one);
	one->unload();
	auto iter = m_set.find(one);
	m_set.erase(iter);
}

template <typename T, typename Ptr>
void SetContainer<T, Ptr>::clear()
{
	m_sig_beforeCleared();
	for ( auto& i : m_set )
	{
		i->unload();
	}
	m_set.clear();
}

template <typename T, typename Ptr>
bool SetContainer<T, Ptr>::has(const T* one) const
{
	return m_set.find(const_cast<T*>(one)) != m_set.end();
}

template <typename T>
class SetContainer<T, TypeEnum::Ref> : public Container
{
public:
	class Remove;

	using Container::Container;

	ContainerType type() const override final { return ContainerType::Set; }
	std::vector<Data*> datas() const override final;

	std::vector<T*> list() const;
	size_t size() const override final { return m_set.size(); }

	void add(T* one);
	void remove(T const* one);
	void clear();
	bool has(T const* one) const;

	auto sig_added() { return &m_sig_added; }
	auto sig_beforeRemoved() { return &m_sig_beforeRemoved; }
	auto sig_beforeCleared() { return &m_sig_beforeCleared; }

private:
	boost::signals2::signal<void (T* one)>
	m_sig_added,
	m_sig_beforeRemoved;
	boost::signals2::signal<void ()>
	m_sig_beforeCleared;

	std::set<T*>
	m_set;
};

template <typename T>
class SetContainer<T, TypeEnum::Ref>::Remove : public DataCmd
{
public:
	Remove(SetContainer<T, TypeEnum::Ref>* owner, T* target) :
		m_owner(owner), m_target(target) {}
	void run() override final
	{
		m_owner->remove(m_target);
	}
	void undo() override final
	{
		m_owner->add(m_target);
	}

private:
	SetContainer<T, TypeEnum::Ref>*
	m_owner;

	T*
	m_target;
};

template <typename T>
std::vector<Data*> SetContainer<T, TypeEnum::Ref>::datas() const
{
	std::vector<Data*> result;
	result.reserve(size());
	for ( auto& i : m_set )
	{
		result.push_back(i);
	}
	return result;
}

template <typename T>
std::vector<T*> SetContainer<T, TypeEnum::Ref>::list() const
{
	std::vector<T*> result;
	result.reserve(size());
	for ( auto& i : m_set )
	{
		result.push_back(i);
	}
	return result;
}

template <typename T>
void SetContainer<T, TypeEnum::Ref>::add(T* one)
{
	m_set.insert(one);
	one->addDepended(this, std::make_shared<Remove>(this, one));
	m_sig_added(one);
}

template <typename T>
void SetContainer<T, TypeEnum::Ref>::remove(T const* constOne)
{
	auto one = const_cast<T*>(constOne);
	m_sig_beforeRemoved(one);
	one->removeDepended(this);
	m_set.erase(one);
}

template <typename T>
void SetContainer<T, TypeEnum::Ref>::clear()
{
	m_sig_beforeCleared();
	for ( auto& i : m_set )
	{
		i->removeDepended(this);
	}
	m_set.clear();
}

template <typename T>
bool SetContainer<T, TypeEnum::Ref>::has(const T* one) const
{
	return m_set.find(const_cast<T*>(one)) != m_set.end();
}

}}

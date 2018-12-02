#pragma once
#include "container.h"

namespace wally {
namespace data {

template <typename T, typename Ptr>
class SingleContainer : public Container
{
public:
	using Container::Container;

	ContainerType type() const override final
	{
		return ContainerType::Single;
	}
	std::vector<Data*> datas() const override final
	{
		// If there's data, return vector with size 1.
		// Otherwise, return null vector.
		return isValid() ? std::vector<Data*>{m_single.get()} : std::vector<Data*>();
	}
	size_t size() const override final
	{
		// If there's data, return 1.
		// Otherwise, return 0.
		return isValid() ? 1 : 0;
	}

	auto single() const { return m_single.get(); }
	bool isValid() const { return (bool)m_single; }

	void setValid(Ptr const& one)
	{
		m_single = one;
		m_single->load(this);
		m_sig_validSet();
	}
	void setValid(Ptr&& one)
	{
		m_single = std::move(one);
		m_single->load(this);
		m_sig_validSet();
	}
	void setNull()
	{
		m_sig_beforeNullSet();
		m_single->unload();
		m_single = nullptr;
	}

	auto sig_validSet() { return &m_sig_validSet; }
	auto sig_beforeNullSet() { return &m_sig_beforeNullSet; }

private:
	boost::signals2::signal<void ()>
	m_sig_validSet,
	m_sig_beforeNullSet;

	Ptr
	m_single;
};

template <typename T>
class SingleContainer<T, TypeEnum::Ref> : public Container
{
	class SetNull;

public:
	using Container::Container;

	ContainerType type() const override final
	{
		return ContainerType::Single;
	}
	std::vector<Data*> datas() const override final
	{
		// If there's data, return vector with size 1.
		// Otherwise, return null vector.
		return isValid() ? std::vector<Data*>{m_single} : std::vector<Data*>();
	}
	size_t size() const override final
	{
		// If there's data, return 1.
		// Otherwise, return 0.
		return isValid() ? 1 : 0;
	}

	auto single() const { return m_single; }
	bool isValid() const { return m_single; }

	void setValid(T* one);
	void setNull()
	{
		m_sig_beforeNullSet();
		m_single->removeDepended(this);
		m_single = nullptr;
	}

	auto sig_validSet() { return &m_sig_validSet; }
	auto sig_beforeNullSet() { return &m_sig_beforeNullSet; }

private:
	boost::signals2::signal<void ()>
	m_sig_validSet,
	m_sig_beforeNullSet;

	T*
	m_single{};
};

template <typename T>
class SingleContainer<T, TypeEnum::Ref>::SetNull : public DataCmd
{
public:
	SetNull(SingleContainer<T, TypeEnum::Ref>* owner) : m_owner(owner) {}
	void run() override final
	{
		m_prev = m_owner->single();
		m_owner->setNull();
	}
	void undo() override final
	{
		m_owner->setValid(m_prev);
	}

private:
	SingleContainer<T, TypeEnum::Ref>*
	m_owner;

	T*
	m_prev;
};

template <typename T>
void SingleContainer<T, TypeEnum::Ref>::setValid(T* one)
{
	m_single = one;
	one->addDepended(this, std::make_shared<SetNull>(this));
	m_sig_validSet();
}

}}

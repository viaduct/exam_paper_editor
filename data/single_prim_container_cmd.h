#pragma once
#include "single_prim_container.h"
#include "data_cmd.h"

namespace wally {
namespace data {

template <typename T> class SetSinglePrim : public DataCmd
{
public:
	void run() override final
	{
		m_prevValue = m_container->single();
		m_container->set(m_value);
	}
	void undo() override final
	{
		m_container->set(m_prevValue);
	}

	void setContainer(data::SinglePrimContainer<T>* container)
	{
		m_container = container;
	}

	void setValue(T const& t)
	{
		m_value = t;
	}
	void setValue(T&& t)
	{
		m_value = std::move(t);
	}

private:
	data::SinglePrimContainer<T>*
	m_container;

	T
	m_value,
	m_prevValue;
};

}}

#pragma once
#include "single_container.h"

namespace wally {
namespace data {

template <typename T, typename ContainerT = T> class CreateSetToSingle : public DataCmd
{
public:
	void run() override final
	{
		init();
		m_container->setValid(m_result);
		if ( m_solution )
		{
			m_solution->undo();
		}
	}
	void undo() override final
	{
		m_solution = m_result->solution();
		m_solution->run();
		m_container->setNull();
	}

	void setContainer(data::SingleContainer<ContainerT, std::shared_ptr<ContainerT>>* container)
	{
		m_container = container;
	}

	std::shared_ptr<T> result()
	{
		init();
		return m_result;
	}

private:
	void init()
	{
		if ( m_result.operator bool() == false )
		{
			m_result = std::make_shared<T>();
		}
	}

	std::shared_ptr<T>
	m_result;

	std::shared_ptr<DataCmd>
	m_solution;

	data::SingleContainer<ContainerT, std::shared_ptr<ContainerT>>*
	m_container;
};

template <typename T> class UnsetFromSingle : public DataCmd
{
public:
	void run() override final
	{
		m_prev = std::static_pointer_cast<T>(m_container->single()->shared_from_this());
		m_solution = m_prev->solution();
		m_solution->run();
		m_container->setNull();
	}
	void undo() override final
	{
		m_container->setValid(std::move(m_prev));
		m_solution->undo();
	}

	void setContainer(data::SingleContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

private:
	std::shared_ptr<T>
	m_prev;
	std::shared_ptr<DataCmd>
	m_solution;

	data::SingleContainer<T, std::shared_ptr<T>>*
	m_container;
};

template <typename T> class SetRefToSingle : public DataCmd
{
public:
	void run() override final
	{
		m_container->setValid(m_data);
	}
	void undo() override final
	{
		m_container->setNull();
	}

	void setContainer(data::SingleContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setData(T* data)
	{
		m_data = data;
	}

private:
	data::SingleContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_data;
};

template <typename T> class UnsetRefFromSingle : public DataCmd
{
public:
	void run() override final
	{
		m_prev = m_container->single();
		m_container->setNull();
	}
	void undo() override final
	{
		m_container->setValid(m_prev);
	}

	void setContainer(data::SingleContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

private:
	data::SingleContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_prev;
};

}}

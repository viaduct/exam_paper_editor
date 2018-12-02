#pragma once
#include "set_container.h"

namespace wally {
namespace data {

template <typename T, typename ContainerT = T> class CreateAddToSet : public DataCmd
{
public:
	void run() override final
	{
		init();
		m_container->add(m_result);
		if ( m_solution )
		{
			m_solution->undo();
		}
	}
	void undo() override final
	{
		m_solution = m_result->solution();
		m_solution->run();
		m_container->remove(m_result.get());
	}

	void setContainer(data::SetContainer<ContainerT, std::shared_ptr<ContainerT>>* container)
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

	data::SetContainer<ContainerT, std::shared_ptr<ContainerT>>*
	m_container;
};

template <typename T> class RemoveFromSet : public DataCmd
{
public:
	void run() override final
	{
		m_prev = std::static_pointer_cast<T>(const_cast<T*>(m_target)->shared_from_this());
		m_solution = m_prev->solution();
		m_solution->run();
		m_container->remove(m_target);
	}
	void undo() override final
	{
		m_container->add(std::move(m_prev));
		m_solution->undo();
	}

	void setContainer(data::SetContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

	void setTarget(T const* target)
	{
		m_target = target;
	}

private:
	std::shared_ptr<T>
	m_prev;
	std::shared_ptr<DataCmd>
	m_solution;

	data::SetContainer<T, std::shared_ptr<T>>*
	m_container;

	T const*
	m_target;
};

template <typename T> class ClearSet : public DataCmd
{
public:
	void run() override final
	{
		for ( auto& one : m_container->list() )
		{
			m_prev.push_back(std::static_pointer_cast<T>(one->shared_from_this()));
			auto solution = one->solution();
			solution->run();
			m_solutions.push_back(solution);
		}
		m_container->clear();
	}
	void undo() override final
	{
		for ( size_t i = 0; i < m_prev.size(); ++i )
		{
			m_container->add(std::move(m_prev[i]));
			m_solutions[i]->undo();
		}
		m_prev.clear();
		m_solutions.clear();
	}

	void setContainer(data::SetContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

private:
	std::vector<std::shared_ptr<T>>
	m_prev;
	std::vector<std::shared_ptr<DataCmd>>
	m_solutions;

	data::SetContainer<T, std::shared_ptr<T>>*
	m_container;
};

template <typename T> class AddRefToSet : public DataCmd
{
public:
	void run() override final
	{
		m_container->add(m_data);
	}
	void undo() override final
	{
		m_container->remove(m_data);
	}

	void setContainer(data::SetContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setData(T* data)
	{
		m_data = data;
	}

private:
	data::SetContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_data;
};

template <typename T> class RemoveRefFromSet : public DataCmd
{
public:
	void run() override final
	{
		m_container->remove(m_target);
	}
	void undo() override final
	{
		m_container->add(m_target);
	}

	void setContainer(data::SetContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setTarget(T const* target)
	{
		m_target = const_cast<T*>(target);
	}

private:
	data::SetContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_target;
};

template <typename T> class ClearRefSet : public DataCmd
{
public:
	void run() override final
	{
		for ( auto& one : m_container->list() )
		{
			m_prev.push_back(one);
		}
		m_container->clear();
	}
	void undo() override final
	{
		for ( auto& one : m_prev )
		{
			m_container->add(one);
		}
		m_prev.clear();
	}

	void setContainer(data::SetContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

private:
	std::vector<T*>
	m_prev;

	data::SetContainer<T, data::TypeEnum::Ref>*
	m_container;
};

}}

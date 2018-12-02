#pragma once
#include "map_container.h"

namespace wally {
namespace data {

template <typename K, typename T, typename ContainerT = T> class CreateAddToMap : public DataCmd
{
public:
	void run() override final
	{
		init();
		m_container->add(m_result, m_key);
		if ( m_solution )
		{
			m_solution->undo();
		}
	}
	void undo() override final
	{
		m_solution = m_result->solution();
		m_solution->run();
		m_container->remove(m_key);
	}

	void setContainer(data::MapContainer<K, ContainerT, std::shared_ptr<ContainerT>>* container)
	{
		m_container = container;
	}
	void setKey(K const& k)
	{
		m_key = k;
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

	data::MapContainer<K, ContainerT, std::shared_ptr<ContainerT>>*
	m_container;

	K
	m_key;
};

template <typename K, typename T> class RemoveFromMap : public DataCmd
{
public:
	void run() override final
	{
		m_prev = std::static_pointer_cast<T>(m_container->value(m_target)->shared_from_this());
		m_solution = m_prev->solution();
		m_solution->run();
		m_container->remove(m_target);
	}
	void undo() override final
	{
		m_container->add(std::move(m_prev), m_target);
		m_solution->undo();
	}

	void setContainer(data::MapContainer<K, T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

	void setTarget(K const& target)
	{
		m_target = target;
	}

private:
	std::shared_ptr<T>
	m_prev;
	std::shared_ptr<DataCmd>
	m_solution;

	data::MapContainer<K, T, std::shared_ptr<T>>*
	m_container;

	K
	m_target;
};

template <typename K, typename T> class ClearMap : public DataCmd
{
public:
	void run() override final
	{
		for ( auto& one : m_container->list() )
		{
			m_prev.push_back(std::make_pair(one.first, std::static_pointer_cast<T>(one.second->shared_from_this())));
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
			m_container->add(std::move(m_prev[i].second), m_prev[i].first);
			m_solutions[i]->undo();
		}
		m_prev.clear();
		m_solutions.clear();
	}

	void setContainer(data::MapContainer<K, T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

private:
	std::vector<std::pair<K, std::shared_ptr<T>>>
	m_prev;
	std::vector<std::shared_ptr<DataCmd>>
	m_solutions;

	data::MapContainer<K, T, std::shared_ptr<T>>*
	m_container;
};

template <typename K, typename T> class AddRefToMap : public DataCmd
{
public:
	void run() override final
	{
		m_container->add(m_data, m_key);
	}
	void undo() override final
	{
		m_container->remove(m_key);
	}

	void setContainer(data::MapContainer<K, T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setData(T* data)
	{
		m_data = data;
	}
	void setKey(K const& key)
	{
		m_key = key;
	}

private:
	data::MapContainer<K, T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_data;

	K
	m_key;
};

template <typename K, typename T> class RemoveRefFromMap : public DataCmd
{
public:
	void run() override final
	{
		m_prev = m_container->value(m_target);
		m_container->remove(m_target);
	}
	void undo() override final
	{
		m_container->add(m_prev, m_target);
	}

	void setContainer(data::MapContainer<K, T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setTarget(K const& target)
	{
		m_target = target;
	}

private:
	data::MapContainer<K, T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_prev;

	K
	m_target;
};

template <typename K, typename T> class ClearRefMap : public DataCmd
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
			m_container->add(one.second, one.first);
		}
		m_prev.clear();
	}

	void setContainer(data::MapContainer<K, T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

private:
	std::vector<std::pair<K, T*>>
	m_prev;

	data::MapContainer<K, T, data::TypeEnum::Ref>*
	m_container;
};

}}

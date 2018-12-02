#pragma once
#include "list_container.h"

namespace wally {
namespace data {

template <typename T, typename ContainerT = T> class CreateAppendToList : public DataCmd
{
public:
	void run() override final
	{
		init();
		m_container->append(m_result);
		if ( m_solution )
		{
			m_solution->undo();
		}
	}
	void undo() override final
	{
		m_solution = m_result->solution();
		m_solution->run();
		m_container->remove(m_container->size() - 1);
	}

	void setContainer(data::ListContainer<ContainerT, std::shared_ptr<ContainerT>>* container)
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

	data::ListContainer<ContainerT, std::shared_ptr<ContainerT>>*
	m_container;
};

template <typename T, typename ContainerT = T> class CreateInsertToList : public DataCmd
{
public:
	void run() override final
	{
		init();
		m_container->insert(m_result, m_index);
		if ( m_solution )
		{
			m_solution->undo();
		}
	}
	void undo() override final
	{
		m_solution = m_result->solution();
		m_solution->run();
		m_container->remove(m_index);
	}

	void setContainer(data::ListContainer<ContainerT, std::shared_ptr<ContainerT>>* container)
	{
		m_container = container;
	}
	void setIndex(size_t at)
	{
		m_index = at;
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

	data::ListContainer<ContainerT, std::shared_ptr<ContainerT>>*
	m_container;

	size_t
	m_index = 0;
};

template <typename T> class RemoveFromList : public DataCmd
{
public:
	void run() override final
	{
		m_prev = std::static_pointer_cast<T>(m_container->single(m_index)->shared_from_this());
		m_solution = m_prev->solution();
		m_solution->run();
		m_container->remove(m_index);
	}
	void undo() override final
	{
		m_container->insert(std::move(m_prev), m_index);
		m_solution->undo();
	}

	void setContainer(data::ListContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

	void setTarget(size_t at)
	{
		m_index = at;
	}

private:
	std::shared_ptr<T>
	m_prev;
	std::shared_ptr<DataCmd>
	m_solution;

	data::ListContainer<T, std::shared_ptr<T>>*
	m_container;

	size_t
	m_index = 0;
};

template <typename T> class ClearList : public DataCmd
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
			m_container->append(std::move(m_prev[i]));
			m_solutions[i]->undo();
		}
		m_prev.clear();
		m_solutions.clear();
	}

	void setContainer(data::ListContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

private:
	std::vector<std::shared_ptr<T>>
	m_prev;
	std::vector<std::shared_ptr<DataCmd>>
	m_solutions;

	data::ListContainer<T, std::shared_ptr<T>>*
	m_container;
};

template <typename T> class MoveList : public DataCmd
{
public:
	void run() override final
	{
		m_container->move(m_moveThis, m_toHere);
	}
	void undo() override final
	{
		m_container->move(m_toHere, m_moveThis);
	}

	void setContainer(data::ListContainer<T, std::shared_ptr<T>>* container)
	{
		m_container = container;
	}

	void setTarget(size_t moveThis, size_t toHere)
	{
		m_moveThis = moveThis;
		m_toHere = toHere;
	}

private:
	data::ListContainer<T, std::shared_ptr<T>>*
	m_container;

	size_t
	m_moveThis,
	m_toHere;
};

template <typename T> class AppendRefToList : public DataCmd
{
public:
	void run() override final
	{
		m_container->append(m_data);
	}
	void undo() override final
	{
		m_container->remove(m_container->size() - 1);
	}

	void setContainer(data::ListContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setData(T* data)
	{
		m_data = data;
	}

private:
	data::ListContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_data;
};

template <typename T> class InsertRefToList : public DataCmd
{
public:
	void run() override final
	{
		m_container->insert(m_data, m_index);
	}
	void undo() override final
	{
		m_container->remove(m_index);
	}

	void setContainer(data::ListContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setData(T* data)
	{
		m_data = data;
	}
	void setIndex(size_t index)
	{
		m_index = index;
	}

private:
	data::ListContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_data;

	size_t
	m_index;
};

template <typename T> class RemoveRefFromList : public DataCmd
{
public:
	void run() override final
	{
		m_prev = m_container->single(m_target);
		m_container->remove(m_target);
	}
	void undo() override final
	{
		m_container->insert(m_prev, m_target);
	}

	void setContainer(data::ListContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setTarget(size_t target)
	{
		m_target = target;
	}

private:
	data::ListContainer<T, data::TypeEnum::Ref>*
	m_container;

	T*
	m_prev;

	size_t
	m_target;
};

template <typename T> class ClearRefList : public DataCmd
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
			m_container->append(one);
		}
		m_prev.clear();
	}

	void setContainer(data::ListContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

private:
	std::vector<T*>
	m_prev;

	data::ListContainer<T, data::TypeEnum::Ref>*
	m_container;
};

template <typename T> class MoveRefList : public DataCmd
{
public:
	void run() override final
	{
		m_container->move(m_moveThis, m_toHere);
	}
	void undo() override final
	{
		m_container->move(m_toHere, m_moveThis);
	}

	void setContainer(data::ListContainer<T, data::TypeEnum::Ref>* container)
	{
		m_container = container;
	}

	void setTarget(size_t moveThis, size_t toHere)
	{
		m_moveThis = moveThis;
		m_toHere = toHere;
	}

private:
	data::ListContainer<T, data::TypeEnum::Ref>*
	m_container;

	size_t
	m_moveThis,
	m_toHere;
};

}}

#include "data.h"
#include "data_cmd.h"
#include "container.h"

namespace wally {
namespace data {

Data::Data()
{
}

Data::~Data()
{
}

Data*Data::parent() const
{
	return m_parentContainer->owner();
}

std::vector<Data*> Data::children() const
{
	// Iterates through all containers, which contains the data's children.
	// First, call vector::reserve for efficiency.
	// This step can be skipped if you do not care about performance.
	auto containers = this->containers();
	size_t sizeSum = 0;
	for ( auto& container : containers )
	{
		sizeSum += container->size();
	}

	// Now, put children to container "result".
	std::vector<Data*> result;
	result.reserve(sizeSum);
	for ( auto& container : containers )
	{
		for ( auto& child : container->datas() )
		{
			result.push_back(child);
		}
	}

	return result;
}

Container*Data::parentContainer() const
{
	return m_parentContainer;
}

void Data::load(Container* parentContainer)
{
	m_parentContainer = parentContainer;
}

void Data::unload()
{
	m_parentContainer = nullptr;
}

void Data::addDepended(Container* cont, const std::shared_ptr<DataCmd>& solution)
{
	m_solutions[cont] = solution;
}

void Data::addDepended(Container* cont, std::shared_ptr<DataCmd>&& solution)
{
	m_solutions[cont] = std::move(solution);
}

void Data::removeDepended(const Container* cont)
{
	m_solutions.erase(const_cast<Container*>(cont));
}

void Data::addDepended(const DependencyKey& key, const std::shared_ptr<DataCmd>& solution)
{
	m_customSolutions[key] = solution;
}

void Data::addDepended(const DependencyKey& key, std::shared_ptr<DataCmd>&& solution)
{
	m_customSolutions[key] = std::move(solution);
}

void Data::removeDepended(const DependencyKey& key)
{
	m_customSolutions.erase(key);
}

void Data::purgeDepended(const DependencyKey& key)
{
	m_customSolutions[key]->ignore();
	m_customSolutions.erase(key);
}

std::shared_ptr<DataCmd> Data::solution()
{
	// Take all children first.
	auto children = this->children();

	// Call vector::reserve() for performance.
	auto result = std::make_shared<DataCmdList>();
	result->reserve(children.size() + m_solutions.size() + m_customSolutions.size());

	// Children's solution will be run first.
	for ( auto& child : children )
	{
		result->append(child->solution());
	}

	for ( auto& solution : m_customSolutions )
	{
		result->append(solution.second);
	}
	for ( auto& solution : m_solutions )
	{
		result->append(solution.second);
	}

	return result;
}

}}

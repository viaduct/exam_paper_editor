#pragma once
#include <boost/signals2.hpp>
#include <map>
#include <memory>
#include "data_type.h"
#include "dependency_key.h"

namespace wally {
namespace data {

class DataCmd;
class Container;

// Data
class Data : public std::enable_shared_from_this<Data>
{
public:
	Data();
	virtual ~Data();
	Data(Data const&) = delete;
	Data& operator =(Data const&) = delete;

	virtual DataType type() const = 0;
	virtual std::vector<Container const*> containers() const = 0;

	Data* parent() const;
	std::vector<Data*> children() const;
	Container* parentContainer() const;

	void load(Container* parentContainer);
	void unload();

	void addDepended(Container* cont, std::shared_ptr<DataCmd> const& solution);
	void addDepended(Container* cont, std::shared_ptr<DataCmd>&& solution);
	void removeDepended(Container const* cont);

	void addDepended(DependencyKey const& key, std::shared_ptr<DataCmd> const& solution);
	void addDepended(DependencyKey const& key, std::shared_ptr<DataCmd>&& solution);
	void removeDepended(DependencyKey const& key);

	std::shared_ptr<DataCmd> solution();

private:
	std::map<Container*, std::shared_ptr<DataCmd>>
	m_solutions;

	std::map<DependencyKey, std::shared_ptr<DataCmd>>
	m_customSolutions;

	Container*
	m_parentContainer{};
};

}}

#pragma once
#include <boost/signals2.hpp>
#include <set>
#include <vector>
#include <memory>
#include "data_cmd.h"
#include "container_type.h"
#include "type_enum_ref.h"

namespace wally {
namespace data {

class Data;

class Container
{
public:
	Container(Data* owner);
	virtual ~Container() = default;
	Container(Container const&) = delete;
	Container& operator =(Container const&) = delete;

	virtual ContainerType type() const = 0;
	virtual size_t size() const = 0;
	virtual std::vector<Data*> datas() const = 0;

	Data* owner() const;

private:
	Data*
	m_owner{};
};

}}

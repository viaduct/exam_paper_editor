#include "dir.h"

namespace wally {
namespace data {

Dir::Dir() :
	m_subItemContainer(new SubItemContainer(this))
{
}

Dir::~Dir()
{
}

DataType Dir::type() const
{
	return DataType::Dir;
}

std::vector<const Container*> Dir::containers() const
{
	auto result = TreeItem::containers();

	result.push_back(m_subItemContainer.get());

	return result;
}

const Dir::SubItemContainer*Dir::subItemContainer() const
{
	return m_subItemContainer.get();
}

Dir::SubItemContainer*Dir::subItemContainer()
{
	return m_subItemContainer.get();
}

}}

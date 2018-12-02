#include "tree_item.h"

namespace wally {
namespace data {

TreeItem::TreeItem() :
	m_nameContainer(new NameContainer)
{
}

TreeItem::~TreeItem()
{
}

std::vector<const Container*> TreeItem::containers() const
{
	std::vector<const Container*> result;

	return result;
}

const TreeItem::NameContainer*TreeItem::nameContainer() const
{
	return m_nameContainer.get();
}

TreeItem::NameContainer*TreeItem::nameContainer()
{
	return m_nameContainer.get();
}

}}

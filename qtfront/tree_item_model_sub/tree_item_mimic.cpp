#include "tree_item_mimic.h"
#include "../tree_item_model.h"
#include "../../data/tree_item.h"

namespace wally {
namespace qtfront {
namespace tree_item_model_sub {

TreeItemMimic::TreeItemMimic()
{
}

TreeItemMimic::~TreeItemMimic()
{
}

data::TreeItem*TreeItemMimic::treeItem() const
{
	return m_treeItem;
}

void TreeItemMimic::setValidTreeItem(data::TreeItem* one)
{
	m_treeItem = one;

	auto nameUpdated = [this]
	{
		auto index = treeItemModel()->dataToIndex(m_treeItem);
		treeItemModel()->dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
	};
	m_con_nameUpdated = m_treeItem->nameContainer()->sig_updated()->connect(std::move(nameUpdated));
}

void TreeItemMimic::setNullTreeItem()
{
	m_con_nameUpdated.disconnect();

	m_treeItem = nullptr;
}

void TreeItemMimic::initialized()
{
}

}}}

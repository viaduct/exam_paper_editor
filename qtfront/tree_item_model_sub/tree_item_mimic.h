#pragma once
#include <boost/signals2.hpp>
#include "tree_item_model_context_holder.h"

namespace wally {

namespace data {
class TreeItem;
}

namespace qtfront {
namespace tree_item_model_sub {

class TreeItemMimic : public TreeItemModelContextHolder
{
public:
	TreeItemMimic();
	~TreeItemMimic();
	TreeItemMimic(TreeItemMimic const&) = delete;
	TreeItemMimic& operator =(TreeItemMimic const&) = delete;

	data::TreeItem* treeItem() const;
	void setValidTreeItem(data::TreeItem* one);
	void setNullTreeItem();

protected:
	void initialized() override final;

private:
	boost::signals2::scoped_connection
	m_con_nameUpdated;

	data::TreeItem*
	m_treeItem{};
};

}}}

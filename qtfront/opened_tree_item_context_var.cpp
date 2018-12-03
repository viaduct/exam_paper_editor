#include "opened_tree_item_context_var.h"

namespace wally {
namespace qtfront {

void OpenedTreeItemContextVar::openTreeItem(data::TreeItem* one)
{
	m_sig_treeItemOpened(one);
}

boost::signals2::signal<void (data::TreeItem*)>*OpenedTreeItemContextVar::sig_treeItemOpened()
{
	return &m_sig_treeItemOpened;
}

}}

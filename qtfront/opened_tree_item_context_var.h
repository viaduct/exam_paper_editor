#pragma once
#include <boost/signals2.hpp>

namespace wally {

namespace data {
class TreeItem;
}

namespace qtfront {

class OpenedTreeItemContextVar
{
public:
	OpenedTreeItemContextVar() = default;
	OpenedTreeItemContextVar(OpenedTreeItemContextVar const&) = delete;
	OpenedTreeItemContextVar& operator =(OpenedTreeItemContextVar const&) = delete;

	void openTreeItem(data::TreeItem* one);

	boost::signals2::signal<void (data::TreeItem*)>* sig_treeItemOpened();

private:
	boost::signals2::signal<void (data::TreeItem*)>
	m_sig_treeItemOpened;
};

}}

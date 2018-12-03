#include "tree_item_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace tree_item_view_sub {

void TreeItemViewContextHolder::init(Context* context, TreeItemView* view)
{
	m_view = view;
	ContextHolder::init(context);
}

TreeItemView*TreeItemViewContextHolder::treeItemView() const
{
	return m_view;
}

}}}

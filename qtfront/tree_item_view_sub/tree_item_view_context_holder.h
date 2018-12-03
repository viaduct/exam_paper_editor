#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class TreeItemView;

namespace tree_item_view_sub {

class TreeItemViewContextHolder : public ContextHolder
{
public:
	void init(Context* context, TreeItemView* view);

	TreeItemView* treeItemView() const;

private:
	using ContextHolder::init;

	TreeItemView*
	m_view;
};

}}}

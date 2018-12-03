#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class TreeItemModel;

namespace tree_item_model_sub {

class TreeItemModelContextHolder : public ContextHolder
{
public:
	void init(Context* context, TreeItemModel* model);

	TreeItemModel* treeItemModel() const;

private:
	using ContextHolder::init;

	TreeItemModel*
	m_model;
};

}}}

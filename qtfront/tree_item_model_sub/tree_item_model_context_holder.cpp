#include "tree_item_model_context_holder.h"

namespace wally {
namespace qtfront {
namespace tree_item_model_sub {

void TreeItemModelContextHolder::init(Context* context, TreeItemModel* model)
{
	m_model = model;
	ContextHolder::init(context);
}

TreeItemModel*TreeItemModelContextHolder::treeItemModel() const
{
	return m_model;
}

}}}

#pragma once
#include "tree_item.h"

namespace wally {
namespace data {

class Dir : public TreeItem
{
public:
	using SubItemContainer = SetContainer<TreeItem, std::shared_ptr<TreeItem>>;

	Dir();
	virtual ~Dir();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	SubItemContainer const* subItemContainer() const;
	SubItemContainer* subItemContainer();

private:
	std::unique_ptr<SubItemContainer>
	m_subItemContainer;
};

}}

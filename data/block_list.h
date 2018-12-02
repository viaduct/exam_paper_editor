#pragma once
#include "block.h"

namespace wally {
namespace data {

class BlockList : public Block
{
public:
	using SubBlockContainer = ListContainer<Block, std::shared_ptr<Block>>;

	BlockList();
	virtual ~BlockList();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	SubBlockContainer const* subBlockContainer() const;
	SubBlockContainer* subBlockContainer();

private:
	std::unique_ptr<SubBlockContainer>
	m_subBlockContainer;
};

}}

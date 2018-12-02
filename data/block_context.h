#pragma once
#include "context.h"

namespace wally {
namespace data {

class BlockList;

class BlockContext : public Context
{
public:
	using RootBlockContainer = SingleContainer<BlockList, std::shared_ptr<BlockList>>;

	BlockContext();
	virtual ~BlockContext();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	RootBlockContainer const* rootBlockContainer() const;
	RootBlockContainer* rootBlockContainer();

private:
	std::unique_ptr<RootBlockContainer>
	m_rootBlockContainer;
};

}}

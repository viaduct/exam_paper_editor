#include "block_list.h"

namespace wally {
namespace data {

BlockList::BlockList() :
	m_subBlockContainer(new SubBlockContainer(this))
{
}

BlockList::~BlockList()
{
}

DataType BlockList::type() const
{
	return DataType::BlockList;
}

std::vector<const Container*> BlockList::containers() const
{
	auto result = Block::containers();

	result.push_back(m_subBlockContainer.get());

	return result;
}

const BlockList::SubBlockContainer*BlockList::subBlockContainer() const
{
	return m_subBlockContainer.get();
}

BlockList::SubBlockContainer*BlockList::subBlockContainer()
{
	return m_subBlockContainer.get();
}

}}

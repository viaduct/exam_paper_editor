#include "block_context.h"
#include "block_list.h"

namespace wally {
namespace data {

BlockContext::BlockContext() :
	m_rootBlockContainer(new RootBlockContainer(this))
{
}

BlockContext::~BlockContext()
{
}

DataType BlockContext::type() const
{
	return DataType::BlockContext;
}

std::vector<const Container*> BlockContext::containers() const
{
	auto result = Context::containers();

	result.push_back(m_rootBlockContainer.get());

	return result;
}

const BlockContext::RootBlockContainer*BlockContext::rootBlockContainer() const
{
	return m_rootBlockContainer.get();
}

BlockContext::RootBlockContainer*BlockContext::rootBlockContainer()
{
	return m_rootBlockContainer.get();
}

}}

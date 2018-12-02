#include "matching_resp.h"
#include "matching_resp_item.h"

namespace wally {
namespace data {

MatchingResp::MatchingResp() :
	m_firstGroupContainer(new FirstGroupContainer(this)),
	m_secondGroupContainer(new SecondGroupContainer(this))
{
}

MatchingResp::~MatchingResp()
{
}

DataType MatchingResp::type() const
{
	return DataType::MatchingResp;
}

std::vector<const Container*> MatchingResp::containers() const
{
	auto result = Resp::containers();

	result.push_back(m_firstGroupContainer.get());
	result.push_back(m_secondGroupContainer.get());

	return result;
}

const MatchingResp::FirstGroupContainer*MatchingResp::firstGroupContainer() const
{
	return m_firstGroupContainer.get();
}

MatchingResp::FirstGroupContainer*MatchingResp::firstGroupContainer()
{
	return m_firstGroupContainer.get();
}

const MatchingResp::SecondGroupContainer*MatchingResp::secondGroupContainer() const
{
	return m_secondGroupContainer.get();
}

MatchingResp::SecondGroupContainer*MatchingResp::secondGroupContainer()
{
	return m_secondGroupContainer.get();
}

}}

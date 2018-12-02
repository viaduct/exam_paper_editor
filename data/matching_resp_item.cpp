#include "matching_resp_item.h"

namespace wally {
namespace data {

MatchingRespItem::MatchingRespItem() :
	m_textContainer(new TextContainer)
{
}

MatchingRespItem::~MatchingRespItem()
{
}

DataType MatchingRespItem::type() const
{
	return DataType::MatchingRespItem;
}

std::vector<const Container*> MatchingRespItem::containers() const
{
	std::vector<const Container*> result;

	return result;
}

const MatchingRespItem::TextContainer*MatchingRespItem::textContainer() const
{
	return m_textContainer.get();
}

MatchingRespItem::TextContainer*MatchingRespItem::textContainer()
{
	return m_textContainer.get();
}

}}

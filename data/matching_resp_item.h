#pragma once
#include "data.h"

namespace wally {
namespace data {

class MatchingRespItem : public Data
{
public:
	using TextContainer = SinglePrimContainer<std::string>;

	MatchingRespItem();
	virtual ~MatchingRespItem();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	TextContainer const* textContainer() const;
	TextContainer* textContainer();

private:
	std::unique_ptr<TextContainer>
	m_textContainer;
};

}}
